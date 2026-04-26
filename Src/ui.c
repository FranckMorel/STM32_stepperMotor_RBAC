/*
 * ui.c
 *
 *  Created on: Apr 25, 2026
 *      Author: Morel
 */

/*Currently testing Display functions on this project to use on the stepperMotor project*/

#include "ui.h"
#include "tft.h"
#include <stdint.h>



uint8_t current_item = 0;

const char* menu_items[] = {
        "Start",
        "Stop",
        "Status",
        "Settings"
  };



void draw_menu(void) {
     // Hintergrund löschen
     tft_testFullScreenColor(TFT_BLACK);

     // Titel
     tft_draw_string(20, 10, "Motor Control", TFT_WHITE, TFT_BLACK);

     // Menü Einträge zeichnen
     for(int i = 0; i < 4; i++) {
         uint16_t color = TFT_WHITE;

         // Aktueller Eintrag wird mit ">" markiert
         if(i == current_item) {
             tft_draw_char(10, 40 + i*20, '>', TFT_YELLOW, TFT_BLACK);
             color = TFT_YELLOW;
         } else {
             tft_draw_char(10, 40 + i*20, ' ', TFT_WHITE, TFT_BLACK);
         }

         tft_draw_string(25, 40 + i*20, menu_items[i], color, TFT_BLACK);
     }
 }
