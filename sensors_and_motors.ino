#include <AccelStepper.h>

#define HALFSTEP 8 

// defines pins numbers
const int buzzer = 13;
const int redLED = 4;
const int blueLED = 5;
const int trigPin = 7;
const int echoPin = 6;     

const int mtr1Pin1 = 8;     // IN1 on the ULN2003 driver 1
const int mtr1Pin2 = 9;     // IN2 on the ULN2003 driver 1
const int mtr1Pin3 = 10;     // IN3 on the ULN2003 driver 1
const int mtr1Pin4 = 11;     // IN4 on the ULN2003 driver 1

 

const int detectionThreshold = 50;

long duration;
int distance;
int data=0;
int IsRecyclable;
int frontDistance;
int backDistance;

AccelStepper stepper1(HALFSTEP, mtr1Pin1, mtr1Pin3, mtr1Pin2, mtr1Pin4);
 

void setup() {
  Serial.begin(9600);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(mtr1Pin1, OUTPUT);
  pinMode(mtr1Pin2, OUTPUT);
  pinMode(mtr1Pin3, OUTPUT);
  pinMode(mtr1Pin4, OUTPUT);


  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);


  
}


void loop() {
  
  frontDistance = measureFrontDistance();
  Serial.println(frontDistance);
  if (frontDistance <= detectionThreshold) {
    
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);  
    
       while(Serial.available())
        {
          IsRecyclable = Serial.read();
           
        }

        if(IsRecyclable = '1'){
        // Code for moving motors - recyled item

          
                 stepper1.setMaxSpeed(1000.0);
                 stepper1.setAcceleration(100.0);
                 stepper1.setSpeed(200);
                  stepper1.moveTo(20000);


                if (stepper1.distanceToGo() == 0) {
                      stepper1.moveTo(-stepper1.currentPosition());
                   }
                  stepper1.run();

            
          
          }

          else if (IsRecyclable = '0'){
         // Code for moving motors - garbagee

         if (stepper1.distanceToGo() == 0) {
                      stepper1.moveTo(-stepper1.currentPosition());
                   }
                  stepper1.run();
            stepper1.setMaxSpeed(1000.0);
            stepper1.setAcceleration(100.0);
            stepper1.setSpeed(200);
            stepper1.moveTo(20000);
                  
          
    
  }
  
  else {
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);   
  }

   delay(2500);

}
}

int measureFrontDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  return distance;
}
