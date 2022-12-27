#pragma once
#include "FastAccelStepper.h"
#include "AVRStepperPins.h" // Only required for AVR controllers

//---------Define if using A4988 or TMC2208---------
#define A4988
//#define TMC2208
#ifdef A4988
  #define EN_PIN 49
  #define MS1_PIN 31
  #define MS2_PIN 32
  #define MS3_PIN 33
#endif
#ifdef TMC2208
  #define UART_PIN -1
#endif
//---------Step and Direction Pins---------
#define STEP_PIN 8
#define DIR_PIN 47
//---------Endstop Switch Pin---------
#define ENDSTOP_PIN 52
//---------Constants---------
#define MICROSTEP_RATIO 16.0
#define STEPS_PER_MM (6.25 * MICROSTEP_RATIO)
#define ENDBOUND_MM 220
#define PRINT_START_POS_MM 60


class StepperManager {
  public:
    void setup();

    void loop();

    void setTarget(float newPos);

    void incrementPosition(float amount);

    void printing_home();

    void printing_setTarget(float newOffsetPos);

  private:
    FastAccelStepperEngine engine = FastAccelStepperEngine();
    FastAccelStepper *stepper = NULL;

    bool homing = true;
    float lastPosition = 0;

    
    void homeStepper();
};