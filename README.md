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

<pre><code class="language-c">uint32_t POT_read(ADC_HandleTypeDef* hadc);
</code></pre>

This function starts an ADC conversion, reads the potentiometer value if available, and returns the result.

<pre><code class="language-c">uint32_t POT_map(uint32_t value, long inMin, long inMax, long outMin, long outMax);
</code></pre>

This function maps the potentiometer’s ADC value from an input range to a desired output range.

<pre><code class="language-c">void L298N_init(TIM_HandleTypeDef* hTIMx);
</code></pre>

This function initializes the L298N motor driver by starting PWM on the specified timer channel.

<pre><code class="language-c">void L298N_setPWM(TIM_HandleTypeDef* hTIMx, uint32_t xChannel, uint16_t xDuty);
</code></pre>

This function sets the PWM duty cycle for the L298N motor driver on the specified timer channel.

<pre><code class="language-c">void L298N_setDirection(L298N_Direction_t direction);
</code></pre>

This function sets the rotation direction of the motor by controlling the L298N input pins.

# 🖥️ Test Highlights

You can easily test the L298N Motor Driver Module using the following code snippet

<pre><code class="language-c">#include "main.h"
#include "POT.h"
#include "L298N.h"

ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim2;

extern L298N_Direction_t motorDirection;
uint32_t potValue;
uint32_t dutyValue;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC1_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  L298N_init(&htim2);
  while (1)
  {
     potValue = POT_read(&hadc1);
     dutyValue = POT_map(potValue, 0, 4095, 0, 100);
     motorDirection = LEFT;
     L298N_setDirection(motorDirection);
     L298N_setPWM(&htim2,TIM_CHANNEL_1, dutyValue);
  }
}
</code></pre>

![test](images/test.jpg)

## 🎉 Thank You for Reviewing!

Thank you for taking the time to check out this project.

Feel free to follow me on these platforms for more updates and projects.

- YouTube: @mnane34

- LinkedIn: Mertcan Nane