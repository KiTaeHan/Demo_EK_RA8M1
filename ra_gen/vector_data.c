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
            [4] = spi_b_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [5] = spi_b_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [6] = spi_b_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [7] = spi_b_eri_isr, /* SPI0 ERI (Error) */
            [8] = r_icu_isr, /* ICU IRQ11 (External pin interrupt 11) */
            [9] = r_icu_isr, /* ICU IRQ2 (External pin interrupt 2) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_SCI0_RXI), /* SCI0 RXI (Receive data full) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TXI), /* SCI0 TXI (Transmit data empty) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TEI), /* SCI0 TEI (Transmit end) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_SCI0_ERI), /* SCI0 ERI (Receive error) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_SPI0_RXI), /* SPI0 RXI (Receive buffer full) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_SPI0_TXI), /* SPI0 TXI (Transmit buffer empty) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_SPI0_TEI), /* SPI0 TEI (Transmission complete event) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_SPI0_ERI), /* SPI0 ERI (Error) */
            [8] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ11), /* ICU IRQ11 (External pin interrupt 11) */
            [9] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ2), /* ICU IRQ2 (External pin interrupt 2) */
        };
        #elif __has_include("r_ioport_b.h")
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_IRQ_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
            [BSP_PRV_IELS_ENUM(SCI0_RXI)] = sci_b_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [BSP_PRV_IELS_ENUM(SCI0_TXI)] = sci_b_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [BSP_PRV_IELS_ENUM(SCI0_TEI)] = sci_b_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [BSP_PRV_IELS_ENUM(SCI0_ERI)] = sci_b_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [BSP_PRV_IELS_ENUM(SPI0_RXI)] = spi_b_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [BSP_PRV_IELS_ENUM(SPI0_TXI)] = spi_b_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [BSP_PRV_IELS_ENUM(SPI0_TEI)] = spi_b_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [BSP_PRV_IELS_ENUM(SPI0_ERI)] = spi_b_eri_isr, /* SPI0 ERI (Error) */
            [BSP_PRV_IELS_ENUM(ICU_IRQ11)] = r_icu_isr, /* ICU IRQ11 (External pin interrupt 11) */
            [BSP_PRV_IELS_ENUM(ICU_IRQ2)] = r_icu_isr, /* ICU IRQ2 (External pin interrupt 2) */
        };
        #endif
        #endif
