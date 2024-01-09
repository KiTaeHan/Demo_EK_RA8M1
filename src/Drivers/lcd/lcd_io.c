#include "lcd_conf.h"
#include "lcd_io.h"
#include "ili9341/ili9341.h"

static int32_t LCD_IO_Init(void);
static int32_t LCD_IO_DeInit(void);
static int32_t LCD_IO_ReadReg(volatile uint8_t *Reg, uint32_t Length);
static int32_t LCD_IO_WriteReg(volatile uint8_t *Reg, uint32_t Length);
static int32_t LCD_IO_SendData(uint8_t *pData, uint32_t Length);
static int32_t LCD_IO_SendDataDMA(uint8_t *pData, uint32_t Length);
static int32_t LCD_IO_RecvData(uint8_t *pData, uint32_t Length);
static int32_t LCD_IO_RecvDataDMA(uint8_t *pData, uint32_t Length);
static int32_t LCD_IO_GetTick(void);
static int32_t LCD_IO_Delay(uint32_t Delay);

static void             *LcdCompObj = NULL;
static LCD_Drv_t        *LcdDrv = NULL;
static ILI9341_IO_t     IO_Ili9341 = {0};
static ILI9341_Object_t Obj_Ili9341 = {0};



/* Register Bus IO
 */
int LCD_Probe(uint32_t Orientation)
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

int LCD_GetXSize(uint32_t *xsize)
{
    int ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

    if(LcdDrv->GetXSize != NULL)
    {
       if(LcdDrv->GetXSize(LcdCompObj, xsize) < 0)
       {
           ret = BSP_ERROR_COMPONENT_FAILURE;
       }
       else
       {
           ret = BSP_ERROR_NONE;
       }
    }

    return ret;
}

int LCD_GetYSize(uint32_t *ysize)
{
    int ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

    if(LcdDrv->GetYSize != NULL)
    {
       if(LcdDrv->GetYSize(LcdCompObj, ysize) < 0)
       {
           ret = BSP_ERROR_COMPONENT_FAILURE;
       }
       else
       {
           ret = BSP_ERROR_NONE;
       }
    }

    return ret;
}

int LCD_GetOrientation(uint32_t *orientation)
{
    int ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

    if(LcdDrv->GetOrientation != NULL)
    {
       if(LcdDrv->GetOrientation(LcdCompObj, orientation) < 0)
       {
           ret = BSP_ERROR_COMPONENT_FAILURE;
       }
       else
       {
           ret = BSP_ERROR_NONE;
       }
    }

    return ret;
}

/*
 * Send data to select the LCD GRAM
 * pData: Pointer to data to write LCD GRAM.
 * Length: Length of data to write to LCD GRAM.
 */
int LCD_WriteDataDMA(uint8_t *pData, uint32_t Length)
{
   int ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

   if(IO_Ili9341.SendDataDMA != NULL)
   {
       if(IO_Ili9341.SendDataDMA(pData, (Length/2)) < 0)
       {
           ret = BSP_ERROR_COMPONENT_FAILURE;
       }
       else
       {
           ret = BSP_ERROR_NONE;
       }
   }

   return ret;
}

/*
 * Send data to select the LCD GRAM
 * pData: Pointer to data to write LCD GRAM.
 * Length: Length of data to write to LCD GRAM.
 */
int LCD_WriteData(uint8_t *pData, uint32_t Length)
{
   int ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

   if(IO_Ili9341.SendData != NULL)
   {
       if(IO_Ili9341.SendData(pData, (Length/2)) < 0)
       {
           ret = BSP_ERROR_COMPONENT_FAILURE;
       }
       else
       {
           ret = BSP_ERROR_NONE;
       }
   }

   return ret;
}

/*
 * Sets a display windw.
 * Xpos: Specifies the X position.
 * Ypos: Specifies the Y position.
 * Width: Specifies the width of the rectangle to fill.
 * Height: Specifies the height of the rectangle to fill.
 */
int LCD_SetDisplayWindow(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
    int ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

    if(LcdDrv->SetDisplayWindow != NULL)
    {
       if(LcdDrv->SetDisplayWindow(LcdCompObj, Xpos, Ypos, Width, Height) < 0)
       {
           ret = BSP_ERROR_COMPONENT_FAILURE;
       }
       else
       {
           ret = BSP_ERROR_NONE;
       }
    }

    return ret;
}

/*
 * Send RGB Data to Select the LCD GRAM
 * UseDMA: Specifies if DMA will be used for data Transferring.
 * pData: Pointer to data to write to LCD GRAM.
 * Xpos: Specifies the X position.
 * Ypos: Specifies the Y position.
 * Width: Specifies the width of the rectangle to fill.
 * Height: Specifies the height of the rectangle to fill.
 */
int LCD_FillRGBRect(uint8_t UseDMA, uint8_t *pData, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
    int ret = BSP_ERROR_NONE;

    if(LCD_SetDisplayWindow(Xpos, Ypos, Width, Height) == BSP_ERROR_NONE)
    {
        if(UseDMA)
        {
            ret = LCD_WriteDataDMA(pData, (2*Width*Height));
        }
        else
        {
            ret = LCD_WriteData(pData, (2*Width*Height));
        }
    }
    else
    {
        ret = BSP_ERROR_BUS_FAILURE;
    }

    return ret;
}

/**
  * Switch On the display.
  * Instance:     LCD Instance.
  * int32_t:      BSP status.
  */
