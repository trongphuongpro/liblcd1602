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


typedef struct PortPin {
    uint32_t base;
    uint8_t pin;
} PortPin_t;


void lcd1602_init(const PortPin_t *en, 
                    const PortPin_t *rs, 
                    const PortPin_t *d4, 
                    const PortPin_t *d5, 
                    const PortPin_t *d6, 
                    const PortPin_t *d7);

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