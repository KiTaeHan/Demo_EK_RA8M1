#include "lcd_conf.h"
#include "lcd_errno.h"
#include "lcd_io.h"
#include "ili9341/ili9341.h"

static int32_t LCD_IO_Init(void);

static void             *LcdCompObj = NULL;
static LCD_Drv_t        *LcdDrv = NULL;
static ILI9341_IO_t     IO_Ili9341 = {0};
static ILI9341_Object_t Obj_Ili9341 = {0};



/* Register Bus IO
 */
static int32_t LCD_Probe(uint32_t Orientation)
{
  int32_t ret = BSP_ERROR_NONE;
  ILI9341_InitParams_t ILI9341_InitParams;

  /* Configure the lcd driver : map to LCD_IO function*/
  IO_Ili9341.Init             = LCD_IO_Init;
  IO_Ili9341.DeInit           = LCD_IO_DeInit;
  IO_Ili9341.ReadReg          = LCD_IO_ReadReg;
  IO_Ili9341.WriteReg         = LCD_IO_WriteReg;
  IO_Ili9341.SendData         = LCD_IO_SendData;
  IO_Ili9341.SendDataDMA      = LCD_IO_SendDataDMA;
  IO_Ili9341.RecvData         = LCD_IO_RecvData;
  IO_Ili9341.RecvDataDMA      = LCD_IO_RecvDataDMA;
  IO_Ili9341.GetTick          = LCD_IO_GetTick;
  IO_Ili9341.Delay            = LCD_IO_Delay;

  if(ILI9341_RegisterBusIO(&Obj_Ili9341, &IO_Ili9341) != ILI9341_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    LcdCompObj = &Obj_Ili9341;

    /* LCD Initialization */
    LcdDrv = (LCD_Drv_t *)&ILI9341_LCD_Driver;

    Obj_Ili9341.IsInitialized = 0;

    ILI9341_InitParams.Endian         = ILI9341_ENDIAN_LITTLE;
    ILI9341_InitParams.SwapRB         = 0;
    ILI9341_InitParams.ColorCoding    = ILI9341_FORMAT_DEFAULT;
    ILI9341_InitParams.Orientation    = Orientation;
    ILI9341_InitParams.TEScanline     = 0;
    ILI9341_InitParams.TEMode         = ILI9341_TE_MODE_1;
    ILI9341_InitParams.Timings.hsync  = ILI9341_HSYNC;
    ILI9341_InitParams.Timings.hbp    = ILI9341_HBP;
    ILI9341_InitParams.Timings.hfp    = ILI9341_HFP;
    ILI9341_InitParams.Timings.vsync  = ILI9341_VSYNC;
    ILI9341_InitParams.Timings.vbp    = ILI9341_VBP;
    ILI9341_InitParams.Timings.vfp    = ILI9341_VFP;
    if(LcdDrv->Init(LcdCompObj, &ILI9341_InitParams) != ILI9341_OK)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
  }

  return ret;
}

/* Initializes LCD low level.
  */
static int32_t LCD_IO_Init(void)
{
  int32_t ret = BSP_ERROR_NONE;
  LCD_RST_LOW();
  UserDelay_10MS(10);
  LCD_RST_HIGH();
  UserDelay_10MS(10);

  /* turn LCD on = drive pin low (active low) */
  /* Set or Reset the control line */
  LCD_CS_HIGH();
  LCD_DC_HIGH();

  ret = LCD_SPI_Init();

  if(ret == BSP_ERROR_NONE)
  {
      /* Register TE event IRQ handler */
      R_ICU_ExternalIrqOpen(&LCD_external_irq11_ctrl, &LCD_external_irq11_cfg);
      R_ICU_ExternalIrqEnable(&LCD_external_irq11_ctrl);
  }

  return ret;
}
