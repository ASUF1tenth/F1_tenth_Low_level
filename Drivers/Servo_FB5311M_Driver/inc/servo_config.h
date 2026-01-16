#ifndef __SERVO_CONFIG_H
#define __SERVO_CONFIG_H
/**
 * @file servo_config.h
 * @brief Configuration parameters for the FB5311M Servo Driver
*/
#define DEBUG_ENABLED 0
#define SERVO_MIN_ANGLE         0.0f    // Minimum angle in degrees
#define SERVO_MAX_VOLTAGE       3.3f    // Maximum voltage in volts
#define REF_NUCLEO_VOLTAGE       3.3f    // Minimum voltage in volts
#define SERVO_MAX_ANGLE        180.0f  // Maximum angle in degrees
#define SERVO_PWM_FREQUENCY     50      // PWM frequency in Hz
#define SERVO_KP          0.1f    // Proportional gain for control  
#define SERVO_KI          0.01f   // Integral gain for control
#define SERVO_KD          0.001f  // Derivative gain for control
#define SERVO_CONTROL_FREQUENCY  100.0f  // Control loop frequency in Hz
#define INTEGRAL_WINDUP_GUARD  60.0f   // Integral windup guard
#define ADC_RESOLUTION 4095.0f  // 12-bit ADC
#define ADC_BUFFER_SIZE 16     // Size of the ADC buffer

#endif /* __SERVO_CONFIG_H */