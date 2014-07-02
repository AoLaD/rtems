/**
 * @file timerbenchmark.c
 *
 * @ingroup tms570
 *
 * @brief Timer benchmark functions for the tms570 bsp.
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

#include <rtems.h>
#include <bsp.h>


void benchmark_timer_initialize( void )
{
}

uint32_t benchmark_timer_read( void )
{
  uint32_t delta = 0;

  return delta;
}

void benchmark_timer_disable_subtracting_average_overhead( bool find_avg_ovhead )
{
}
