#ifndef DRIVERS_APP_DISPLAY_H_
#define DRIVERS_APP_DISPLAY_H_

#include "lcd_io.h"

#define BUFFER_CACHE_COUNT          3


int APP_LCD_FillRect(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint32_t Color);
void APP_LCD_Clear(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height);

#endif /* DRIVERS_APP_DISPLAY_H_ */
