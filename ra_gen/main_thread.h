/* generated thread header file - do not edit */
#ifndef MAIN_THREAD_H_
#define MAIN_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void main_thread_entry(void);
                #else
extern void main_thread_entry(void);
#endif
#include "r_adc.h"
#include "r_adc_api.h"
FSP_HEADER
/** ADC on ADC Instance. */
extern const adc_instance_t mic_adc04;

/** Access the ADC instance using these structures when calling API functions directly (::p_api is not used). */
extern adc_instance_ctrl_t mic_adc04_ctrl;
extern const adc_cfg_t mic_adc04_cfg;
extern const adc_channel_cfg_t mic_adc04_channel_cfg;

#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif

#ifndef NULL
#define ADC_DMAC_CHANNELS_PER_BLOCK_NULL  1
#endif
FSP_FOOTER
#endif /* MAIN_THREAD_H_ */
