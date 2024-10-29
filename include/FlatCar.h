#ifndef FLATCAR_H
#define FLATCAR_H

extern bool CAN_SNIFF;
extern char USER_INPUT;
extern float SPEED;
extern float RPS;
extern unsigned long SPEED_UPDATE;
extern int BRAKE_VAL;
extern int THROTTLE_VAL;
extern float TARGET_RUN_TIME; // In minutes when selected by the user
extern unsigned long RUN_TIME; // Target run time of user in millis
extern unsigned long CURRENT_TIME;
extern unsigned long DIGITAL_UPDATE; // How often Digital sensors should be updated
extern unsigned long DIGITAL_ELAPSED;
extern unsigned long DIGITAL_LAST;
extern unsigned long WHEEL_UPDATE;
extern unsigned long WHEEL_ELAPSED;
extern unsigned long WHEEL_LAST;
extern unsigned long ANALOG_UPDATE;
extern unsigned long ANALOG_ELAPSED;
extern unsigned long ANALOG_LAST;
extern long RANDOM_ANALOG;
extern unsigned long CAN_UPDATE;
extern unsigned long CAN_ELAPSED;
extern unsigned long CAN_LAST;

extern bool WHEEL_STATUS; // Used to store current wheel sensor status

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
