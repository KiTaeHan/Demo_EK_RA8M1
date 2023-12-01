#include "tx_api.h"

#include "lcd_errno.h"
#include "lcd_conf.h"

#define RESET_VALUE    0x00

static volatile spi_event_t LCD_spi_EventFlag = RESET_VALUE;

#if 0
static int LCD_spi_EventCheck(void);

static int LCD_spi_EventCheck(void)
{
    int count = 0x7FFFFFF;

    while(SPI_EVENT_TRANSFER_COMPLETE != LCD_spi_EventFlag)
    {
        count--;
        if(RESET_VALUE >= count)
        {
            // SPI blocked in W/R operation
            return -1;
        }
        else if(SPI_EVENT_TRANSFER_ABORTED == LCD_spi_EventFlag)
        {
            // SPI transfer aborted.
            return -1;
        }
        else
        {
            // SPI error
            return -1;
        }
    }

    return 0;
}
#endif

// ISR Callback
void LCD_spi_callback(spi_callback_args_t *p_args)
{
    if(SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
       LCD_spi_EventFlag =  SPI_EVENT_TRANSFER_COMPLETE;
    }
    else
    {
       LCD_spi_EventFlag =  SPI_EVENT_TRANSFER_ABORTED;
    }
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
 /*
    if(R_SPI_B_Open(&LCD_spi0_ctrl, &LCD_spi0_cfg) != FSP_SUCCESS)
    {
        ret = BSP_ERROR_BUS_FAILURE;
    }
*/

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

int32_t  RA8M1_SPI1_Recv(uint8_t *pData, uint32_t Length)
{
    int32_t ret = BSP_ERROR_NONE;

    if(R_SPI_B_Read(&LCD_spi0_ctrl, (void*)pData, Length, SPI_BIT_WIDTH_8_BITS) != FSP_SUCCESS)
    {
        ret = BSP_ERROR_UNKNOWN_FAILURE;
    }

    return ret;
}

uint32_t RA8M1_GetTick(void)
{
    uint32_t tick = 0;

    tick = (uint32_t)tx_time_get();

    return tick;
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

void UserDelay_MS(uint32_t  ms)
{
    tx_thread_sleep(ms);
}
