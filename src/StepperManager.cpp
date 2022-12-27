#include "StepperManager.h"
#include "PCBPrinter.h"

void StepperManager::setup() {
    #ifdef A4988
        pinMode(MS1_PIN, OUTPUT);
        pinMode(MS2_PIN, OUTPUT);
        pinMode(MS3_PIN, OUTPUT);
        digitalWrite(MS1_PIN, HIGH);
        digitalWrite(MS2_PIN, HIGH);
        digitalWrite(MS3_PIN, HIGH);
    #endif

    pinMode(ENDSTOP_PIN, INPUT);

    engine.init();
    stepper = engine.stepperConnectToPin(STEP_PIN);
    stepper->setDirectionPin(DIR_PIN, true);

    stepper->setSpeedInUs(1200); //Slow speed for homing
    stepper->setAcceleration(50000);
    
    homeStepper();
}

void StepperManager::loop() {
    if (homing) {
        int endstopPinState = digitalRead(ENDSTOP_PIN);
        if (endstopPinState == HIGH) {
            stepper->forceStop();
            homing = false;
            stepper->setSpeedInUs(100);
            stepper->setCurrentPosition(0);

            PCBPrinter::this_PCBPrinter->switchState(0);
        }
    }
}

void StepperManager::setTarget(float newPos) {
    if (newPos > ENDBOUND_MM) newPos = ENDBOUND_MM;
    if (newPos < 0) newPos = 0;
    lastPosition = newPos;
    (*stepper).moveTo((int) (newPos * STEPS_PER_MM));
}

void StepperManager::incrementPosition(float amount) {
    setTarget(lastPosition + amount);
}


void StepperManager::homeStepper() {
    stepper->moveTo(-50000);
    homing = true;
}


void StepperManager::printing_home() {
    setTarget(PRINT_START_POS_MM);
}

void StepperManager::printing_setTarget(float newOffsetPos) {
    setTarget(PRINT_START_POS_MM + newOffsetPos);
}