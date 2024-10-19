#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "FlatCar.h"

void setup() {
  return;
  Serial.begin(9600);
  Serial.println("Serial Port Intialized");
  canSetup();
  pinSetup();
}

void loop() {

  menuSelect();
  runPrograms();

  return;
}