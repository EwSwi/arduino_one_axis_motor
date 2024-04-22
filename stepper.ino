#include <AccelStepper.h>

const int stepPin = 2;
const int dirPin = 3;
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

int stepsPerMM = 200;
float Z0 = 2180;
float targetZ = 2181;
float current_Z = Z0;
float newRefZ;

float limitUP = 2390;
float limitDOWN = 2150;
bool chimneyDetected;

void moveMotor(float targetPosition) {
  myStepper.moveTo(targetPosition);
}

bool checkForChimney() {
  Serial.print("chimney? (y/n): ");


  while (!Serial.available()) {
    delay(10); 
  }
  
  char inputChar = Serial.read(); 
  while (Serial.available()) {
    Serial.read();
  }

  // Process the input character
  if (inputChar == 'y' || inputChar == 'Y') {
    return true; 
  } else if (inputChar == 'n' || inputChar == 'N') {
    return false; 
  } else {
    return false; 
  }
}

void setup() {
  
  myStepper.setAcceleration(2000); 
  myStepper.setMaxSpeed(100);
  Serial.begin(9600);
}

void loop() {
  myStepper.run();
  current_Z = Z0 + (float)myStepper.currentPosition() / stepsPerMM;
  if (!chimneyDetected) 
  {
  chimneyDetected = true;
  if (checkForChimney() == true) {
  myStepper.setMaxSpeed(50);
  myStepper.moveTo(Z0); 
 }
 }
  if (targetZ >= limitDOWN && targetZ <= limitUP) {
    float targetPosition = (targetZ - Z0) * stepsPerMM;
    moveMotor(-targetPosition);
  } else {
    myStepper.stop();
    Serial.println("Target position is out of range.");
  }
  
}
