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

<img src="https://github.com/user-attachments/assets/3283be0d-4228-4ca0-a638-f685a51320de" height="20%" width="70%" alt="Disk Sanitization Steps"/>

