/*
 * tft.h
 *
 *  Created on: Apr 23, 2026
 *      Author: Morel
 */

#include <stdint.h>

#ifndef TFT_H_
#define TFT_H_

#define DC_PIN     	6
#define CS_PIN     	9
#define RST_PIN  	8

#define DC_HIGH()	(GPIOA -> BSRR = (1U<<6))
#define DC_LOW()	(GPIOA -> BSRR = (1U<<(DC_PIN + 16)))

#define RST_HIGH()	(GPIOA -> BSRR = (1U<<8))
#define RST_LOW()	(GPIOA -> BSRR = (1U<<(RST_PIN + 16)))


// ab s104 -> ST7735S Datasheet v1.1: COMMANDOS
#define SWRESET		0x01  // Reset zum Start
#define SLPOUT		0x11  // Display aus dem Schalf holen
#define COLMOD		0x3A  // Farbformat einstellen (16-bit)
#define MADCTL		0x36  // RGB/BGR Reihenfolge
#define DISPON 		0x29  // Display einschalten
#define CASET		0x2A  // Spaltenbereich setzen
#define RASET 		0x2B  // Zeilenbereich setzen
#define RAMWR		0x2C  // Pixel schreiben

#define TFT_WIDTH   132   // 132 Pixel breit (Spalten)
#define TFT_HEIGHT  162   // 162 Pixel hoch (Zeilen)


#define TFT_BLACK   0x0000
#define TFT_WHITE   0xFFFF
#define TFT_RED     0xF800
#define TFT_GREEN   0x07E0
#define TFT_BLUE    0x001F
#define TFT_YELLOW  0xFFE0

void tft_write_cmd(uint8_t cmd);
void tft_write_data(uint8_t data);
void tft_write_data16(uint16_t data);
void tft_reset(void);
void tft_Init(void);

void tft_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void tft_draw_char(uint16_t x, uint16_t y, char ch, uint16_t fg, uint16_t bg);
void tft_draw_string(uint16_t x, uint16_t y, const char *str, uint16_t fg, uint16_t bg);

void tft_testFullScreenColor(uint16_t color);


#endif /* TFT_H_ */
