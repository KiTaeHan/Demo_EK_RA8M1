#include "tx_api.h"

#include "lcd_errno.h"
#include "lcd_conf.h"

// ISR Callback
void LCD_spi_callback(spi_callback_args_t *p_args)
{
    (void)p_args;
}

void LCD_ext_irq11_callback(external_irq_callback_args_t *p_args)
{
    bsp_io_level_t status;

    if(11 == p_args->channel)
    {
        R_IOPORT_PinRead(&g_ioport_ctrl, LCD_TE, &status);
        if(BSP_IO_LEVEL_HIGH == status)
        {

        }
        else
        {

        }
    }
}

int32_t RA8M1_SPI1_Init(void)
{
    int32_t ret = BSP_ERROR_NONE;

    if(R_SPI_B_Open(&LCD_spi0_ctrl, &LCD_spi0_cfg) != FSP_SUCCESS)
    {
        ret = BSP_ERROR_BUS_FAILURE;
    }

    return ret;
}

int32_t RA8M1_SPI1_DeInit(void)
{
    int32_t ret = BSP_ERROR_NONE;

    if(R_SPI_B_Close(&LCD_spi0_ctrl) != FSP_SUCCESS)
    {
        ret = BSP_ERROR_BUS_FAILURE;
    }
    if(R_SPI_B_Open(&LCD_spi0_ctrl, &LCD_spi0_cfg) != FSP_SUCCESS)
    {
        ret = BSP_ERROR_BUS_FAILURE;
    }

    return ret;
}

int32_t RA8M1_SPI1_Send(uint8_t *pData, uint32_t Length)
{
  int32_t ret = BSP_ERROR_NONE;

  if(R_SPI_B_Write(&LCD_spi0_ctrl, (void*)pData, Length, SPI_BIT_WIDTH_8_BITS) != FSP_SUCCESS)
  {
      ret = BSP_ERROR_UNKNOWN_FAILURE;
  }

  return ret;
}




void LCD_RST_LOW()
{
    R_BSP_PinWrite(LCD_RESET, BSP_IO_LEVEL_LOW);
}

void LCD_RST_HIGH()
{
    R_BSP_PinWrite(LCD_RESET, BSP_IO_LEVEL_HIGH);
}

void LCD_CS_LOW()
{
    R_BSP_PinWrite(LCD_CS, BSP_IO_LEVEL_LOW);
}

void LCD_CS_HIGH()
{
    R_BSP_PinWrite(LCD_CS, BSP_IO_LEVEL_HIGH);
}

// Command select
void LCD_DC_LOW()
{
    R_BSP_PinWrite(LCD_DCX, BSP_IO_LEVEL_LOW);
}

// Data select
void LCD_DC_HIGH()
{
    R_BSP_PinWrite(LCD_DCX, BSP_IO_LEVEL_HIGH);
}

void UserDelay_10MS(int ms)
{
    tx_thread_sleep(ms);
}
