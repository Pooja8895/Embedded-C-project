// Arduino Solar Tracker

// Including The Servo Header File
#include <Servo.h>

Servo Horizontal;
Servo Vertical;

// Setting Up Initial Position For Horizontal And Vertical Servos

int ServoOH = 90;
int ServoOV = 90;


// Naming the LDR Pin Configuration

int ldrlt = 0;
int ldrrt = 1;
int ldrld = 2;
int ldrrd = 3;

// Setting Up the Function

void setup()
{
  Serial.begin(9600);
  Horizontal.attach(6);
  Vertical.attach(7);
  Horizontal.write(90);
  Vertical.write(90);
  
}

void loop()
{
  int LeftTop = analogRead(ldrlt);
  int RightTop = analogRead(ldrrt);
  int LeftDown = analogRead(ldrld);
  int RightDown = analogRead(ldrrd);
  
  // Reading The Potentiometer Values
 
 int dtime = analogRead(4)/20;
int tol = analogRead(5)/4;

// Finding The Average Value

int Avg_Top = (LeftTop+RightTop)/2;
int Avg_Down = (LeftDown+RightDown)/2;
int Avg_Left = (LeftDown+LeftTop)/2;
int Avg_Right = (RightDown+RightTop)/2;

int Diff_Vert = Avg_Top - Avg_Down;
int Diff_Hor = Avg_Left - Avg_Right;

 //Checking If the Difference in the Vertical Tolerance else Change Vertical Angle

if(-1*tol > Diff_Vert || Diff_Vert > tol)
{
  if(Avg_Top > Avg_Down)
  {
    ServoOV = --ServoOV;
    if(ServoOH < 0)
    {
      ServoOH =0;
    }
  }
  else if (Avg_Top < Avg_Down)
  {
    ServoOV = ++ServoOV;
    if(ServoOV > 180 )
    {
      ServoOV = 180;
    }
  }
  Vertical.write(ServoOV);
}

//Check If the Difference is in The Horizontal Tolerance Level else Change the Horizontal Angle

if (-1*tol > Diff_Hor || Diff_Hor > tol)
{
  
  if(Avg_Left > Avg_Right)
  {
    ServoOH = --ServoOH;
    if(ServoOH < 0 )
    {
      ServoOH = 0;
    }
  }
  else if(Avg_Left < Avg_Right)
  {
    ServoOH = ++ServoOH;
    if(ServoOH > 180)
    {
      ServoOH = 180;
    }
  }
  else if(Avg_Left == Avg_Right)
  {
  }
  Horizontal.write(ServoOH);
delay(100);
}

