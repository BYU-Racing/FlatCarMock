#include "FlatCar.h"
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CORE_CAN;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> AUX_CAN;


bool canSniffState = false;
int USER_INPUT = 0;
float SPEED = 0.0;
float RPS = 0.0;
unsigned long speedUpdate = 0;
int brakeVal = 0;
int throttleVal = 0;
float targetRunTime = 0.0;
unsigned long runTime = 0;
unsigned long currentTime = 0;
unsigned long DIGITAL_UPDATE = 0;
unsigned long digitalElapsed = 0;
unsigned long digitalLast = 0;
unsigned long WHEEL_UPDATE = 0;
unsigned long wheelElapsed = 0;
unsigned long wheelLast = 0;
unsigned long ANALOG_UPDATE = 0;
unsigned long analogElapsed = 0;
unsigned long analogLast = 0;
long randomAnalog = 0;
unsigned long CAN_UPDATE = 0;
unsigned long canElapsed = 0;
unsigned long canLast = 0;
unsigned long CAN_SNIFF_UPDATE = 0;
unsigned long canSniffElapsed = 0;
unsigned long canSniffLast = 0;
bool wheelStatus = false;

const int WHEEL_SPEED_PINS[] = {2, 3, 4, 5};
int START_SWITCH_PIN = 26;
int BRAKE_1_PIN = 27;
int TRACTIVE_PIN = 9;
int THROTTLE_1_PIN = 37;
int THROTTLE_2_PIN = 38;
const int NUM_WHEEL_SPEED_PINS = sizeof(WHEEL_SPEED_PINS) / sizeof(WHEEL_SPEED_PINS[0]);


void canSetup() {
    CORE_CAN.begin();
    CORE_CAN.setBaudRate(250000);
    AUX_CAN.begin();
    AUX_CAN.setBaudRate(250000);
}


void pinSetup() {
    for (int i = 0; i < NUM_WHEEL_SPEED_PINS; i++) {
        pinMode(WHEEL_SPEED_PINS[i], OUTPUT);
        Serial.print("WHEEL SPEED PIN ");
        Serial.print(WHEEL_SPEED_PINS[i]);
        Serial.println(" INITIALIZED");
    }

    pinMode(START_SWITCH_PIN, OUTPUT);
    Serial.print("SWITCH PIN: ");
    Serial.print(START_SWITCH_PIN);
    Serial.println(" INITIALIZED");
    
    pinMode(BRAKE_1_PIN, OUTPUT);
    Serial.print("BRAKE 1 PIN ");
    Serial.print(BRAKE_1_PIN);
    Serial.println(" INITIALIZED");
    
    pinMode(TRACTIVE_PIN, OUTPUT);
    Serial.print("TRACTIVE PIN ");
    Serial.print(TRACTIVE_PIN);
    Serial.println(" INITIALIZED");
    
    pinMode(THROTTLE_1_PIN, OUTPUT);
    Serial.print("THROTTLE 1 PIN ");
    Serial.print(THROTTLE_1_PIN);
    Serial.println(" INITIALIZED");
    
    pinMode(THROTTLE_2_PIN, OUTPUT);
    Serial.print("THROTTLE 2 PIN ");
    Serial.print(THROTTLE_2_PIN);
    Serial.println(" INITIALIZED");

    Serial.println("ALL PINS INITIALIZED");
}

void canSniff() {
    CAN_message_t msg;
    if (CORE_CAN.read(msg)) {
        Serial.print("[CORE CAN] ID: ");
        Serial.print(msg.id);
        Serial.print(" LENGTH: ");
        Serial.print(msg.len);
        Serial.print(" DATA: ");
        for (uint8_t i = 0; i < msg.len; i++) {
            Serial.print(msg.buf[i]);
            Serial.print(" ");
        }
        Serial.println();
    }

    if (AUX_CAN.read(msg)) {
        Serial.print("[AUX CAN] ID: ");
        Serial.print(msg.id);
        Serial.print(" LENGTH: ");
        Serial.print(msg.len);
        Serial.print(" DATA: ");
        for (uint8_t i = 0; i < msg.len; i++) {
            Serial.print(msg.buf[i]);
            Serial.print(" ");
        }
        Serial.println();
    }
    canSniffLast = millis();
}

