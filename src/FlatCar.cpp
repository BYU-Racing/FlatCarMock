#include "FlatCar.h"
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
// Define defintions here


void canSetup() {
    Serial.begin(9600);
    can1.begin();
    can1.setBaudRate(500000);
    Serial.println("CAN BUS INITALIZED");
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

void menuInit() {
    Serial.println("WELCOME TO FLATCAR");
    Serial.println("START MENU:");
    Serial.println("1) STATIC VALUE TEST");
    Serial.println("2) VARIABLE VALUE TEST");
    Serial.println("3) RANDOM VALUE TEST");
    Serial.println("4) RUN SIM");
    Serial.println("5) EXIT");
}

char menuSelect() {
    menuInit();
    Serial.println("WAITING FOR INPUT");
    Serial.print("SELECTION: ");
    while (!Serial.available()) {
        // Wait for serial input
    }
    char VAL = Serial.read();
    Serial.print("TARGET RUN TIME (MIN): ");
        while (!Serial.available()) {
        // Wait for serial input
    }
    float RUN_TIME = Serial.read();
    switch (VAL) {
        case '1':
            Serial.println("SELECTED: STATIC VALUE TEST");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.print(RUN_TIME);
            break;
        case '2':
            Serial.println("SELECTED: VARIABLE VALUE TEST");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.print(RUN_TIME);
            break;
        case '3':
            Serial.println("SELECTED: RANDOM VALUE TEST");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.print(RUN_TIME);
            break;
        case '4':
            Serial.println("SELECTED: RUN SIM");
            Serial.print("TARGET RUN TIME (MIN): ");
            Serial.print(RUN_TIME);
            break;
        case '5':
            Serial.println("EXITING...");
            break;
        default:
            Serial.println("INVALID CHOICE");
            break;
    }
}

char runPrograms() {
    switch (VAL) {
        case '1':
            staticTest();
        case '2':
            variableTest();
        case '3':
            randomTest();
        case '4':
            simTest();
    }
}

void startSequence() {
    digitalWrite(START_SWITCH_PIN, HIGH);
    digitalWrite(TRACTIVE_PIN, HIGH);
}

void staticTest() {
    startSequence();
    for (int i = 0; i < 4; i++) {
        digitalWrite(WHEEL_SPEED_PINS[i], HIGH);
    }
    analogWrite(BRAKE_1_PIN, 127);
    analogWrite(THROTTLE_1_PIN, 127);
    analogWrite(THROTTLE_2_PIN, 127);
    
    Serial.println("STATIC TEST COMPLETE");
    while (Serial.available()) {
        // wait for Serial input
    }
}

void updateTimes() {
    // Update all times to get current elapse times
        CURRENT_TIME = millis();
        DIGITAL_ELAPSED = CURRENT_TIME - DIGITAL_LAST;
        ANALOG_ELAPSED = CURRENT_TIME - ANALOG_LAST;
        WHEEL_ELAPSED = CURRENT_TIME - WHEEL_LAST;
        CAN_ELAPSED = CURRENT_TIME - CAN_LAST;

}

void variableTest() {
    startSequence();
    // DIGITAL_UPDATE = 100;
    ANALOG_UPDATE = 100;
    // WHEEL_UPDATE = SPEED (ADD CONSTANT TO CONVERT FROM MPH TO DIGITAL READ RATE)
    CAN_UPDATE = 100;
    BRAKE_VAL = 0;
    THROTTLE_VAL = 0;
    
    while (CURRENT_TIME < RUN_TIME) {

        updateTimes();

        // if (DIGITAL_ELAPSED > DIGITAL_UPDATE) {

        //     DIGITAL_LAST = millis();
        // }
        if (ANALOG_ELAPSED > ANALOG_UPDATE) {
            // Writes values to pins
            analogWrite(BRAKE_1_PIN, BRAKE_VAL);
            analogWrite(THROTTLE_1_PIN, THROTTLE_VAL);
            analogWrite(THROTTLE_2_PIN, 255 - THROTTLE_VAL);
            
            // Incriment +1 each cycle
            BRAKE_VAL++;
            THROTTLE_VAL++;

            // Resets values at 255
            if (BRAKE_VAL = 255) {
                BRAKE_VAL = 0;
            }
            if (THROTTLE_VAL = 255) {
                THROTTLE_VAL = 0;
            }

            // Updates last rut time
            ANALOG_LAST = millis();
        }
        if (WHEEL_ELAPSED > WHEEL_UPDATE) {
            if (j = 0) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], HIGH);
                }
                j = 1;
            }
            if (j = 1) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], LOW);
                }
                j = 0;
            }
            WHEEL_LAST = millis();
        }
        if (CAN_ELAPSED > CAN_UPDATE) {

            CAN_LAST = millis();
        }
        else {
            CURRENT_TIME = millis();
        }
    }
}

void randomTest() {
    startSequence();
    while (CURRENT_TIME < RUN_TIME) {

        updateTimes();

        if (DIGITAL_ELAPSED > DIGITAL_UPDATE) {

            DIGITAL_LAST = millis();
        }
        if (ANALOG_ELAPSED > ANALOG_UPDATE) {
            RANDOM_ANALOG = random(0, 255);
            
            analogWrite(BRAKE_1_PIN, RANDOM_ANALOG);

            RANDOM_ANALOG = random(0, 255);
            analogWrite(THROTTLE_1_PIN, RANDOM_ANALOG);
            analogWrite(THROTTLE_2_PIN, 255 - RANDOM_ANALOG);
            
            ANALOG_LAST = millis();
        }
        if (WHEEL_ELAPSED > WHEEL_UPDATE) {
                if (j = 0) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], HIGH);
                }
                j = 1;
            }
            if (j = 1) {
                for (int i = 0; i < 4; i++) {
                    digitalWrite(WHEEL_SPEED_PINS[i], LOW);
                }
                j = 0;
            }
            WHEEL_LAST = millis();
        }
        if (CAN_ELAPSED > CAN_UPDATE) {

            CAN_LAST = millis();
        }
        else {
            CURRENT_TIME = millis();
        }
    }
}

void simTest() {
    startSequence();
    return;
}