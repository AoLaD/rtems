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

#include <rtems/bspIo.h>
#include <stdint.h>

#define UART_FLR (*(volatile uint32_t *)(0xFFF7E500U+0x1C))
#define UART_TD (*(volatile uint32_t *)(0xFFF7E500U+0x38))

static void tms570_putc(char ch)
{
  while ((UART_FLR & 0x100) == 0); /* wait until busy */
  UART_TD = ch;
}

static void console_output(char c)
{
  if (c == '\n') {
    char r = '\r';
    tms570_putc(r);
  }
  tms570_putc(c);
}

BSP_output_char_function_type BSP_output_char = console_output;
