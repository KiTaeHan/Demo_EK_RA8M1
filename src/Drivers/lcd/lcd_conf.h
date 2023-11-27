/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_CONF_H__
#define __LCD_CONF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_data.h"

/* Exported types ------------------------------------------------------------*/
#if 0
/* BUS IO Instance handler */
extern  SPI_HandleTypeDef                   hspi1;

/* DMA Instance handlers */
extern  DMA_HandleTypeDef                   hdma_spi1_rx;
extern  DMA_HandleTypeDef                   hdma_spi1_tx;

/* Tearing Effect EXTI handler */
extern EXTI_HandleTypeDef                   hexti_lcd_te;

/* HSync Timer Instance handler */
extern  TIM_HandleTypeDef                   htim2;
#endif

/* Exported constants --------------------------------------------------------*/
/* Number of LCD instances */
#define LCD_INSTANCES_NBR                   1U

/* BUS IO Instance handlers */
#define hLCDSPI                             hspi1

#define hLCDDMA_rx                          hdma_spi1_rx
#define hLCDDMA_tx                          hdma_spi1_tx

/* HSync Timer Instance handler */
#define hLCDTIM_HSync                       htim2
#define hLCDTIM                             htim2

/* BUS IO functions */
#define LCD_SPI_Init                        RA8M1_SPI1_Init
#define LCD_SPI_DeInit                      BSP_SPI1_DeInit
#define LCD_SPI_Send                        BSP_SPI1_Send
#define LCD_SPI_Recv                        BSP_SPI1_Recv
#define LCD_SPI_SendRecv                    BSP_SPI1_SendRecv
#define LCD_SPI_Send_DMA                    BSP_SPI1_Send_DMA
#define LCD_SPI_Recv_DMA                    BSP_SPI1_Recv_DMA
#define LCD_SPI_SendRecv_DMA                BSP_SPI1_SendRecv_DMA

#if 0
/* CS Pin mapping */
#define LCD_CS_GPIO_PORT                    GPIOB
#define LCD_CS_GPIO_PIN                     GPIO_PIN_5


#define LCD_DCX_GPIO_PORT                   GPIOB
#define LCD_DCX_GPIO_PIN                    GPIO_PIN_3

/* RESET Pin mapping */
#define LCD_RESET_GPIO_PORT                 GPIOA
#define LCD_RESET_GPIO_PIN                  GPIO_PIN_1

/* TE Pin mapping */
#define LCD_TE_GPIO_PORT                    GPIOA
#define LCD_TE_GPIO_PIN                     GPIO_PIN_0

#define LCD_TE_GPIO_LINE                    EXTI_LINE_0
#define LCD_TE_GPIO_IRQn                    EXTI0_1_IRQn

/* Tearing Effect EXTI handler */
#define H_EXTI_0                            hexti_lcd_te
#endif


int32_t RA8M1_SPI1_Init();


void LCD_RST_LOW();
void LCD_RST_HIGH();
void LCD_CS_LOW();
void LCD_CS_HIGH();
void LCD_DC_LOW();
void LCD_DC_HIGH();
void UserDelay_10MS(int ms);


#ifdef __cplusplus
}
#endif
#endif /* __LCD_CONF_H__ */
