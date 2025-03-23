This project demonstrates how to build a dimmable RGB LED controller using PWM (Pulse Width Modulation) with a Raspberry Pi Pico W. The brightness of each LED color (red, green, blue) is controlled via user input over USB serial, allowing real-time adjustments of each channel's duty cycle.

The main objective of this project is to develop a clear understanding of how PWM controls LED brightness by adjusting the duty cycle, and to gain hands-on experience using the Raspberry Pi Pico SDK within Visual Studio Code, supported by the official Pico extension.

<img src="https://github.com/user-attachments/assets/b5bb4672-7a68-4cf8-adb6-1525310fd4e0" height="20%" width="100%" alt="Disk Sanitization Steps"/>

The circuit was built by referencing the Pico PWM layout diagram, which outlines the GPIO pins along with their corresponding PWM slices and channels. For this project, GPIO16, GPIO17, and GPIO18 were selected to control the red, green, and blue channels of a common cathode RGB LED.

<img src="https://github.com/user-attachments/assets/948efbb2-78ef-4658-b533-5855249a096c" height="20%" width="20%" alt="Disk Sanitization Steps"/>

Each GPIO pin was connected through a 330 ohm resistor to its respective LED pin. The longest leg of the RGB LED (the common cathode) was connected to ground, completing the circuit.

<img src="https://github.com/user-attachments/assets/1c2be0dc-76cb-4c86-9447-313cb74e6538" height="20%" width="20%" alt="Disk Sanitization Steps"/>


