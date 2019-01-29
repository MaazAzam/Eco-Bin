#include <AccelStepper.h>

#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

const int mtr1Pin1 = 8;     // IN1 on the ULN2003 driver 1
const int mtr1Pin2 = 9;     // IN2 on the ULN2003 driver 1
const int mtr1Pin3 = 10;     // IN3 on the ULN2003 driver 1
const int mtr1Pin4 = 11;     // IN4 on the ULN2003 driver 1

const int blueLED = 5;
const int redLED = 4;

const int echoPin = 6;
const int trigPin = 7;

int distance;

AccelStepper stepper1(HALFSTEP, mtr1Pin1, mtr1Pin3, mtr1Pin2, mtr1Pin4);

void setup() {
  // put your setup code here, to run once:

  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(400);
}

void loop() {

   digitalWrite(blueLED, HIGH);
 
 if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());

    digitalWrite(blueLED, LOW);
  }
  
  stepper1.run();

}
