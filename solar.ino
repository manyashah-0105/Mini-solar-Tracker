#include <Servo.h>

Servo panelServo;

// Pins
const int LDR_LEFT  = A0;
const int LDR_RIGHT = A1;
const int SERVO_PIN = 5;      // servo signal wire on D5

// Servo settings
int pos = 90;                 // start in the middle
const int POS_MIN = 20;       // minimum angle
const int POS_MAX = 160;      // maximum angle

// Tracking settings
const int tolerance = 25;     // ignore small differences (stops jitter)
const int stepSize  = 1;      // degrees moved each step
const int loopDelay = 40;     // ms between steps (higher = slower)

// Read an LDR several times and average it for a stable value
int readAverage(int pin) {
  long total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(pin);
    delay(2);
  }
  return total / 10;
}

void setup() {
  Serial.begin(9600);
  panelServo.attach(SERVO_PIN);
  panelServo.write(pos);
  delay(1000);                // let the servo settle
}

void loop() {
  int left  = readAverage(LDR_LEFT);
  int right = readAverage(LDR_RIGHT);
  int diff  = left - right;

  if (abs(diff) > tolerance) {
    if (diff > 0) {
      pos += stepSize;        // more light on left, so turn left
    } else {
      pos -= stepSize;        // more light on right, so turn right
    }
    pos = constrain(pos, POS_MIN, POS_MAX);
    panelServo.write(pos);
  }

  Serial.print("Left: ");    Serial.print(left);
  Serial.print("  Right: "); Serial.print(right);
  Serial.print("  Angle: "); Serial.println(pos);

  delay(loopDelay);
}
