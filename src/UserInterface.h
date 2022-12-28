#pragma once
#include <LiquidCrystal_I2C.h>

//---------Screen---------
#define I2C_SDA 20
#define I2C_SCL 21
//---------USER---------
#define USR_BTN 3

class UserInterface {
  public:
    void setup();

    void loop();

    void setText(const char* text);

    void buttonPressed();

  private:

    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
    unsigned long lastDisplayUpdate = 0;

    char currentText[25];

    void updateDisplay();
};