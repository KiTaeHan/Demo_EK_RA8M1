#ifndef DRIVERS_LCD_LCD_IO_H_
#define DRIVERS_LCD_LCD_IO_H_

#include "hal_data.h"

#include "lcd_errno.h"
#include "ili9341/ili9341.h"

/**
  * @addtogroup LCD_Orientation LCD Orientation
  * @brief      Supported LCD Orientations.
  * @{
  */
#define LCD_ORIENTATION_PORTRAIT            ILI9341_ORIENTATION_PORTRAIT          /*!< Portrait orientation choice of LCD screen               */
#define LCD_ORIENTATION_PORTRAIT_ROT180     ILI9341_ORIENTATION_PORTRAIT_ROT180   /*!< Portrait rotated 180° orientation choice of LCD screen  */
#define LCD_ORIENTATION_LANDSCAPE           ILI9341_ORIENTATION_LANDSCAPE         /*!< Landscape orientation choice of LCD screen              */
#define LCD_ORIENTATION_LANDSCAPE_ROT180    ILI9341_ORIENTATION_LANDSCAPE_ROT180  /*!< Landscape rotated 180° orientation choice of LCD screen */

/**
  * @addtogroup LCD_Cache_lines LCD Cache lines
  * @brief      LCD Cache buffer as configured by the user.
  * @{
  */
#define BUFFER_CACHE_LINES                  16  /*!< hideinitializer Number of lines defined by the user for the Buffer cache */

typedef struct
{
  /* Control functions */
  int32_t (*Init             )(void*, void*);
  int32_t (*DeInit           )(void*);
  int32_t (*ReadID           )(void*, uint32_t*);
  int32_t (*DisplayOn        )(void*);
  int32_t (*DisplayOff       )(void*);
  int32_t (*SetDisplayWindow )(void*, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t (*SetBrightness    )(void*, uint32_t);
  int32_t (*GetBrightness    )(void*, uint32_t*);
  int32_t (*SetOrientation   )(void*, uint32_t);
  int32_t (*GetOrientation   )(void*, uint32_t*);

  /* Drawing functions*/
  int32_t ( *SetCursor       ) (void*, uint32_t, uint32_t);
  int32_t ( *DrawBitmap      ) (void*, uint32_t, uint32_t, uint8_t *);
  int32_t ( *FillRGBRect     ) (void*, uint32_t, uint32_t, uint8_t*, uint32_t, uint32_t);
  int32_t ( *DrawHLine       ) (void*, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *DrawVLine       ) (void*, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *FillRect        ) (void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *GetPixel        ) (void*, uint32_t, uint32_t, uint32_t*);
  int32_t ( *SetPixel        ) (void*, uint32_t, uint32_t, uint32_t);
  int32_t ( *GetXSize        ) (void*, uint32_t *);
  int32_t ( *GetYSize        ) (void*, uint32_t *);
}LCD_Drv_t;


int LCD_Probe(uint32_t Orientation);
int LCD_GetXSize(uint32_t *xsize);
int LCD_GetYSize(uint32_t *ysize);
int LCD_GetOrientation(uint32_t *orientation);
int LCD_WriteDataDMA(uint8_t *pData, uint32_t Length);
int LCD_WriteData(uint8_t *pData, uint32_t Length);
int LCD_SetDisplayWindow(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height);
int LCD_FillRGBRect(uint8_t UseDMA, uint8_t *pData, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height);
int32_t LCD_DisplayOn(void);


void LCD_TERisingCallback(void);
void LCD_TEFallingCallback(void);
void LCD_SignalTearingEffectEvent(uint8_t State, uint16_t Line);


#endif /* DRIVERS_LCD_LCD_IO_H_ */
