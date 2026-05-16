/*
 * ui.h
 *
 *  Created on: Apr 25, 2026
 *      Author: Morel
 */

#include <stdint.h>

#ifndef UI_H_
#define UI_H_

#define MAIN_MENU_COUNT    4
#define MODE_MENU_COUNT    4
#define STATUS_MENU_COUNT  4

typedef enum {
    UI_MENU_MAIN,
    UI_MENU_MODE,
    UI_MENU_STATUS
} UiMenu_t;


void UI_DrawMenu(void);
void UI_DrawStatus(void);
void UI_UpdateSelection(void);
void UI_NextItem(void);
void UI_PrevItem(void);
void UI_SelectItem(void);


#endif /* UI_H_ */
