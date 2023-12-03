#include "tx_api.h"

#include "lcd_errno.h"
#include "lcd_conf.h"

#define LCD_SPI_USE_RTOS        1
#define RESET_VALUE    0x00

static int LCD_spi_EventCheck(void);

#if LCD_SPI_USE_RTOS

TX_EVENT_FLAGS_GROUP LCD_Spi_EventFlag;

static int LCD_spi_EventCheck(void)
{
    ULONG event;

    // RA8M1 SPI events
    tx_event_flags_get(&LCD_Spi_EventFlag, 0xFF, TX_OR_CLEAR, &event, TX_WAIT_FOREVER);

    if(SPI_EVENT_TRANSFER_COMPLETE != event)
    {
        return -1;
    }

    return 0;
}
#else
static volatile spi_event_t LCD_spi_EventFlag = RESET_VALUE;

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
#if LCD_SPI_USE_RTOS
    // Set event flags
    tx_event_flags_set(&LCD_Spi_EventFlag, p_args->event, TX_OR);
    /* Optionally, resume a higher-priority thread if needed */
//    tx_interrupt_control(new_posture);

#else
    if(SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
       LCD_spi_EventFlag =  SPI_EVENT_TRANSFER_COMPLETE;
    }
    else
    {
       LCD_spi_EventFlag =  SPI_EVENT_TRANSFER_ABORTED;
    }
#endif
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

#if LCD_SPI_USE_RTOS
    UINT status;

    status = tx_event_flags_create (&LCD_Spi_EventFlag, (CHAR*) "LCD Spi Event Flags");
    if (TX_SUCCESS != status)
    {
        return BSP_ERROR_COMPONENT_FAILURE;
    }
#endif

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

    if(LCD_spi_EventCheck())
    {
        ret = TX_WAIT_FOREVER;
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

    if(LCD_spi_EventCheck())
    {
        ret = TX_WAIT_FOREVER;
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
