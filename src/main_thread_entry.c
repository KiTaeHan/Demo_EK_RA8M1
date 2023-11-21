#include "main_thread.h"
#include "RTT/SEGGER_RTT.h"

int system_init(void);

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

    return status;
}

/* Main Thread entry function */
void main_thread_entry(void)
{
    uint16_t mic_data=0;

    system_init();

    /* TODO: add your own code here */
    while (1)
    {
        R_ADC_Read(&mic_adc04_ctrl, ADC_CHANNEL_4, &mic_data);
        SEGGER_RTT_printf(0, "MIC: %d\r\n", mic_data);

        tx_thread_sleep (1);
    }
}
