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

#include <bsp/tms570.h>
#include <bsp/dma.h>
#include <bsp/irq.h>

static void tms570_dma_copy_handler( void *arg )
{
}

rtems_status_code tms570_dma_copy_initialize( void )
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_dma_copy_release( void )
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_dma_copy(
  unsigned          channel,
  const void *const dest,
  const void *const src,
  size_t            n,
  const size_t      width
)
{
  rtems_status_code             status_code;
  return status_code;
}

rtems_status_code tms570_dma_copy_wait( const unsigned channel )
{
  rtems_status_code status_code;
  return status_code;
}
