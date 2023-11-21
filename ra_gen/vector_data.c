/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        #if __has_include("r_ioport.h")
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_b_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [1] = sci_b_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [2] = sci_b_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [3] = sci_b_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [4] = r_icu_isr, /* ICU IRQ2 (External pin interrupt 2) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_SCI0_RXI), /* SCI0 RXI (Receive data full) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TXI), /* SCI0 TXI (Transmit data empty) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TEI), /* SCI0 TEI (Transmit end) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_SCI0_ERI), /* SCI0 ERI (Receive error) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ2), /* ICU IRQ2 (External pin interrupt 2) */
        };
        #elif __has_include("r_ioport_b.h")
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_IRQ_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
            [BSP_PRV_IELS_ENUM(SCI0_RXI)] = sci_b_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [BSP_PRV_IELS_ENUM(SCI0_TXI)] = sci_b_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [BSP_PRV_IELS_ENUM(SCI0_TEI)] = sci_b_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [BSP_PRV_IELS_ENUM(SCI0_ERI)] = sci_b_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [BSP_PRV_IELS_ENUM(ICU_IRQ2)] = r_icu_isr, /* ICU IRQ2 (External pin interrupt 2) */
        };
        #endif
        #endif
