
#include <SPI.h>
#include <Pixy2.h>
Pixy2 pixy;
int sign=0;

int maxArea = 0;
int minArea = 0;
int i=0;
int x = 0;                  
int y = 0;
int pot_val=0;
char bl_val;
int mid_val=500;
unsigned int width = 0;        
unsigned int height = 0;        
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;                
int Xmax = 200;

const int speed = 100;
const int In1 = 4;
const int In2 = 5;
const int In3 = 6;      
const int In4 = 7;

void setup() {
 Serial.begin(9600);
 pinMode(In1, OUTPUT);
 pinMode(In2, OUTPUT);
 pinMode(In3, OUTPUT);
 pinMode(In4, OUTPUT);
 pixy.init();
}
void scan()
{
  pixy.ccc.getBlocks();
  width=pixy.ccc.blocks[i].m_width;
  height = pixy.ccc.blocks[i].m_height;
  x= pixy.ccc.blocks[i].m_x;
  y= pixy.ccc.blocks[i].m_y;

}





void Forward()
 {
  Serial.println("Moving Forward");
  analogWrite(In1, speed); // 馬達 A 的 PWM 輸出
  analogWrite(In2, speed); 
  analogWrite(In3, speed); // 馬達 B 的 PWM 輸出
  analogWrite(In4, speed); 
  //digitalWrite(In1, HIGH);
  //digitalWrite(In2, LOW);
  //digitalWrite(In3, HIGH);
  //digitalWrite(In4, LOW);
 }

 void Backward()
 {
  Serial.println("Moving Backward");
  analogWrite(In1, speed); // 馬達 A 的 PWM 輸出
  analogWrite(In2, speed); 
  analogWrite(In3, speed); // 馬達 B 的 PWM 輸出
  analogWrite(In4, speed);
  //digitalWrite(In1, LOW);
  //digitalWrite(In2, HIGH);
  //digitalWrite(In3, LOW);
  //digitalWrite(In4, HIGH);
 
 }

 void Right()
 {
  Serial.println("Moving Right");
  //digitalWrite(In1, LOW);
  //digitalWrite(In2, LOW);
  //digitalWrite(In3, HIGH);
  //digitalWrite(In4, LOW);
  
 }
 void Left()
 {
  Serial.println("Moving Left");
  //digitalWrite(In1, HIGH);
  //digitalWrite(In2, LOW);
  //digitalWrite(In3, LOW);
  //digitalWrite(In4, LOW);
  
 }
 void Freeze()
  {
  Serial.println("Stopping");
  //digitalWrite(In1, LOW);
  //digitalWrite(In2, LOW);
  //digitalWrite(In3, LOW);
  //digitalWrite(In4, LOW);
 }

  void mfront(){
  Serial.println("Moving Forward");
  analogWrite(In1, speed); // 馬達 A 的 PWM 輸出
  analogWrite(In2, speed); 
  analogWrite(In3, speed); // 馬達 B 的 PWM 輸出
  analogWrite(In4, speed); 
  //digitalWrite(In3, HIGH);
  //digitalWrite(In4, LOW);
  //digitalWrite(In1, HIGH);
  //digitalWrite(In2, LOW);
}
 
   void mode1()
{
  while(millis()<5000)
  {
    scan();
    area = width * height;
    maxArea = area + 2000;
    minArea = area + 1000;
  }
  scan();
   sign=pixy.ccc.blocks[i].m_signature;
    if(sign == 1)
    {
    newarea = width * height;
      if (x < Xmin)
      {    
       Left();
       Serial.println(x);
       Serial.println(Xmin);
      }
      else if (x > Xmax)
      {
       Right();
       Serial.println(x);
       Serial.println(Xmax);
      }
      else if(newarea < minArea)
      {
       mfront();
       Serial.println(newarea);
       Serial.println(minArea);
      }
      else if(newarea > maxArea)
      {
       Backward();
       Serial.println(newarea);
       Serial.println(maxArea);
      }
      else
      {
       Freeze();
       Serial.println(newarea);
       Serial.println(maxArea);
      }
      delay(500);
   }
   else
   {
    Freeze();
   }

}
void mode2(){
   if(Serial.available()){
     bl_val = Serial.read();
     Serial.println(bl_val);
   }
   if(bl_val == 'w')
   {
    mfront();
   }
   else if(bl_val == 'a')
   {
    Left();
   }
   else if(bl_val == 'd')
   {
    Right();
   }
   else if(bl_val == 's')
   {
    Backward();
   }
   else
   {
    Forward();
   }
}




 void loop() {
   pot_val = analogRead(A0);
   bl_val  = analogRead(A1);
   Serial.println(pot_val);
     
     if(pot_val<mid_val)
     {
      Serial.println("Mode1 -Follow Mode");
      mode1();
     }
     else
     {
      Serial.println("Bluetooth Mode");
      mode2();
     }
  }
