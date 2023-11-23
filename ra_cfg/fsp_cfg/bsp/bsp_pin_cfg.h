/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#if __has_include("r_ioport.h")
#include "r_ioport.h"
#elif __has_include("r_ioport_b.h")
#include "r_ioport_b.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define LCD_TE (BSP_IO_PORT_00_PIN_06)
#define MIC_INT (BSP_IO_PORT_05_PIN_09)
#define LED1 (BSP_IO_PORT_06_PIN_00)
#define LCD_MISO (BSP_IO_PORT_06_PIN_09)
#define LCD_SCK (BSP_IO_PORT_06_PIN_10)
#define LCD_MOSI (BSP_IO_PORT_06_PIN_11)
#define LCD_CS (BSP_IO_PORT_06_PIN_12)
#define LCD_DCX (BSP_IO_PORT_06_PIN_14)
#define LCD_RESET (BSP_IO_PORT_10_PIN_08)
extern const ioport_cfg_t g_bsp_pin_cfg; /* R7FA8M1AHECBD.pincfg */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
