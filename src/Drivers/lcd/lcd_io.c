#include "lcd_conf.h"
#include "lcd_errno.h"
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

    return ret;
}

/* DeInitializes LCD low level
  */
static int32_t LCD_IO_DeInit(void)
{
    int32_t ret = BSP_ERROR_NONE;

    ret = LCD_SPI_DeInit();

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
    int32_t ret = BSP_ERROR_NONE;

    LCD_CS_LOW();

    /* Send Data */
//    ret = LCD_SPI_Send_DMA(pData, Length);

    return ret;
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

