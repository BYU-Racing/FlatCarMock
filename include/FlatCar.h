#ifndef FLATCAR_H
#define FLATCAR_H

bool CAN_SNIFF;
char VAL;
float SPEED;
float RPS;
unsigned long SPEED_UPDATE;
int BRAKE_VAL;
int THROTTLE_VAL;
float TARGET_RUN_TIME; // In minutes when selected by the user
unsigned long RUN_TIME; // Target run time of user in millis
unsigned long CURRENT_TIME;
unsigned long DIGITAL_UPDATE; // How often Digital sensors should be updated
unsigned long DIGITAL_ELAPSED;
unsigned long DIGITAL_LAST;
unsigned long WHEEL_UPDATE;
unsigned long WHEEL_ELAPSED;
unsigned long WHEEL_LAST;
unsigned long ANALOG_UPDATE;
unsigned long ANALOG_ELAPSED;
unsigned long ANALOG_LAST;
long RANDOM_ANALOG;
unsigned long CAN_UPDATE;
unsigned long CAN_ELAPSED;
unsigned long CAN_LAST;

bool j; // Used to store current wheel sensor status

const int WHEEL_SPEED_PINS[] = {2, 3, 4, 5};
constexpr int START_SWITCH_PIN = 6;
constexpr int BRAKE_1_PIN = A0;
constexpr int TRACTIVE_PIN = 9;
constexpr int THROTTLE_1_PIN = A2;
constexpr int THROTTLE_2_PIN = A3;

const int NUM_WHEEL_SPEED_PINS = sizeof(WHEEL_SPEED_PINS) / sizeof(WHEEL_SPEED_PINS[0]);


char menuSelect();
void canSetup();
void pinSetup();
void canSniff();
void menuInit();
char runPrograms();
void staticTest();
void variableTest();
void randomTest();
void simTest();

#endif
