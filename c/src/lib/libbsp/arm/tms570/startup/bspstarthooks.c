/**
 * @file bspstarthooks.c
 *
 * @ingroup tms570
 *
 * @brief First configurations and initializations to the correct
 *              functionality of the board.
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
 * by embedded brains GmbH and others
 * 
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/start.h>


BSP_START_TEXT_SECTION void bsp_start_hook_0( void )
{
  printk("StartHook0\n");
  //tms570_init_main_oscillator();
  //tms570_init_pll();
}

BSP_START_TEXT_SECTION void bsp_start_hook_1( void )
{
  printk("StartHook1\n");
  bsp_start_copy_sections();
  bsp_start_clear_bss();
  while(1)
  printk("StartHook1-end\n");
  /* At this point we can use objects outside the .start section  */
}
