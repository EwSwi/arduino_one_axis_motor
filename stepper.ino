#include <AccelStepper.h>

const int stepPin = 2;
const int dirPin = 3;
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

int stepsPerMM = 200;
float Z0 = 2180;
float targetZ = 2170;
float current_Z;

float limitUP = 2390;
float limitDOWN = 2150;
bool clockwise = true;

void moveMotor(float targetPosition) {
  myStepper.moveTo(targetPosition);
}

void setup() {
  Serial.begin(9600);
  myStepper.setMaxSpeed(100); 
  myStepper.setAcceleration(500);
}

void loop() {
  myStepper.run();
  current_Z = Z0 + (float)myStepper.currentPosition() / stepsPerMM;
  if (targetZ >= limitDOWN && targetZ <= limitUP) {
    float targetPosition = (targetZ - Z0) * stepsPerMM;
    moveMotor(targetPosition);
  } else {
    myStepper.stop();
    Serial.println("Target position is out of range.");
  }
  Serial.print("Current Z position: ");
  Serial.println(current_Z);
}
