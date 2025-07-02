
#include "ar_motor_control.h"
char ar_t_data = "0";
int x=1;
#define BUTTON_PIN1 11
#define BUTTON_PIN2 12



void setup() 
{
    ar_setupMotors();
}

void loop() 
{
  Serial.begin(9600);
    //초음파 센서로 입력받은 거리 출력
    long ar_distance = ar_getDistance();
   
    
  if (digitalRead(BUTTON_PIN1) == HIGH) {  // 컨베이여 동작 버튼
        ar_startConveyor();
    }
  if (digitalRead(BUTTON_PIN2) == HIGH) {  // 컨베이여 동작 멈춤 버튼
        ar_stopConveyor();
    }

    //초음파 센서로 입력받은 거리(cm)가 10이하일 경우 컨베이어 벨트 정지
  if (ar_distance <= 10 ) 
  {
    delay(200);
    x=ar_stopConveyor();
  }

  if (Serial.available()) 
  {
    ar_t_data = Serial.read();
        if(x==1)   //컨베이어 벨트가 정지후 작동   
        {
          if (ar_t_data == 'P') //평택(PP)
          {
              ar_startConveyor();
              ar_controlServo(120, 180, 180);//120도에 해당하는 구역으로 분류
              delay(5000);
              ar_startConveyor();
              ar_controlServo(180, 180, 180);
          }
          else if (ar_t_data == 'C') //천안(CC)
          {
              ar_startConveyor();
              ar_controlServo(180, 120, 180);//180도는 다음 구역으로 이동
              delay(7000);
              ar_startConveyor();
              ar_controlServo(180, 180, 180);
          }

          else if (ar_t_data == 'J') //제주(JJ)
          {
              ar_startConveyor();
              ar_controlServo(180, 180, 120);
              delay(8000);
              ar_startConveyor();
              ar_controlServo(180, 180, 180);
          }
          else if (ar_t_data == 'E') {  //에러(Error)
            ar_startConveyor();
            delay(800);
            ar_pushBox();
          }
          else
        {
            ar_startConveyor();//그 외에 지역(Else)
            ar_controlServo(180, 180, 180);//모든 구간이 열려 그외 지역으로 빠짐
            delay(200);
            ar_controlServo(180, 180, 180);
          }
        }

       x=0;
      }

}