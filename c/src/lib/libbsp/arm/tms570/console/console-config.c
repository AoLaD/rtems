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
#include <libchip/serial.h>
#include <bsp/tms570-sci.h>


unsigned long Console_Configuration_Count = 1;

console_tbl Console_Configuration_Ports [] = {
  {
    .sDeviceName = "/dev/ttyS0",
    .deviceType = SERIAL_CUSTOM,
    .pDeviceFns = &tms570_uart_fns,
    .deviceProbe = NULL,
    .pDeviceFlow = NULL,
    .ulMargin = 0,
    .ulHysteresis = 0,
    .pDeviceParams = (void *) 115200,
    .ulCtrlPort1 = 0xe0000000,
    .ulCtrlPort2 = 0,
    .ulDataPort = 0,
    .getRegister = NULL,
    .setRegister = NULL,
    .getData = NULL,
    .setData = NULL,
    .ulClock = 0,
    //.ulIntVector = ZYNQ_IRQ_UART_0
  }
};
