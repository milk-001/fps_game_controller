#include <Keyboard.h>
#include <Mouse.h>
#include <Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int mouse_moving = 14;
int r = 6;
int mouse_r = 5;
int mouse_l = 4;
int jump = 8;
int f = 9;
int q = 10;
int shift = 15;
const int sw=7;
int x=0;
int y=0;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
  Mouse.begin();
  Keyboard.begin();
  Serial.println("Mouse Start!!");
  pinMode(mouse_r, INPUT);
  pinMode(mouse_l, INPUT);
  pinMode(r, INPUT);
  pinMode(jump, INPUT);
  pinMode(f, INPUT);
  pinMode(1, INPUT);
  pinMode(shift, INPUT);
  pinMode (sw, INPUT_PULLUP);
  pinMode(mouse_moving, INPUT);
}

void loop(){
  x=analogRead(A0);
  y=analogRead(A1);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
  
  int16_t gyroX, gyroZ;
  int Sensitivity = 300;
  gyroX = GyX / Sensitivity / 1.1 * -1;
  gyroZ = GyZ / Sensitivity * -1;

  if(digitalRead(mouse_moving) == HIGH){
    Mouse.move(gyroZ, gyroX);
  }
  if(digitalRead(mouse_l) == HIGH){
    Mouse.press(MOUSE_LEFT);
    Mouse.release(MOUSE_LEFT);
  }

  if(digitalRead(mouse_r) == HIGH){
    Mouse.press(MOUSE_RIGHT);
    Mouse.release(MOUSE_RIGHT);
  }

  if(digitalRead(r) == HIGH){
    Keyboard.press('r');
    Keyboard.release('r');
  }
  if(digitalRead(f) == HIGH){
    Keyboard.press('f');
    Keyboard.release('f');
  }
  if(digitalRead(jump) == HIGH){
    Keyboard.press(' ');
    Keyboard.release(' ');
  }
  if(digitalRead(q) == HIGH){
    Keyboard.press('q');
    Keyboard.release('q');
  }
  if(digitalRead(shift) == HIGH){
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.release(KEY_LEFT_SHIFT);
  }
  if (x==0) {
    Keyboard.press('s');
    Keyboard.release('s');
  }
  if (x > 1000) {
    Keyboard.press('w');
    Keyboard.release('w');
  }
  if (y==0) {
    Keyboard.press('a');
    Keyboard.release('a');
  }
  if (y > 1000) {
    Keyboard.press('d');
    Keyboard.release('d');
  }
  if (digitalRead(sw)==LOW) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.release(KEY_LEFT_CTRL);
  }
}
