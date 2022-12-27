#include "PrinterPositionManager.h"
#include "PCBPrinter.h"

void PrinterPositionManager::setup() {
    pinMode(OPTENCP1, INPUT);
    pinMode(OPTENCP2, INPUT);
}

void PrinterPositionManager::loop() {
    monitorPatterns();
}

void PrinterPositionManager::p1Rising() {
    int p2 = digitalRead(OPTENCP2);
    if (p2 == HIGH) {
    //Both are high, P2 is leading (clockwise)
    counts += 1;
    totalCounts += 1;
    } else {
    //P1 is leading (anticlockwise)
    counts -= 1;
    totalCounts -= 1;
    }
}

void PrinterPositionManager::printStarted() {
    printStartRequested = true;      
}

float PrinterPositionManager::getPaperPosition() {
    return (totalCounts*(0.01763888888));
}

void PrinterPositionManager::monitorPatterns() {
    //Every 50 ms update velocity
    if ((lastAlgoUpdate + 50) < millis()) {
        lastAlgoUpdate = millis();

        float velocity = counts;
        counts = 0;

        //Serial.println("/*" + String(totalCounts) + "," + String(velocity) + "," + printStartRequested + "*/");

        if (printStartRequested) {
            //Waiting for printer to start up completely. First detect forward motion stops. 
            if (!initialLeapOver) {
                if (velocity < 20 && velocity < 20) {
                    //Initial leap is over!
                    initialLeapOver = true;
                }
            } else if (!secondLeapNegative) {
                if (velocity < 50) {
                    //Second leap has gone negative 
                    secondLeapNegative = true;
                }
            } else if (!secondLeapPositive) {
                if (velocity > 50) {
                    secondLeapPositive = true;
                }
            } else if (!thirdLeapNegative) {
                if (velocity < 50) {
                    //Third leap has gone negative 
                    thirdLeapNegative = true;
                }
            } else if (!thirdLeapPositive) {
                if (velocity > 50) {
                    thirdLeapPositive = true;
                }
            } else {
                //All conditions satisfied
                if (velocity < 20 && velocity < 20) {
                    //Reset position and start printing!
                    totalCounts = 0;
                    printStartRequested = false;
                    PCBPrinter::this_PCBPrinter->switchState(3);
                }
            }
        }
    }
}