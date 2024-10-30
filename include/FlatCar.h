#ifndef FLATCAR_H
#define FLATCAR_H

extern bool canSniffState;
extern int USER_INPUT;
extern float SPEED;
extern float RPS;
extern unsigned long speedUpdate;
extern int brakeVal;
extern int throttleVal;
extern float targetRunTime; // In minutes when selected by the user
extern unsigned long runTime; // Target run time of user in millis
extern unsigned long currentTime;
extern unsigned long DIGITAL_UPDATE; // How often Digital sensors should be updated
extern unsigned long digitalElapsed;
extern unsigned long digitalLast;
extern unsigned long WHEEL_UPDATE;
extern unsigned long wheelElapsed;
extern unsigned long wheelLast;
extern unsigned long ANALOG_UPDATE;
extern unsigned long analogElapsed;
extern unsigned long analogLast;
extern long randomAnalog;
extern unsigned long CAN_UPDATE;
extern unsigned long canElapsed;
extern unsigned long canLast;
extern unsigned long CAN_SNIFF_UPDATE;
extern unsigned long canSniffElapsed;
extern unsigned long canSniffLast;

extern bool wheelStatus; // Used to store current wheel sensor status

extern const int WHEEL_SPEED_PINS[];
extern int START_SWITCH_PIN;
extern int BRAKE_1_PIN;
extern int TRACTIVE_PIN;
extern int THROTTLE_1_PIN;
extern int THROTTLE_2_PIN;

extern const int NUM_WHEEL_SPEED_PINS;


void menuSelect();
void canSetup();
void pinSetup();
void canSniff();
void menuInit();
void runPrograms();
void staticTest();
void variableTest();
void randomTest();
void simTest();

#endif
