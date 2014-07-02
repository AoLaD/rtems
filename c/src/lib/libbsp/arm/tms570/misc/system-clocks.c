/**
 * @file
 *
 * @ingroup tms570_clocks
 *
 * @brief System clocks.
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

#include <bsp.h>
inline unsigned tms570_sysclk( void );

void tms570_timer_initialize( void )
{
}

void tms570_micro_seconds_delay( const unsigned us )
{
}

unsigned tms570_sysclk( void )
{
return 0;
}

unsigned tms570_pllclk( void )
{
  return 0;
}

unsigned tms570_cclk( void )
{
  return 0;
}

CPU_Counter_ticks _CPU_Counter_read( void )
{
  return 0;
}

inline CPU_Counter_ticks _CPU_Counter_difference(
  CPU_Counter_ticks second,
  CPU_Counter_ticks first
)
{
  return second - first;
}

