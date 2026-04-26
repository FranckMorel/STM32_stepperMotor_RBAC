/*
 * tft.c
 *
 *  Created on: Apr 23, 2026
 *      Author: Morel
 */
#include "stm32f401xe.h"
#include "tft.h"
#include "spi.h"
#include "timer.h"
#include "font.h"


// s24 -> ST7735S Datasheet v1.1: DC LOW for cmd and DC HIGH for data
void tft_write_cmd(uint8_t cmd){

	DC_LOW();
	cs_enable();
	spi1_transmit(&cmd,1);
	cs_disable();

}

void tft_write_data(uint8_t data){

	DC_HIGH();
	cs_enable();
	spi1_transmit(&data,1);
	cs_disable();

}


void tft_write_data16(uint16_t data){
    uint8_t high = (data >> 8); 	 // obere 8 Bits (z.B. 0xF8)
    uint8_t low  = (data & 0xFF);    // untere 8 Bits (z.B. 0x00)
    tft_write_data(high);
    tft_write_data(low);
}

// s93 -> ST7735S Datasheet v1.1: RST muss mindestens 10us LOW sein
void tft_reset(void){

	RST_LOW();
    delay_ms(10);

    RST_HIGH();
    delay_ms(120);
}

void tft_Init(){

    tft_reset();
    tft_write_cmd(SWRESET);
    delay_ms(150);			 // s108 discription fpr SWRESET
    tft_write_cmd(SLPOUT);
    delay_ms(120);			 // s120 Sleepout cmd
    tft_write_cmd(COLMOD);
    tft_write_data(0x05);    // s150, 16-bit RGB565
    tft_write_cmd(MADCTL);
    tft_write_data(0xC0);    // BGR Modus, alle anderen Bits werden überschrieben aber ok , weil nicht gebraucht werden
    tft_write_cmd(DISPON);
    delay_ms(100);
}


/*
void tft_test1(void) {
     // Daten werden als 16 Bits Werte geschrieben, also in 8Bits Paare aufgespittet
     // s128,s130 : CASET und RASET definieren den Schreibbereich

    tft_write_cmd(CASET);
    tft_write_data(0x00); tft_write_data(0x00); // Start bei 0
    tft_write_data(0x00); tft_write_data(0x83); // Ende bei 131

    tft_write_cmd(RASET);
    tft_write_data(0x00); tft_write_data(0x00); // Start bei 0
    tft_write_data(0x00); tft_write_data(0xA1); // Ende bei 161

    tft_write_cmd(RAMWR); // versetzt Display in den Pixel Schreib Modus

    for(uint32_t i = 0; i < 132 * 162; i++) {
        tft_write_data(0x00);  // Rot High
        tft_write_data(0x1F);  // Rot Low
    }
}
*/


void tft_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    tft_write_cmd(CASET);
    // Koordinaten in 8 Bits Paare aufgesplittet:
    tft_write_data(x1 >> 8); tft_write_data(x1 & 0xFF);
    tft_write_data(x2 >> 8); tft_write_data(x2 & 0xFF);

    tft_write_cmd(RASET);
    tft_write_data(y1 >> 8); tft_write_data(y1 & 0xFF);
    tft_write_data(y2 >> 8); tft_write_data(y2 & 0xFF);

    tft_write_cmd(RAMWR);
}

/* Zeichen zeichnen:
   @param x, y: Position (oben links)
   @param ch: ASCII Zeichen (32-127)
   @param fg: Vordergrundfarbe (das Zeichen selbst)
   @param bg: Hintergrundfarbe (die Fläche um das Zeichen)
 */

void tft_draw_char(uint16_t x, uint16_t y, char ch, uint16_t fg, uint16_t bg) {
    if(ch < 32 || ch > 127) return; // ungueltige Zeichen filtern

    const uint8_t *data = &Font8x16[ch - 32][0];
    tft_set_window(x, y, x + 7, y + 15); // Ein Zeichen ist 8Pixel breit und 16Pixel hoch

    for(int row = 0; row < 16; row++) {
        uint8_t row_data = data[row];
        for(int col = 0; col < 8; col++) {
            if(row_data & 0x80) { // 0x80 = 10000000 -> wenn Bit7 ist 1 -> Bedingung erfüllt || MSB fisrt
                tft_write_data16(fg); // Print mit eingestellter Zeichenfarbe
            } else {
                tft_write_data16(bg); // print mit Hintergrundfarbe
            }
            row_data <<= 1;
        }
    }
}

void tft_draw_string(uint16_t x, uint16_t y, const char *str, uint16_t fg, uint16_t bg) {
    while(*str) {
        if(x > TFT_WIDTH - 8) {
            x = 0;
            y += 16;
        }
        tft_draw_char(x, y, *str, fg, bg);
        x += 8;
        str++;
    }
}


void tft_testFullScreenColor(uint16_t color){

	tft_set_window(0,0,131,161);

	for(uint32_t i = 0; i < 132 * 162; i++) {

		tft_write_data16(color);

	    }
}





