#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(12, 13);  // 블루투스 모듈 연결
Servo ser1;
Servo ser2;
Servo esc;

int escSpeed = 1500;        // 초기 ESC 속도
int ser1Angle = 90;         // 기어
int ser2Angle = 90;         // 방향

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  
  ser1.attach(9);
  ser2.attach(10);
  esc.attach(11);

  esc.writeMicroseconds(1000);  // ESC 초기화
  delay(2000);
}

void loop() {
  if (BT.available()) {
    char command = BT.read();
    Serial.print("Command: ");
    Serial.println(command);

    switch (command) {
      case '1':  // ESC 속도 증가
        escSpeed += 100;
        if (escSpeed > 2000) escSpeed = 2000;
        esc.writeMicroseconds(escSpeed);
        Serial.print("ESC Speed Up: ");
        Serial.println(escSpeed);
        break;

      case '2':  // ESC 속도 감소
        escSpeed -= 100;
        if (escSpeed < 1000) escSpeed = 1000;
        esc.writeMicroseconds(escSpeed);
        Serial.print("ESC Speed Down: ");
        Serial.println(escSpeed);
        break;

      case '3':  // ser1 각도 증가
        ser1Angle += 5;
        if (ser1Angle > 180) ser1Angle = 180;
        ser1.write(ser1Angle);
        Serial.print("ser1 Angle Up: ");
        Serial.println(ser1Angle);
        break;

      case '4':  // ser1 각도 감소
        ser1Angle -= 5;
        if (ser1Angle < 0) ser1Angle = 0;
        ser1.write(ser1Angle);
        Serial.print("ser1 Angle Down: ");
        Serial.println(ser1Angle);
        break;

      case '5':  // ser2 각도 증가
        ser2Angle += 5;
        if (ser2Angle > 180) ser2Angle = 180;
        ser2.write(ser2Angle);
        Serial.print("ser2 Angle Up: ");
        Serial.println(ser2Angle);
        break;

      case '6':  // ser2 각도 감소
        ser2Angle -= 5;
        if (ser2Angle < 0) ser2Angle = 0;
        ser2.write(ser2Angle);
        Serial.print("ser2 Angle Down: ");
        Serial.println(ser2Angle);
        break;

      case '7':  // ESC 정지
        esc.writeMicroseconds(1000);
        escSpeed = 1000;
        Serial.println("ESC Stop");
        break;

      case '8':  // 초기화
        escSpeed = 1000;
        ser1Angle = 90;
        ser2Angle = 90;
        esc.writeMicroseconds(escSpeed);
        ser1.write(ser1Angle);
        ser2.write(ser2Angle);
        Serial.println("Reset to default");
        break;
    }
  }
}
