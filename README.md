# Driver Development of L298N Motor Driver Module on STM32 

# ⚡ What is L298N Motor Driver Modules?

The L298N Motor Driver Module is an electronic board that controls the speed and direction of DC motors and stepper motors. It uses an H-bridge circuit to allow current flow in both directions. This makes it popular in robotics and DIY projects.

# 🔥 How to Use L298N Motor Driver Module with Microcontrollers?

Using the L298N with a microcontroller, connect the motor wires to the output pins and the power supply to the module. Then, connect the control pins to the microcontroller’s digital pins. By sending HIGH or LOW signals, you can control motor speed and direction.

# 🛠️ Electrical Diagram

- **IN1 (Pin 1)**<br> 
Input control pin for Motor A. Used to set the direction of rotation.

- **IN2 (Pin 2)**<br> 
Second input control pin for Motor A. Works with IN1 to control direction.

- **IN3 (Pin 3)**<br>
Input control pin for Motor B. Used to set the direction of rotation. 

- **IN4 (Pin 4)**<br>
Second input control pin for Motor B. Works with IN3 to control direction. 

- **ENA (Pin 5)**<br>
Enable pin for Motor A. A PWM signal can be applied here to control speed. 

- **ENB (Pin 6)**<br>
Enable pin for Motor B. A PWM signal can be applied here to control speed. 

- **OUT1, OUT2 (Pins 7, 8)**<br>
Output pins for Motor A. Connect the terminals of Motor A here. 

- **OUT3, OUT4 (Pins 9, 10)**<br>
Output pins for Motor B. Connect the terminals of Motor B here. 

- **VCC (Pin 11)**<br>
Logic power supply, usually connected to +5V. 

- **GND (Pin 12)**<br>
Ground connection (common ground for logic and motor supply). 

- **12V / VMS (Pin 13)**<br>
Motor power supply pin. Provides power for the motors (typically 7V–12V).

![Shematic](images/shematic.png)

In this application, the STM32 Nucleo F446RE development board was used. You can refer to the above wiring diagram.

# 🚀 Code Explanation
