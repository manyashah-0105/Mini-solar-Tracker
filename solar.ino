
#include <Servo.h>  // servo library

Servo s2;

void setup()
{
  Serial.begin(9600);
  s2.attach(3);
}

void loop()
{
  int s1 = analogRead(A0);
  Serial.println(s1);
  delay(10);

  if (s1 > 500)
  {
    s2.write(0);
  }

  if (s1 < 500)
  {
    s2.write(25);
    delay(50);
  }
}
