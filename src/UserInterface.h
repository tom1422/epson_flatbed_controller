#pragma once
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
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

    hd44780_I2Cexp lcd = hd44780_I2Cexp(0x3F, 16, 2);

    unsigned long lastDisplayUpdate = 0;

    char currentText[25];

    void updateDisplay();

    //Debouce stuff
    unsigned long lastUsrBtnPressed = 0;
    bool usrBtnPressed = false;
};