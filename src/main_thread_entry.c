#include <stdio.h>

#include "main_thread.h"
#include "RTT/SEGGER_RTT.h"

#include "syscall.h"
#include "app_display.h"

#define UART_BUFFER_SIZE        1024

int system_init(void);
int LCD_Display_Init(void);

volatile bool log_TXComplete;

// ISR callback functions
void ext_isr_irq2(external_irq_callback_args_t *p_args)
{
    bsp_io_level_t pin_status;

    if(p_args->channel == 2)
    {
        R_IOPORT_PinRead(&g_ioport_ctrl, MIC_INT, &pin_status);
        if(BSP_IO_LEVEL_LOW == pin_status)
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, LED1, BSP_IO_LEVEL_HIGH);
        }
        else
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, LED1, BSP_IO_LEVEL_LOW);
        }
    }
}

void log_uart_callback(uart_callback_args_t *p_args)
{
    switch(p_args->event)
    {
        case UART_EVENT_TX_COMPLETE:
            log_TXComplete = true;
            break;
        default:
            break;
    }
}



// glibc callback functions
int _write(int file, char *buffer, int count)
{
    (void)file;
    int tx_count;
    int i;

    for(i=0, tx_count=0; i<count; i++, tx_count++)
    {
        log_TXComplete = false;
        R_SCI_B_UART_Write(&log_uart0_ctrl, (uint8_t const*)(buffer+i), 1);
        while(log_TXComplete){}
    }

    return tx_count;
}


int LCD_Display_Init(void)
{
    uint32_t LCD_Width = 0;
    uint32_t LCD_Height = 0;
    uint32_t LCD_Orientation = 0;

    LCD_Probe(LCD_ORIENTATION_PORTRAIT);

    if((LCD_GetXSize(&LCD_Width) != BSP_ERROR_NONE) ||
       (LCD_GetYSize(&LCD_Height) != BSP_ERROR_NONE) ||
       (LCD_GetOrientation(&LCD_Orientation) != BSP_ERROR_NONE) )
    {
        printf("Error get LCD info\r\n");
        return -1;
    }

    APP_LCD_Clear(0, 0, LCD_Width, LCD_Height);
    if(LCD_DisplayOn() != BSP_ERROR_NONE)
    {
        printf("Error LCD display ON\r\n");
        return -1;
    }

    return 0;
}

// user define functions
int system_init(void)
{
    fsp_err_t status = FSP_SUCCESS;

    // ADC init
    status = R_ADC_Open(&mic_adc04_ctrl, &mic_adc04_cfg);
    if(FSP_SUCCESS != status){
        SEGGER_RTT_printf(0, "ADC open Failed\r\n");
        return status;
    }
    R_ADC_ScanCfg(&mic_adc04_ctrl, &mic_adc04_channel_cfg);
    R_ADC_ScanStart(&mic_adc04_ctrl);

    // E_IRQ init
    R_ICU_ExternalIrqOpen(&mic_external_irq2_ctrl, &mic_external_irq2_cfg);
    R_ICU_ExternalIrqEnable(&mic_external_irq2_ctrl);

    // Uart init
    R_SCI_B_UART_Open(&log_uart0_ctrl, &log_uart0_cfg);
    setvbuf(stdout, NULL, _IONBF, UART_BUFFER_SIZE);

    LCD_Display_Init();

    return status;
}

/* Main Thread entry function */
void main_thread_entry(void)
{
    uint16_t mic_data=0;

    system_init();

    printf("Start Application\r\n");

    while(1)
    {
        unsigned char data = 0xAA;
        R_SPI_B_Write(&LCD_spi0_ctrl, &data, 1, SPI_BIT_WIDTH_8_BITS);
        tx_thread_sleep (1);
    }

    while(1)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_RED, BSP_IO_LEVEL_HIGH);
        tx_thread_sleep (500);
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED_RED, BSP_IO_LEVEL_LOW);
        tx_thread_sleep (500);
    }

    /* TODO: add your own code here */
    while (1)
    {
        R_ADC_Read(&mic_adc04_ctrl, ADC_CHANNEL_4, &mic_data);
        SEGGER_RTT_printf(0, "MIC: %d\r\n", mic_data);

        printf("MIC: %d\r\n", mic_data);

        tx_thread_sleep (1);
    }
}
