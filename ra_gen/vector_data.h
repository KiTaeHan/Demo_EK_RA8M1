/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (1)
#endif
/* ISR prototypes */
void r_icu_isr(void);

#if __has_include("r_ioport.h")
        /* Vector table allocations */
        #define VECTOR_NUMBER_ICU_IRQ2 ((IRQn_Type) 0) /* ICU IRQ2 (External pin interrupt 2) */
        #define ICU_IRQ2_IRQn          ((IRQn_Type) 0) /* ICU IRQ2 (External pin interrupt 2) */
        #endif

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
