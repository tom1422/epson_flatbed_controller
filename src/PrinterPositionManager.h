#pragma once
//---------Optical Encoder Stuff---------
#define OPTENCP1 18
#define OPTENCP2 19

class PrinterPositionManager {
  public:
    void setup();

    void loop();

    void p1Rising();

    void printStarted();

    float getPaperPosition();

  private:
    int counts = 0;
    int totalCounts = 0;

    unsigned long lastAlgoUpdate = 0;

    //Print start sense algorithm
    bool initialLeapOver = false;
    bool secondLeapNegative = false;
    bool secondLeapPositive = false;
    bool thirdLeapNegative = false;
    bool thirdLeapPositive = false;

    //Current State Variables
    bool printStartRequested = false;

    void monitorPatterns();
};