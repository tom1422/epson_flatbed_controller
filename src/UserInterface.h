#pragma once
#include <LiquidCrystal_I2C.h>

//---------Screen---------
#define I2C_SDA 20
#define I2C_SCL 21
//---------USER---------
#define USR_BTN 3
//Enble or disable this for serial logging
#define serialLog

class UserInterface {
  public:
    void setup();

    void loop();

    void setText(const char* text);

    void buttonPressed();

    void buttonPressedInterrupt();

  private:

    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
    unsigned long lastDisplayUpdate = 0;

    char currentText[25];

    void updateDisplay();

    //Debouce stuff
    unsigned long lastUsrBtnPressed = 0;
    bool usrBtnPressed = false;
};