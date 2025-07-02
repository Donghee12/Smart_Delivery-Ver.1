#pragma once
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <Servo.h>

// 핀 번호 설정
#define ar_g_ultrasonic_trig 3    
#define ar_g_ultrasonic_echo 2

extern int ar_conveyor_1;
extern int ar_conveyor_2;
extern int ar_servo_motor_1;
extern int ar_servo_motor_2;
extern int ar_servo_motor_3;

// 모터 및 서보모터 제어 관련 함수 선언
void ar_setupMotors();
void ar_controlServo(int ar_servo_motor_1_angle, int ar_servo_motor_2_angle, int ar_servo_motor_3_angle);
int ar_stopConveyor();
void ar_startConveyor();
long ar_getDistance();
void ar_pushBox();
#endif
