

#include <Wire.h>
const byte speed = 100;
const int In1 = 4;
const int In2 = 5;
const int In3 = 6;      
const int In4 = 7;

int front = 0;
int right = 0;
int left  = 0;
int back  = 0;


#define JoyX A0   // 搖桿 X 軸的接腳連接 Uno A0
#define JoyY A1   // 搖桿 Y 軸的接腳連接 Uno A1

//超音波
int trigPinF = 9;  //前方超音波觸發Trig
int echoPinF = 8;  //前方超音波觸發echo
unsigned long distanceF ; //距離cm

int trigPinB = 11; //後方超音波觸發Trig
int echoPinB = 10; //後方超音波觸發echo
unsigned long distanceB ;  //距離cm

unsigned long pingF(){
  digitalWrite(trigPinF , HIGH);  //觸發腳位高電位
  delayMicroseconds(10);   //持續5微秒
  digitalWrite(trigPinF , LOW);
  return ( pulseIn(echoPinF ,HIGH) /58); //換算成cm並回傳
}

unsigned long pingB(){
  digitalWrite(trigPinB , HIGH);  // 觸發腳位高電位
  delayMicroseconds(10); //持續5微秒
  digitalWrite(trigPinB , LOW);
  return ( pulseIn(echoPinB , HIGH) /58);  //換算成cm並回傳
}

void setup(){
  Serial.begin(38400);
  const byte speed = 50;
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  //超音波
  pinMode(trigPinF,OUTPUT);
  pinMode(echoPinF,INPUT);

  pinMode(trigPinB,OUTPUT);
  pinMode(echoPinB,INPUT);
}
void loop(){
int valX = analogRead(JoyX); // Read current value of Joystick 1 X axis
int valY = analogRead(JoyY); // Read current value of Joystick 1 Y axis



//超音波
String str1 = "";

distanceF = pingF();
distanceB = pingB();

str1 = "Front="+String(distanceF)+"cm , Back=" + String(distanceB)+"cm";



while(Serial.available())
{
char c=Serial.read();
  if(c=='L')
{
     Serial.println("left");
     mstop();
     delay(100);
     mfront();
     delay(200);
     mleft();
     delay(700);
     mfront();
     delay(300);
     mstop();
}
if(c=='R')
{
     Serial.println("right");
     mstop();
     delay(100);
     mfront();
     delay(200);
     mright();
     delay(700);
     mfront();
     delay(300);
     mstop();
}
if (c=='F'){
     // 將搖桿讀取的值轉換為高低脈衝間的對應值
     Serial.println("front");
     mfront();
     delay(500);
     mstop();
  }
if (c=='B'){
     // 將搖桿讀取的值轉換為高低脈衝間的對應值
     Serial.println("back");
     mback();
     delay(500);
     mstop();
  }
if (c=='S'){
     // 將搖桿讀取的值轉換為高低脈衝間的對應值
     Serial.println("stop");
     mstop();
  }  
   }

}
void mstop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mfront(){
  analogWrite(In1, speed); // 馬達 A 的 PWM 輸出
  analogWrite(In2, speed); 
  analogWrite(In3, speed); // 馬達 B 的 PWM 輸出
  analogWrite(In4, speed);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void mback(){
  analogWrite(In1, speed); // 馬達 A 的 PWM 輸出
  analogWrite(In2, speed); 
  analogWrite(In3, speed); // 馬達 B 的 PWM 輸出
  analogWrite(In4, speed);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
void mleft(){
  analogWrite(In1, speed); // 馬達 A 的 PWM 輸出
  analogWrite(In2, speed); 
  analogWrite(In3, speed); // 馬達 B 的 PWM 輸出
  analogWrite(In4, speed);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mright(){
  analogWrite(In1, speed); // 馬達 A 的 PWM 輸出
  analogWrite(In2, speed); 
  analogWrite(In3, speed); // 馬達 B 的 PWM 輸出
  analogWrite(In4, speed);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