void menuInit() {
    Serial.println("WELCOME TO FLATCAR");
    Serial.println("START MENU:");
    Serial.println("1) STATIC VALUE TEST");
    Serial.println("2) VARIABLE VALUE TEST");
    Serial.println("3) RANDOM VALUE TEST");
    Serial.println("4) RUN SIM");
    Serial.println("5) EXIT");
}

void menuSelect() {
    menuInit();
    
    Serial.println("WAITING FOR INPUT");
    Serial.print("SELECTION: ");
    while (!Serial.available()) {
        // Wait for serial input
    }
    USER_INPUT = Serial.read() - '0';
    Serial.println(USER_INPUT);
    
    Serial.print("TARGET RUN TIME (MIN): ");
    while (!Serial.available()) {
        // Wait for serial input
    }
    targetRunTime = Serial.parseFloat();
    Serial.println(targetRunTime);

    Serial.print("TOGGLE CAN SNIFF (1/0): ");
    while (!Serial.available()) {
        // Wait for serial input
    }
    canSniffState = (Serial.read() == '1');
    Serial.println(canSniffState);
    
    switch (USER_INPUT) {
        case 1:
            Serial.println("SELECTED: STATIC VALUE TEST");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.println(targetRunTime);
            break;
        case 2:
            Serial.println("SELECTED: VARIABLE VALUE TEST");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.println(targetRunTime);
            break;
        case 3:
            Serial.println("SELECTED: RANDOM VALUE TEST");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.println(targetRunTime);
            break;
        case 4:
            Serial.println("SELECTED: RUN SIM");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.println(targetRunTime);
            break;
        case 5:
            Serial.println("EXITING...");
            break;
        default:
            Serial.println("INVALID CHOICE");
            break;
    }
}

void runPrograms() {
    switch (USER_INPUT) {
        case 1:
            Serial.println(">>>STARTING STATIC VALUE TEST<<<");
            staticTest();
            break;
        case 2:
            Serial.println(">>>STARTING VARIABLE VALUE TEST<<<");
            variableTest();
            break;
        case 3:
            Serial.println(">>>STARTING RANDOM VALUE TEST<<<");
            randomTest();
            break;
        case 4:
            simTest();
            break;
    }
}

void startSequence() {
    digitalWrite(START_SWITCH_PIN, HIGH);
    digitalWrite(TRACTIVE_PIN, HIGH);
}

void motorCAN() {
    return;
}

void BMSCAN() {
    return;
}

void staticTest() {
    startSequence();
    for (int i = 0; i < 4; i++) {
        digitalWrite(WHEEL_SPEED_PINS[i], HIGH);
    }
    analogWrite(BRAKE_1_PIN, 127);
    analogWrite(THROTTLE_1_PIN, 127);
    analogWrite(THROTTLE_2_PIN, 127);
    
    Serial.println("<<<STATIC TEST COMPLETE>>>");
    while (Serial.available()) {
        // wait for Serial input
    }
}

void updateTimes() {
    // Update all times to get current elapse times
        currentTime = millis();
        digitalElapsed = currentTime - digitalLast;
        analogElapsed = currentTime - analogLast;
        wheelElapsed = currentTime - wheelLast;
        canElapsed = currentTime - canLast;
        canSniffElapsed = currentTime - canSniffLast;

}

void updateRates() {
    DIGITAL_UPDATE = 1000;
    ANALOG_UPDATE = 100;
    WHEEL_UPDATE = 350; // Wheel update value for 10 mph initial start
    CAN_UPDATE = 100;
    brakeVal = 0;
    throttleVal = 0;
    SPEED = 10;
    speedUpdate = 5000;
    CAN_SNIFF_UPDATE = 15;
}

