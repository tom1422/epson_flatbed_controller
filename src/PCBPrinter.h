#pragma once
#include <Arduino.h>
#include "PrinterPositionManager.h"
#include "UserInterface.h"
#include "StepperManager.h"

class PCBPrinter {
    public:

        static PCBPrinter* this_PCBPrinter;

        //CAN ONLY BE 1 STATIC INSTANCE OF THE FOLLOWING CLASSES
        static PrinterPositionManager ppm;
        static UserInterface uim;
        static StepperManager sm;
        
        int state = -1; //-1-undefined, 0-idle, 1-busy(homing_or_booting), 2-waiting_to_start, 3-printing(listening)

        PCBPrinter();

        void setup();

        void loop();

        void switchState(int newState);

        static void int_OPT_ENCP1();

        static void int_USR_BTN();

};