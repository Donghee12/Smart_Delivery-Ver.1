#include "ar_motor_control.h"

Servo ar_servo_1, ar_servo_2, ar_servo_3;

//컨베이어 벨트 번호설정
int ar_conveyor_1 = 6                                                                                                                                                                                                                                                                                                                                                                 ;
int ar_conveyor_2 = 5;

//모터 핀번호 설정
int ar_servo_motor_1 = 10;
int ar_servo_motor_2 = 8;
int ar_servo_motor_3 = 9;

//모터및 초음파 센서 연결
void ar_setupMotors()
{
  //모터 번호를 서보모터 연결
    ar_servo_1.attach(ar_servo_motor_1);
    ar_servo_2.attach(ar_servo_motor_2);
    ar_servo_3.attach(ar_servo_motor_3);

    //초음파 센서 입출력 핀번호 설정
    pinMode(ar_g_ultrasonic_trig, OUTPUT);
    pinMode(ar_g_ultrasonic_echo, INPUT);

    //컨베이어 모터 설정
    pinMode(ar_conveyor_1, OUTPUT);
    pinMode(ar_conveyor_2, OUTPUT);

    ar_servo_1.write(180);    
    ar_servo_2.write(180);    
    ar_servo_3.write(180);
}

//서보모터 각도 조절
void ar_controlServo(int ar_servo_motor_1_angle, int ar_servo_motor_2_angle, int ar_servo_motor_3_angle) 
{
    ar_servo_1.write(ar_servo_motor_1_angle);    //1번모터 각도 회전
    ar_servo_2.write(ar_servo_motor_2_angle);    //2번모터 각도 회전
    ar_servo_3.write(ar_servo_motor_3_angle);    //3번모터 각도 회전
    delay(10);
}

//컨베이어 벨트 정지
int ar_stopConveyor() 
{
    analogWrite(ar_conveyor_1, 0);
    analogWrite(ar_conveyor_2, 0);
    return 1;
}

//컨베이어 벨트 속도 255로 설정
void ar_startConveyor() 
{
    analogWrite(ar_conveyor_1, 255);
    analogWrite(ar_conveyor_2, 0);
}

//초음파 센서 거리 입력 확인
long ar_getDistance() 
{
    digitalWrite(ar_g_ultrasonic_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(ar_g_ultrasonic_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ar_g_ultrasonic_trig, LOW);

    long ar_duration = pulseIn(ar_g_ultrasonic_echo, HIGH);
    return (ar_duration / 29.0) / 2.0;
}

// 불량품 쳐내기 위한 1번모터, 천천히 쳐낸후 다시 원래위치로 이동
void ar_pushBox() 
{
    int ar_servo_motor_1_angle = 80;
    ar_servo_1.write(ar_servo_motor_1_angle);
    delay(3000);
    for (int i = 0; i < 90; i++) 
    {
        ar_servo_motor_1_angle--;
        if (ar_servo_motor_1_angle < 2) 
        {
            ar_servo_motor_1_angle = 180;
        }
        ar_servo_1.write(ar_servo_motor_1_angle);
        delay(10);
    }
}