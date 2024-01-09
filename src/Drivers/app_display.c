#include <string.h>

#include "app_display.h"

static uint8_t CacheBuffer[BUFFER_CACHE_COUNT][(320*2*BUFFER_CACHE_LINES)];
volatile uint8_t TransferAllowed = 0;
static volatile uint16_t tearing_effect_counter = 0;


/*
 * Draws a full rectangle in currently active layer.
 * Xpos: X position
 * Ypos: Y position
 * Width: Rectangle width
 * Height: Rectangle height
 * Color:
 */
int APP_LCD_FillRect(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint32_t Color)
{
    uint32_t size;
    uint32_t CacheLineCnt, CacheLinesSz;
    uint32_t offset=0, line_cnt=Ypos;

    size = (2*Width*Height);
    CacheLineCnt = (Height > BUFFER_CACHE_LINES ? BUFFER_CACHE_LINES : Height);
    CacheLinesSz = (2*Width*CacheLineCnt);
    memset(CacheBuffer[0], Color, CacheLinesSz);



    while(line_cnt < (Ypos + Height))
    {
        uint16_t current_display_line;
        timer_status_t timer_status;

        R_GPT_StatusGet(&LCD_timer_ctrl, &timer_status);
        current_display_line = (tearing_effect_counter > 0 ? 0xFFFF : (uint16_t)timer_status.counter);
        if((line_cnt + CacheLineCnt) < current_display_line)
        {
            if(LCD_FillRGBRect(0, CacheBuffer[0], Xpos, line_cnt, Width, CacheLineCnt) == BSP_ERROR_NONE)
            {
                line_cnt += CacheLineCnt;
                offset += CacheLinesSz;
            }
        }

        // Check remaining data size
        if(offset == size)
        {
            // last block transfer was done, so exit
            break;
        }
        else if((offset + CacheLinesSz) > size)
        {
            // Transfer last block and exit
            CacheLineCnt = ((size - offset)/(2*Width));

            R_GPT_StatusGet(&LCD_timer_ctrl, &timer_status);
            current_display_line = (tearing_effect_counter > 0 ? 0xFFFF : (uint16_t)timer_status.counter);
            if((line_cnt + CacheLineCnt) < current_display_line)
            {
                if(LCD_FillRGBRect(0, CacheBuffer[0], Xpos, line_cnt, Width, CacheLineCnt) == BSP_ERROR_NONE)
                {
                    line_cnt += CacheLineCnt;
                }
            }
        }
    }

    return BSP_ERROR_NONE;
}

void APP_LCD_Clear(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
    APP_LCD_FillRect(Xpos, Ypos, Width, Height, 0);
}

void LCD_SignalTearingEffectEvent(uint8_t State, uint16_t Line)
{
    if(State)
    {
        /* Line '0' is the Vsync event */
        if(Line == 0)
        {
            /* TE event is received : de-allow display refresh */
            TransferAllowed = 0;
            // Increment TE counter, so we will know that a TE event has already happened
            tearing_effect_counter++;
            // Disable HW Timer
            R_GPT_Stop(&LCD_timer_ctrl);
            //Reset HW Timer counter
            R_GPT_CounterSet(&LCD_timer_ctrl, 0);
        }
    }
    else
    {
        /* TE event is received : allow display refresh */
        TransferAllowed = 1;
        // Enable HW Timer
        R_GPT_Start(&LCD_timer_ctrl);
    }
}
