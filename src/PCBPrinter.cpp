#include "PCBPrinter.h"

PCBPrinter* PCBPrinter::this_PCBPrinter;


PrinterPositionManager PCBPrinter::ppm;
UserInterface PCBPrinter::uim;
StepperManager PCBPrinter::sm;

PCBPrinter::PCBPrinter() {
    this_PCBPrinter = this;
}

void PCBPrinter::setup() {
    ppm.setup();
    uim.setup();

    //Enter homing state then home by setting up Stepper Manager
    switchState(1);
    sm.setup();

    Serial.begin(9600);

    pinMode(PAPER_SENS_OUT, OUTPUT);
    digitalWrite(PAPER_SENS_OUT, HIGH);

    attachInterrupt(digitalPinToInterrupt(OPTENCP1), int_OPT_ENCP1, RISING);
    attachInterrupt(digitalPinToInterrupt(USR_BTN), int_USR_BTN, RISING);
}

void PCBPrinter::loop() {
    ppm.loop();

    //After print position updated, check if printing then move stepper
    if (state == 3) {
        sm.printing_setTarget(ppm.getPaperPosition());
    }

    uim.loop();
    sm.loop();
}

void PCBPrinter::switchState(int newState) {
    state = newState;
    switch (newState)
    {
    case 0:
        //Enter idle state
        //Probably means it's finished homing, printing and ready to print.

        uim.setText("Ready! (idle/0) ");
        //Make printer think no paper is inserted
        digitalWrite(PAPER_SENS_OUT, HIGH);
        //Re-init PPM Class
        ppm = PrinterPositionManager();
        //Set to idle position (END)
        sm.setTarget(9999999);

        break;
    case 1:
        //Enter busy state

        uim.setText("Busy! (1)       ");

        break;
    case 2:
        //Print about to start state

        uim.setText("Wait to start(2)");
        digitalWrite(PAPER_SENS_OUT, LOW);
        sm.printing_home();
        ppm.printStarted();

        break;
    case 3:
        //Printing state (Listening to printer position data)
        
        uim.setText("Printing! (3)   ");

        break;
    default:
        break;
    }
}

void PCBPrinter::int_OPT_ENCP1() {
    ppm.p1Rising();
}

void PCBPrinter::int_USR_BTN() {
    uim.buttonPressedInterrupt();
}
