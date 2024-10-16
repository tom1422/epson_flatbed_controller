#include "UserInterface.h"
#include "PCBPrinter.h"

void UserInterface::setup() {
    //Switch to: https://github.com/duinoWitchery/hd44780

    Serial.begin(115200);
    Serial.setTimeout(30);

    lcd.begin(16, 2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to PCB");
    lcd.setCursor(0, 1);
    lcd.print("controller V1.0");
}

void UserInterface::loop() {
    //Don't update just for the sake of it!!!!

    /* if ((lastDisplayUpdate + 200) < millis()) {
         lastDisplayUpdate = millis();
         updateDisplay();
    } */

    //Check for button presses (Avoid using an interrupt!)
    if (usrBtnPressed) {
        if (millis() > (lastUsrBtnPressed + 200)) {
            lastUsrBtnPressed = millis();
            this->buttonPressed();
        }
    }    
    usrBtnPressed = false;
}

void UserInterface::setText(const char* text) {
    strcpy(currentText, text);

    updateDisplay();
}


void UserInterface::buttonPressedInterrupt() {
    usrBtnPressed = true;
}

void UserInterface::buttonPressed() {
    //Run stuff for button press
    //Current state changes action
    Serial.println("Button Pressed!");
    switch (PCBPrinter::this_PCBPrinter->state)
    {
    case 0:
        //It is in idle state
        //Attempt to start print
        PCBPrinter::this_PCBPrinter->switchState(2);
        break;
    case 3:
        //It is currently printing (This is when user thinks print is finished)
        PCBPrinter::this_PCBPrinter->switchState(0);
    default:
        break;
    }
}


void UserInterface::updateDisplay() {
    lcd.setCursor(0, 0);
    lcd.print("PCB Cnt V1.0    ");
    lcd.setCursor(0, 1);
    lcd.print(currentText);
}