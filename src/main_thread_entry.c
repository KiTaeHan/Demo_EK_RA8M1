#include "main_thread.h"
#include "RTT/SEGGER_RTT.h"

int system_init(void);

int system_init(void)
{
    fsp_err_t status = FSP_SUCCESS;

    status = R_ADC_Open(&mic_adc04_ctrl, &mic_adc04_cfg);
    if(FSP_SUCCESS != status){
        SEGGER_RTT_printf(0, "ADC open Failed\r\n");
        return status;
    }
    R_ADC_ScanCfg(&mic_adc04_ctrl, &mic_adc04_channel_cfg);
    R_ADC_ScanStart(&mic_adc04_ctrl);

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
