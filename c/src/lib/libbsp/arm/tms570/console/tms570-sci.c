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

#include <bspopts.h>

#include <libchip/sersupp.h>
#include <bsp/tms570-sci.h>

#define UART_FLR (*(volatile uint32_t *)(0xFFF7E500U+0x1C))
#define UART_TD (*(volatile uint32_t *)(0xFFF7E500U+0x38))


static void tms570_uart_initialize(int minor)
{

}

static int tms570_uart_first_open(int major, int minor, void *arg)
{
  rtems_libio_open_close_args_t *oc = (rtems_libio_open_close_args_t *) arg;
  struct rtems_termios_tty *tty = (struct rtems_termios_tty *) oc->iop->data1;
  console_data *cd = &Console_Port_Data[minor];
  const console_tbl *ct = Console_Port_Tbl[minor];

  cd->termios_data = tty;
  rtems_termios_set_initial_baud(tty, (rtems_termios_baud_t) ct->pDeviceParams);

  return 0;
}

static int tms570_uart_last_close(int major, int minor, void *arg)
{
  return 0;
}

static int tms570_uart_read_polled(int minor)
{
  if (1) {
    return -1;
  } else {
    return 'A';
  }
}

static void tms570_uart_write_polled(int minor, char c)
{
  while ((UART_FLR & 0x100) == 0) {
	/* Wait */
  }

  UART_TD = c; 
}

static ssize_t tms570_uart_write_support_polled(
  int minor,
  const char *s,
  size_t n
)
{
  ssize_t i = 0;

  for (i = 0; i < n; ++i) {
    tms570_uart_write_polled(minor, s[i]);
  }

  return n;
}

static int tms570_uart_set_attribues(int minor, const struct termios *term)
{
  return -1;
}

const console_fns tms570_uart_fns = {
  .deviceProbe = libchip_serial_default_probe,
  .deviceFirstOpen = tms570_uart_first_open,
  .deviceLastClose = tms570_uart_last_close,
  .deviceRead = tms570_uart_read_polled,
  .deviceWrite = tms570_uart_write_support_polled,
  .deviceInitialize = tms570_uart_initialize,
  .deviceWritePolled = tms570_uart_write_polled,
  .deviceSetAttributes = tms570_uart_set_attribues,
  .deviceOutputUsesInterrupts = false
};
