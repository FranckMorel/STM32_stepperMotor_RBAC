/*
 * ui.c
 *
 *  Created on: Apr 27, 2026
 *      Author: Morel
 */


#include "ui.h"
#include "tft.h"
#include "motor_control.h"
#include <stdint.h>


static UiMenu_t currentMenu = UI_MENU_MAIN;
static uint8_t currentItem = 0;


const char* mainMenu_items[] = {
        "Start",
        "Stop",
        "Status",
        "Mode"
  };

const char* modeMenu_items[] = {
        "ECO",
        "NORMAL",
        "FAST",
		"Back"
  };

const char* statusMenu_items[] = {
        "Mode: ",
        "State: ",
        "Direction: ",
		"Back"
  };



//void UI_init(void){}

void UI_DrawMenu(void)
{
    tft_testFullScreenColor(TFT_BLACK);

    const char** items = 0;
    uint8_t count = 0;
    const char* title = "";

    if(currentMenu == UI_MENU_MAIN)
    {
        items = mainMenu_items;
        count = MAIN_MENU_COUNT;
        title = "Motor Control";
    }
    else if(currentMenu == UI_MENU_MODE)
    {
        items = modeMenu_items;
        count = MODE_MENU_COUNT;
        title = "Select Mode";
    }
    else if(currentMenu == UI_MENU_STATUS)
    {
        items = statusMenu_items;
        count = STATUS_MENU_COUNT;
        title = "Status";
    }

    tft_draw_string(20, 10, title, TFT_WHITE, TFT_BLACK);

    for(uint8_t i = 0; i < count; i++)
    {
        uint16_t color = TFT_WHITE;

        if(i == currentItem)
        {
            tft_draw_char(10, 40 + i * 20, '>', TFT_YELLOW, TFT_BLACK);
            color = TFT_YELLOW;
        }
        else
        {
            tft_draw_char(10, 40 + i * 20, ' ', TFT_WHITE, TFT_BLACK);
        }

        tft_draw_string(25, 40 + i * 20, items[i], color, TFT_BLACK);
    }
}

void UI_DrawStatus(void)
{
    tft_testFullScreenColor(TFT_BLACK);

    tft_draw_string(20, 10, "Status", TFT_WHITE, TFT_BLACK);

    tft_draw_string(10, 40, "Mode:", TFT_WHITE, TFT_BLACK);
    tft_draw_string(70, 40, MotorControl_GetModeString(), TFT_YELLOW, TFT_BLACK);

    tft_draw_string(10, 60, "State:", TFT_WHITE, TFT_BLACK);
    tft_draw_string(70, 60, MotorControl_GetStateString(), TFT_YELLOW, TFT_BLACK);

    tft_draw_string(10, 80, "Dir:", TFT_WHITE, TFT_BLACK);
    tft_draw_string(70, 80, MotorControl_GetDirectionString(), TFT_YELLOW, TFT_BLACK);

    if(currentItem == 3)
     {
         tft_draw_char(10, 110, '>', TFT_YELLOW, TFT_BLACK);
         tft_draw_string(25, 110, "Back", TFT_YELLOW, TFT_BLACK);
     }
     else
     {
         tft_draw_char(10, 110, ' ', TFT_WHITE, TFT_BLACK);
         tft_draw_string(25, 110, "Back", TFT_WHITE, TFT_BLACK);
     }
}

void UI_NextItem(void){
    uint8_t count = 0;

    switch(currentMenu)
    {
        case UI_MENU_MAIN:   count = MAIN_MENU_COUNT; break;
        case UI_MENU_MODE:   count = MODE_MENU_COUNT; break;
        case UI_MENU_STATUS: count = STATUS_MENU_COUNT; break;
    }

    currentItem++;

    if(currentItem >= count)
        currentItem = 0;
}

void UI_PrevItem(void){
	  uint8_t count = 0;

	    switch(currentMenu)
	    {
	        case UI_MENU_MAIN:   count = MAIN_MENU_COUNT; break;
	        case UI_MENU_MODE:   count = MODE_MENU_COUNT; break;
	        case UI_MENU_STATUS: count = STATUS_MENU_COUNT; break;
	    }

	    if(currentItem == 0)
	 	    currentItem = count - 1;
	    else
	    	currentItem--;

}

void UI_SelectItem(void){

	 if(currentMenu == UI_MENU_MAIN){
		 if(currentItem == 0){
			 MotorControl_RunUserMode();

		 }
		 else if(currentItem == 1){
			 MotorControl_Stop();

		 }
		 else if(currentItem == 2){
			 currentMenu = UI_MENU_STATUS;
			 currentItem = 0;
			 UI_DrawStatus();
		 }
		 else if(currentItem == 3){
			 currentMenu = UI_MENU_MODE;
			 currentItem = 0;
			 UI_DrawMenu();
		 }

	 }

	 else if(currentMenu == UI_MENU_MODE){
		 if(currentItem == 0){
			 MotorControl_SetMode(MODE_ECO);
		 }
		 else if(currentItem == 1) {
			 MotorControl_SetMode(MODE_NORMAL);
		 }
		 else if (currentItem == 2){
			 MotorControl_SetMode(MODE_FAST);
		 }
		 else if(currentItem == 3) {  // "Back"
		        currentMenu = UI_MENU_MAIN;
		        currentItem = 0;
		    }

		 UI_DrawMenu();

	 }

	 else if(currentMenu == UI_MENU_STATUS){
		   if(currentItem == 3)
		    {
		        currentMenu = UI_MENU_MAIN;
		        currentItem = 0;
		        UI_DrawMenu();
		    }
		    else
		    {
		        UI_DrawStatus();
		    }

	 }
}
