/**
 * @file
 *
 * @ingroup tms570_clocks
 *
 * @brief System clocks.
 */

/*
 * Copyright (c) 2008-2012 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/system-clocks.h>

/**
 * @brief Internal RC oscillator frequency in [Hz].
 */
#define TMS570_OSCILLATOR_INTERNAL 4000000u

#ifndef TMS570_OSCILLATOR_MAIN
#error "unknown main oscillator frequency"
#endif

#ifndef TMS570_OSCILLATOR_RTC
#error "unknown RTC oscillator frequency"
#endif

inline unsigned tms570_sysclk( void );

void tms570_timer_initialize( void )
{
  /* Reset timer */
  TMS570_T1TCR = TCR_RST;
  /* Set timer mode */
  TMS570_T1CTCR = 0u;
  /* Set prescaler to zero */
  TMS570_T1PR = 0u;
  /* Reset all interrupt flags */
  TMS570_T1IR = 0xffU;
  /* Do not stop on a match */
  TMS570_T1MCR = 0u;
  /* No captures */
  TMS570_T1CCR = 0u;
  /* Start timer */
  TMS570_T1TCR = TCR_EN;
}

void tms570_micro_seconds_delay( const unsigned us )
{
  const unsigned start = tms570_get_timer1();
  const unsigned delay = us * ( TMS570_PCLK / 1000000u );
  unsigned       elapsed = 0u;

  do {
    elapsed = tms570_get_timer1() - start;
  } while ( elapsed < delay );
}

unsigned tms570_sysclk( void )
{
  return ( TMS570_SCB.clksrcsel & TMS570_SCB_CLKSRCSEL_CLKSRC ) != 0u ?
         TMS570_OSCILLATOR_MAIN : TMS570_OSCILLATOR_INTERNAL;
}

unsigned tms570_pllclk( void )
{
  const unsigned sysclk = tms570_sysclk();
  const unsigned pllstat = ( TMS570_SCB.pll_0 ).stat;
  const unsigned enabled_and_locked = TMS570_PLL_STAT_PLLE |
                                      TMS570_PLL_STAT_PLOCK;
  unsigned pllclk = 0u;

  if ( ( pllstat & enabled_and_locked ) == enabled_and_locked ) {
    unsigned m = TMS570_PLL_SEL_MSEL_GET( pllstat ) + 1u;
    pllclk = sysclk * m;
  }

  /* else implies that the pllstat is unlocked. Also,
     there is nothing to do. */

  return pllclk;
}

unsigned tms570_cclk( void )
{
  const unsigned cclksel = TMS570_SCB.cclksel;
  unsigned       cclk_in = 0u;
  unsigned       cclk = 0u;

  if ( ( cclksel & TMS570_SCB_CCLKSEL_CCLKSEL ) != 0u ) {
    cclk_in = tms570_pllclk();
  } else {
    cclk_in = tms570_sysclk();
  }

  cclk = cclk_in / TMS570_SCB_CCLKSEL_CCLKDIV_GET( cclksel );

  return cclk;
}

CPU_Counter_ticks _CPU_Counter_read( void )
{
  return tms570_get_timer1();
}

inline CPU_Counter_ticks _CPU_Counter_difference(
  CPU_Counter_ticks second,
  CPU_Counter_ticks first
)
{
  return second - first;
}

