/* Includes ------------------------------------------------------------------*/
#include "ili9341_reg.h"

  
/**
  * @brief  Read ILI9341 component registers
  * @param  ctx component context
  * @param  reg Register to read from
  * @param  pdata Pointer to data buffer
  * @param  length Number of data to read  
  * @retval Component status
  */
int32_t ili9341_read_reg(ili9341_ctx_t *ctx, volatile uint8_t* reg, uint32_t length)
{
  return ctx->ReadReg(ctx->handle, reg, length);
}

/**
  * @brief  Write ILI9341 component registers
  * @param  ctx component context
  * @param  reg Register to write to
  * @param  pdata Pointer to data buffer
  * @param  length Number of data to write  
  * @retval Component status
  */
int32_t ili9341_write_reg(ili9341_ctx_t *ctx, volatile uint8_t* reg, uint32_t length)
{
  return ctx->WriteReg(ctx->handle, reg, length);
}

/**
  * @brief  Send data
  * @param  ctx    Component context
  * @param  pdata  data to write
  * @param  Length Length of data to write
  * @retval Component status
  */
int32_t ili9341_send_data(ili9341_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  return ctx->SendData(ctx->handle, pdata, length);
}

/**
  * @brief  Send data using DMA
  * @param  ctx    Component context
  * @param  pdata  data to write
  * @param  Length Length of data to write
  * @retval Component status
  */
int32_t ili9341_send_data_dma(ili9341_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  return ctx->SendDataDMA(ctx->handle, pdata, length);
}

/**
  * @brief  Receive data
  * @param  ctx    Component context
  * @param  pdata  data to read
  * @param  Length Length of data to read
  * @retval Component status
  */
int32_t ili9341_recv_data(ili9341_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  return ctx->RecvData(ctx->handle, pdata, length);
}

/**
  * @brief  Receive data using DMA
  * @param  ctx    Component context
  * @param  pdata  data to read
  * @param  Length Length of data to read
  * @retval Component status
  */
int32_t ili9341_recv_data_dma(ili9341_ctx_t *ctx, uint8_t *pdata, uint32_t length)
{
  return ctx->RecvDataDMA(ctx->handle, pdata, length);
}
