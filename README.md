This project demonstrates how to build a dimmable RGB LED controller using PWM (Pulse Width Modulation) with a Raspberry Pi Pico W. The brightness of each LED color (red, green, blue) is controlled via user input over USB serial, allowing real-time adjustments of each channel's duty cycle.

The main objective of this project is to develop a clear understanding of how PWM controls LED brightness by adjusting the duty cycle, and to gain hands-on experience using the Raspberry Pi Pico SDK within Visual Studio Code, supported by the official Pico extension.

<img src="https://github.com/user-attachments/assets/b5bb4672-7a68-4cf8-adb6-1525310fd4e0" height="20%" width="100%" alt="Disk Sanitization Steps"/>

The circuit was built by referencing the Pico PWM layout diagram, which outlines the GPIO pins along with their corresponding PWM slices and channels. For this project, GPIO16, GPIO17, and GPIO18 were selected to control the red, green, and blue channels of a common cathode RGB LED.

<img src="https://github.com/user-attachments/assets/1c2be0dc-76cb-4c86-9447-313cb74e6538" height="20%" width="50%" alt="Disk Sanitization Steps"/>

Each GPIO pin was connected through a 330 ohm resistor to its respective LED pin. The longest leg of the RGB LED (the common cathode) was connected to ground, completing the circuit.

<img src="https://github.com/user-attachments/assets/948efbb2-78ef-4658-b533-5855249a096c" height="20%" width="20%" alt="Disk Sanitization Steps"/>

Since this project uses PWM to control LED brightness and takes user input through a serial terminal, a few initial setup steps are required in the build system. First, the hardware_pwm library is added to the target_link_libraries section of the CMakeLists.txt file. This gives access to the necessary functions for PWM control.

Additionally, USB output is enabled to allow communication with the serial terminal, which is used to receive user commands during runtime.

At the top of the code, the required headers are included:

- pico/stdlib.h for core Pico functions

- hardware/pwm.h for PWM functionality

- string.h for handling user input as strings

<img src="https://github.com/user-attachments/assets/8a01ce25-8487-41ce-84e9-ad526ad0dd89" height="20%" width="70%" alt="Disk Sanitization Steps"/>

----------------------------------------------------------------------

<img src="https://github.com/user-attachments/assets/3283be0d-4228-4ca0-a638-f685a51320de" height="20%" width="70%" alt="Disk Sanitization Steps"/>

To begin, stdio_init_all() is called. This initializes standard input and output, allowing communication between the Pico and the serial terminal over USB. Without this, printf() and scanf() would not work. Next, gpio_set_function() is used for GPIO16, GPIO17, and GPIO18 to assign each pin to the PWM function. This tells the Pico to treat these GPIOs as PWM outputs instead of general-purpose digital pins. While the Pico PWM layout diagram shows which slice and channel each GPIO is connected to, the Pico SDK provides two helper functions that handle this for us:

pwm_gpio_to_slice_num(pin)   --> returns slice number (0 to 7)
pwm_gpio_to_channel(pin)     --> returns channel (PWM_CHAN_A or PWM_CHAN_B)

Each GPIO maps to a specific slice and channel, and these functions ensure the correct association automatically. After this, the wrap value is set using pwm_set_wrap(). The wrap defines the maximum count for the PWM cycle. We set it to 65535 to take full advantage of the 16-bit resolution: wrap = 65535 --> counts from 0 to 65535. To control the frequency of the PWM signal, the clock divider (clkdiv) is set using pwm_set_clkdiv(). The PWM frequency is determined by the following formula:
- PWM frequency = (125000000 / clkdiv) / (wrap + 1)

In this project, we wanted a 1 kHz PWM signal, so we solved for clkdiv: --> clkdiv = (125000000 / (1000 * (65535 + 1))) = ~1.9

We used 1.9f to represent the value as a float (32-bit) instead of a double (64-bit), which is more efficient on the Pico.

<img src="https://github.com/user-attachments/assets/42edf015-35f5-44ad-8b60-5f18f6fc7fd0" height="20%" width="50%" alt="Disk Sanitization Steps"/>

<img src="https://github.com/user-attachments/assets/410531ce-8fe5-4a73-abba-148c9c4d3ade" height="20%" width="50%" alt="Disk Sanitization Steps"/>

The main logic of the program is handled using a do-while loop that continuously prompts the user for input. First, the user is asked to enter a color (red, green, or blue). Based on the input, the corresponding if or else if statement runs and asks for a brightness percentage from 0 to 100. Using percentage input is more user-friendly than requiring the user to manually enter a number between 0 and 65535. To convert the percentage into a usable PWM value, we multiply the percentage by 65535 and divide by 100:
- duty_cycle_value = 65535 * (brightness_percentage / 100.0f)

This value is then passed into the pwm_set_chan_level() function, which takes three arguments: the slice number, the channel, and a value between 0 and the wrap value (65535). This function is what actually updates the brightness of the corresponding color. After each color change, the brightness levels of all three colors are printed to the terminal so the user can keep track of the current LED state. If the user enters "exit", the program stops asking for input and all three channel levels are set to 0, turning off the LED.

