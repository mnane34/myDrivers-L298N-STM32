# Driver Development of HCSR-04 Ultrasonic Sensor on STM32 

# ⚡ What is HCSR-04 Ultrasonic Sensors?

HCSR-04 Ultrasonic sensors use high-frequency sound waves to detect objects. They measure the time taken for the sound to travel to an object and reflect back. This allows accurate distance measurement in various applications.

# 🔥 How to Use HCSR-04 Ultrasonic Sensor with Microcontrollers?

Connect the TRIG and ECHO pins of the HC-SR04 to your microcontroller’s GPIO. Trigger the sensor with a short pulse and measure the duration of the echo signal. Use this time measurement to calculate the distance in centimeters or inches.

# 🛠️ Electrical Diagram

- **VCC (Pin 1)**  

Power supply pin, typically connected to +5V.

- **TRIG (Pin 2)**  

Trigger input pin. A short HIGH pulse (usually 10 µs) is sent to start the measurement.

- **ECHO (Pin 3)**  

Echo output pin. It goes HIGH for a duration proportional to the distance of the object.

- **GND (Pin 4)**  

Ground connection (GND). It serves as the reference voltage for the circuit.

![Shematic](images/shematic.JPG)

In this application, the STM32 Nucleo F446RE development board was used. You can refer to the above wiring diagram.

# 🚀 Code Explanation