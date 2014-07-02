/**
 * @file
 *
 * @ingroup tms570_dma
 *
 * @brief Direct memory access (DMA) support.
 */
/*
 * Copyright (c) 2014 Premysl Houdek <kom541000@gmail.com>
 *
 * Google Summer of Code 2014 at
 * Czech Technical University in Prague
 * Zikova 1903/4
 * 166 36 Praha 6
 * Czech Republic
 *
 * Based on LPC24xx and LPC1768 BSP
 * 
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */


#include <rtems/endian.h>


void tms570_dma_initialize( void )
{
}

rtems_status_code tms570_dma_channel_obtain( const unsigned channel )
{
  rtems_status_code status_code;
  return status_code;
}

void tms570_dma_channel_release( const unsigned channel )
{
}

void tms570_dma_channel_disable(
  const unsigned channel,
  const bool     force
)
{
}
