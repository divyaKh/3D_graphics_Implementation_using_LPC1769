/*
 * drawLine.h
 *
 *  Created on: May 12, 2021
 *      Author: divya
 */

#ifndef DRAWLINE_H_
#define DRAWLINE_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/* Be careful with the port number and location number, because

some of the location may not exist in that port. */




//-----------------------------------------------------------
// Code for drawing a line - Given By Prof. Harry Li
//-----------------------------------------------------------

void spiwrite(uint8_t c);

void writecommand(uint8_t c);

void writedata(uint8_t c);

void writeword(uint16_t c);

void write888(uint32_t color, uint32_t repeat);

void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void fillrect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);

void lcddelay(int ms);

void lcd_init();

void drawPixel(int16_t x, int16_t y, uint32_t color);

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);


#endif /* DRAWLINE_H_ */