int32_t LCD_DisplayOn(void)
{
    int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

    if(LcdDrv->DisplayOn != NULL)
    {
        if(LcdDrv->DisplayOn(LcdCompObj) < 0)
        {
            ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
            ret = BSP_ERROR_NONE;
        }
    }

    return ret;
}

/*------------------- static functions -------------------*/
/* Initializes LCD low level.
  */
static int32_t LCD_IO_Init(void)
{
    int32_t ret = BSP_ERROR_NONE;
    LCD_RST_LOW();
    UserDelay_MS(100);
    LCD_RST_HIGH();
    UserDelay_MS(100);

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

    R_GPT_Open(&LCD_timer_ctrl, &LCD_timer_cfg);

    return ret;
}

/* DeInitializes LCD low level
  */
static int32_t LCD_IO_DeInit(void)
{
    int32_t ret = BSP_ERROR_NONE;

    ret = LCD_SPI_DeInit();
    R_GPT_Close(&LCD_timer_ctrl);

    return ret;
}

/**
  * @brief  Read register on LCD register.
  * @param  Reg    Register to be read
  * @param  Length length of data be read from the LCD GRAM
  * @retval BSP status
  */
static int32_t LCD_IO_ReadReg(volatile uint8_t *Reg, uint32_t Length)
{
    (void)Reg;
    (void)Length;
    return BSP_ERROR_FEATURE_NOT_SUPPORTED;
}

/**
  * @brief  Writes register on LCD register.
  * @param  Reg    Register to be written
  * @param  Length length of data be read from the LCD GRAM
  * @retval BSP status
  */
static int32_t LCD_IO_WriteReg(volatile uint8_t *Reg, uint32_t Length)
{
    int32_t ret = BSP_ERROR_NONE;

    LCD_CS_LOW();
    LCD_DC_HIGH();
    ret = LCD_SPI_Send((uint8_t *)Reg, Length);
    LCD_DC_LOW();
    LCD_CS_HIGH();

    return ret;
}

/**
  * @brief  Send data to select the LCD GRAM.
  * @param  pData  pointer to data to write to LCD GRAM.
  * @param  Length length of data to write to LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_SendData(uint8_t *pData, uint32_t Length)
{
    int32_t ret = BSP_ERROR_NONE;

    LCD_CS_LOW();
    ret = LCD_SPI_Send(pData, Length);
    LCD_CS_HIGH();

    return ret;
}

/**
  * @brief  Send data to select the LCD GRAM using DMA.
  * @param  pData  pointer to data to write to LCD GRAM.
  * @param  Length length of data to write to LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_SendDataDMA(uint8_t *pData, uint32_t Length)
{
#if 0
    int32_t ret = BSP_ERROR_NONE;
    LCD_CS_LOW();
    /* Send Data */
    ret = LCD_SPI_Send_DMA(pData, Length);
    return ret;
#else
    (void)pData;
    (void)Length;
    return BSP_ERROR_FEATURE_NOT_SUPPORTED;
#endif
}

/**
  * @brief  Receive data from selected LCD GRAM.
  * @param  pData  pointer to data to read to from selected LCD GRAM.
  * @param  Length length of data to read from selected LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_RecvData(uint8_t *pData, uint32_t Length)
{
    int32_t ret = BSP_ERROR_NONE;

    LCD_CS_LOW();
    LCD_DC_HIGH();

    /* Write Register to read */
    ret = LCD_SPI_Send(pData, 1);

    LCD_DC_LOW();

    /* Receive the Data */
    ret = LCD_SPI_Recv(pData, Length);

    LCD_CS_HIGH();

    return ret;
}

/**
  * @brief  Receive data using DMA from selected LCD GRAM.
  * @param  pData  pointer to data to read to from selected LCD GRAM.
  * @param  Length length of data to read from selected LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_RecvDataDMA(uint8_t *pData, uint32_t Length)
{
    (void)pData;
    (void)Length;
    return BSP_ERROR_FEATURE_NOT_SUPPORTED;
}

/**
  * @brief  Provide a tick value in millisecond.
  * @retval int32_t:  Tick value.
  */
static int32_t LCD_IO_GetTick(void)
{
    uint32_t ret;
    ret = LCD_GetTick();

    return (int32_t)ret;
}

/**
  * @brief  LCD IO delay
  * @param  Delay:    Delay in ms
  * @retval int32_t:  Error status
  */
static int32_t LCD_IO_Delay(uint32_t Delay)
{
    LCD_Delay(Delay);
    return BSP_ERROR_NONE;
}


/**
  * @brief HCI Transport Layer Low Level Interrupt Service Routine
  * @param  None
  * @retval None
  */
void LCD_TERisingCallback(void)
{
    LCD_SignalTearingEffectEvent(1, 0);
}

/**
  * @brief HCI Transport Layer Low Level Interrupt Service Routine
  * @param  None
  * @retval None
  */
void LCD_TEFallingCallback(void)
{
    LCD_SignalTearingEffectEvent(0, 0);
}

/**
  * @brief  Signal Transfer Event.
  * @param  State:        Event value.
  * @param  Line:         Line counter.
  */
__WEAK void LCD_SignalTearingEffectEvent(uint8_t State, uint16_t Line)
{
    /* Prevent unused argument(s) compilation warning */;
    (void)Line;

    /* This is the user's Callback to be implemented at the application level */
    if(State)
    {
      /* TE event is done : de-allow display refresh */
    }
    else
    {
      /* TE event is received : allow display refresh */
    }
}
