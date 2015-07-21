#include <math.h>
#include <Servo.h>
#define SERIAL_BPS 115200
int fanpin = 11;
int fanspeed;
int temp1;
int temp2;
int target = 50;
int dift;
int error;
int pwmout;
Servo myservo;

void setup() {
  Serial.begin(SERIAL_BPS);
  myservo.attach(9);
}

void loop() {
  Serial.println(TCCR0A);
  Serial.println(TCCR0B);
  Serial.println(OCR0A);
  temp1 = analogRead(A1);
  
  temp2 = analogRead(A2);
  dift = (temp2 - temp1);
  error = target - dift;
  /*
   * Individual commented out serial prints,
   * are usefull when trying to trouble shoot code
   */
  //Serial.print("Temp T2: ");
  //Serial.println(temp2);
  //Serial.print("Temp T1: ");
  //Serial.println(temp1);
  //Serial.print("Dift: ");
  //Serial.println(dift);
  //Serial.print("Error: ");
  //Serial.println(error);
  /*
   * if the error is too high, let's say it just started up,
   * turn the fan on all the way,
   * and open the damper all the way,
   * then wait 20 seconds.
   */
  if (error < -15)
  {
    myservo.write(180);
    analogWrite(11, 255);
    delay(20000);
  }
  /* if the error is less than 0 open the damper,
   *  then when the damper opens all the way,
   *  turn on the fan at a mapped speed,
   *  around the set point.
   */
  if (error < 0) 
  {
    myservo.write(myservo.read() + 1);
    delay(400);
    if (myservo.read() == 180)
    {
      delay(500);
      fanspeed = map(error, 0, -20, 0, 255);
      analogWrite(11, fanspeed);
      myservo.write(180);
    }

  }
  /* if the error is greater than 0 turn the fan off,
   * and open the damper.
   */
  if (error > 0)
  {
    analogWrite(11, 0);
    {
      myservo.write(myservo.read() - 1);
      delay(400);
    }
  }
  /*if the error is equal to 0,
   * do nothing
   */
if (error == 0)
{
  
}
}

