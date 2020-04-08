//! \file lcd1602.h
//! \brief driver for LCD1602 for Tiva C MCUs.
//! \author Nguyen Trong Phuong (aka trongphuongpro)
//! \date 2020 April 7


#ifndef __LCD1602__
#define __LCD1602__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "utils.h"

void lcd1602_init(PortPin_t en, 
                    PortPin_t rs, 
                    PortPin_t d4, 
                    PortPin_t d5, 
                    PortPin_t d6, 
                    PortPin_t d7);

void lcd1602_scrollLeft();
void lcd1602_scrollRight();
void lcd1602_setCursor(uint8_t row, uint8_t col);
void lcd1602_putChar(uint8_t c);
void lcd1602_print(const char *text, uint8_t row, uint8_t col, uint8_t width, uint16_t delay);
void lcd1602_clear();
void lcd1602_home();


#ifdef __cplusplus
}
#endif


#endif

/************************ End of File ****************************************/ 