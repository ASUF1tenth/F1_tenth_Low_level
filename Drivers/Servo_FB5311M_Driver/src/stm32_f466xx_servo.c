#include <math.h> // For fmax, fmin
#include <stdint.h>
#include "stm32_f466xx_servo.h"
#include "servo_config.h"
#include "adc.h"
#include "tim.h"
uint16_t adc_buffer[ADC_BUFFER_SIZE];
volatile uint8_t adc_avg_ready = 0;
volatile uint16_t adc_average = 0;
float last_angle = 0.0f; // To store the last known angle

void Servo_Init(void)
{
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buffer, ADC_BUFFER_SIZE);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

float map_voltage_to_angle(float voltage, float min_angle, float max_angle)
{
  return (voltage - 0.0f) * (max_angle - min_angle) / (SERVO_MAX_VOLTAGE - 0.0f) + min_angle;
}

void setServoPulseWidth(uint16_t pulse_width)
{
  // Safety Clamping
  if (pulse_width < MIN_PWM_PULSE_WIDTH) pulse_width = MIN_PWM_PULSE_WIDTH;
  if (pulse_width > MAX_PWM_PULSE_WIDTH) pulse_width = MAX_PWM_PULSE_WIDTH;
  // Update Timer Compare Register (Duty Cycle)
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse_width);
}

float servoReadAngle(void)
{

  if (adc_avg_ready != 0)
  {
    adc_avg_ready = 0;
    float adc_value = (float)adc_average; // Use the averaged ADC value
    float voltage = (float)((adc_value) * (REF_NUCLEO_VOLTAGE / ADC_RESOLUTION));
    float angle = map_voltage_to_angle(voltage, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
    last_angle = angle; // Update the last known angle
    return angle;
  }
  else
  {
    return last_angle; // Return the last known angle if no new data is available
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    uint32_t sum = 0;

    for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++)
    {
      sum += (adc_buffer[i] & 0x0FFFu);
    }

    adc_average = sum / ADC_BUFFER_SIZE;
    adc_avg_ready = 1;
  }
}