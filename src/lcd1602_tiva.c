//! \file lcd1602_tiva.c
//! \brief driver for LCD1602 for Tiva C MCUs.
//! \author Nguyen Trong Phuong (aka trongphuongpro)
//! \date 2020 April 7

#include "lcd1602.h"

#include <string.h>

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

static PortPin_t en;
static PortPin_t rs;
static PortPin_t dataPins[4];

static void awake();
static void setFunction();
static void controlDisplay();
static void setEntryMode();
static void writeNibble(uint8_t nibble);
static void writeByte(uint8_t data);
static void sendData(uint8_t data);
static void sendInstruction(uint8_t data);

void lcd1602_init(PortPin_t en__, 
                    PortPin_t rs__, 
                    PortPin_t d4__, 
                    PortPin_t d5__, 
                    PortPin_t d6__, 
                    PortPin_t d7__)
{
    en = en__;
    rs = rs__;

    dataPins[0] = d4__;
    dataPins[1] = d5__;
    dataPins[2] = d6__;
    dataPins[3] = d7__;

    GPIOPinTypeGPIOOutput(en.base, en.pin);
    GPIOPinWrite(en.base, en.pin, 0);

    GPIOPinTypeGPIOOutput(rs.base, rs.pin);
    GPIOPinWrite(rs.base, rs.pin, 0);


    for (uint8_t i = 0; i < 4; i++) {
        GPIOPinTypeGPIOOutput(dataPins[i].base, dataPins[i].pin);
        GPIOPinWrite(dataPins[i].base, dataPins[i].pin, 0);
    }

    delay_init();
    delay_ms(500); // Delay ~500ms

    awake();
    setFunction();
    controlDisplay();
    lcd1602_clear();
    lcd1602_home();
    setEntryMode();
}


void awake() {
    GPIOPinWrite(rs.base, rs.pin, 0);

    for (int i = 0; i < 5; i++) {
        writeNibble(0x00);
    }
}


void setFunction() {
    GPIOPinWrite(dataPins[1].base, dataPins[1].pin, dataPins[1].pin);
    GPIOPinWrite(en.base, en.pin, en.pin);
    GPIOPinWrite(en.base, en.pin, 0);
    GPIOPinWrite(dataPins[1].base, dataPins[1].pin, 0);

    sendInstruction(0x28);
}


void controlDisplay() {
    // Display control: cursor, no blink
    sendInstruction(0x0C);
}


void setEntryMode() {
    // Entry set mode: Increase, no shift
    sendInstruction(0x06);
}


void lcd1602_home() {
    sendInstruction(0x02);
}


void lcd1602_clear() {
    sendInstruction(0x01);
}


void lcd1602_setCursor(uint8_t row, uint8_t col) {
    uint8_t address = (col-1) + (row-1) * 64;
    sendInstruction(address | 0x80);
}


void lcd1602_putChar(uint8_t c) {
    sendData(c);
}


void lcd1602_print(const char *text, uint8_t row, uint8_t col, uint8_t width, uint16_t delay) {
    if (strlen(text) <= width) {
        lcd1602_setCursor(row, col);

        for (uint8_t i = 0; i < strlen(text); i++) {
            lcd1602_putChar(text[i]);
        }
    }
    else {
        for (uint8_t i = 0; i < strlen(text)-width+1; i++) {
            lcd1602_setCursor(row, col);

            for (uint8_t c = 0; c < width; c++) {
                lcd1602_putChar(text[c+i]);
            }

            delay_ms(delay);
        }
    }
}


void writeNibble(uint8_t nibble) {
    for (int i = 0; i < 4; i++) {
        uint8_t bit = ((nibble >> i) & 1) ? dataPins[i].pin : 0;

        GPIOPinWrite(dataPins[i].base, dataPins[i].pin, bit);
    }

    GPIOPinWrite(en.base, en.pin, en.pin);
    GPIOPinWrite(en.base, en.pin, 0);
}



void writeByte(uint8_t data) {
    writeNibble(data >> 4);
    writeNibble(data & 0x0F);
}


void sendData(uint8_t data) {
    GPIOPinWrite(rs.base, rs.pin, rs.pin);
    writeByte(data);
    delay_ms(1); // Delay ~10ms
}


void sendInstruction(uint8_t data) {
    GPIOPinWrite(rs.base, rs.pin, 0);
    writeByte(data);
    delay_ms(1); // Delay ~10ms  
}


void lcd1602_scrollLeft() {
    sendInstruction(0x18);
}


void lcd1602_scrollRight() {
    sendInstruction(0x1C);
}

/************************ End of File ****************************************/ 