void variableTest() {
    startSequence();
    updateRates();
    runTime = currentTime + (targetRunTime * 60000);

    updateTimes();

    Serial.println("VARIABLE TEST INITALIZED");
    Serial.print("TARGET_RUN_TIME: ");
    Serial.println(targetRunTime);
    Serial.print("RUN_TIME: ");
    Serial.println(runTime);
    Serial.print("CURRENT_TIME: ");
    Serial.println(currentTime);
    
    while (currentTime < runTime) {

        updateTimes();

        if (canSniffElapsed >= CAN_SNIFF_UPDATE && canSniffState) {
            canSniff();
            canLast = millis();
        }

        if (currentTime >= speedUpdate) {
            SPEED++;
            RPS = (SPEED * 1.4667) / (3.141592653589793 * 1.33333333);
            WHEEL_UPDATE = 1 / (RPS / 10);
            if (SPEED == 120) {
                SPEED = 0;
            }
            speedUpdate += 5000;
        }

        if (digitalElapsed > DIGITAL_UPDATE) {
            digitalWrite(TRACTIVE_PIN, HIGH);
            digitalWrite(START_SWITCH_PIN, HIGH);

            digitalLast = millis();               
        }

        if (analogElapsed > ANALOG_UPDATE) {
            // Writes values to pins
            analogWrite(BRAKE_1_PIN, brakeVal);
            analogWrite(THROTTLE_1_PIN, throttleVal);
            analogWrite(THROTTLE_2_PIN, 255 - throttleVal);
            
            // Incriment +1 each cycle
            brakeVal++;
            throttleVal++;

            // Resets values at 255
            if (brakeVal == 255) {
                brakeVal = 0;
            }
            if (throttleVal == 255) {
                throttleVal = 0;
            }

            // Updates last run time
            analogLast = millis();
        }
        if (wheelElapsed > WHEEL_UPDATE) {
            if (wheelStatus == 0) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], HIGH);
                }
                wheelStatus = 1;
            }
            if (wheelStatus == 1) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], LOW);
                }
                wheelStatus = 0;
            }
            wheelLast = millis();
        }

        // if (canElapsed > CAN_UPDATE) {

        //     CAN_LAST = millis();
        // }
        // else {
        //     CURRENT_TIME = millis();
        // }
    }
}

void randomTest() {
    startSequence();
    updateRates();
    runTime = currentTime + (targetRunTime * 60000);

    updateTimes();

    Serial.println("VARIABLE TEST INITALIZED");
    Serial.print("TARGET_RUN_TIME: ");
    Serial.println(targetRunTime);
    Serial.print("RUN_TIME: ");
    Serial.println(runTime);
    Serial.print("CURRENT_TIME: ");
    Serial.println(currentTime);

    while (currentTime < runTime) {

        updateTimes();

        if (canSniffElapsed >= CAN_SNIFF_UPDATE && canSniffState) {
            canSniff();
            Serial.println("CAN SNIFFED!");
            canLast = millis();
        }

        if (digitalElapsed > DIGITAL_UPDATE) {
            digitalWrite(TRACTIVE_PIN, HIGH);
            digitalWrite(START_SWITCH_PIN, HIGH);

            digitalLast = millis();
        }
        if (analogElapsed > ANALOG_UPDATE) {
            randomAnalog = random(0, 255);
            
            analogWrite(BRAKE_1_PIN, randomAnalog);

            randomAnalog = random(0, 255);
            analogWrite(THROTTLE_1_PIN, randomAnalog);
            analogWrite(THROTTLE_2_PIN, 255 - randomAnalog);
            
            analogLast = millis();
        }
        if (wheelElapsed > WHEEL_UPDATE) {
                if (wheelStatus == 0) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], HIGH);
                }
                wheelStatus = 1;
            }
            if (wheelStatus == 1) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], LOW);
                }
                wheelStatus = 0;
            }
            wheelLast = millis();
        }
        Serial.println("<<<RANDOM TEST CYCLE COMPLETE>>>");
        Serial.println(currentTime / 1000);

        // if (canElapsed > CAN_UPDATE) {

        //     CAN_LAST = millis();
        // }
        // else {
        //     CURRENT_TIME = millis();
        // }
    }
}

void simTest() {
    startSequence();
    return;
}