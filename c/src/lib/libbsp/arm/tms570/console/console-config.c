/**
 * @file
 *
 * @ingroup tms570
 *
 * @brief Console configuration.
 */

/*
 * Copyright (c) 2008-2011 embedded brains GmbH.  All rights reserved.
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

#include <libchip/serial.h>
#include <libchip/ns16550.h>

#include <bsp.h>
#include <bsp/io.h>
#include <bsp/irq.h>

/**
 * @brief Gets the uart register according to the current address.
 *
 * @param  addr Register address.
 * @param  i Index register.
 * @return  Uart register.
 */
static inline uint8_t tms570_uart_get_register(
  const uintptr_t addr,
  const uint8_t   i
)
{
  volatile uint32_t *reg = (volatile uint32_t *) addr;

  return (uint8_t) reg[ i ];
}

/**
 * @brief Sets the uart register address according to the value passed.
 *
 * @param  addr Register address.
 * @param  i Index register.
 * @param val Value to set.
 */
static inline void tms570_uart_set_register(
  const uintptr_t addr,
  const uint8_t   i,
  const uint8_t   val
)
{
  volatile uint32_t *reg = (volatile uint32_t *) addr;

  reg[ i ] = val;
}

/**
 * @brief Represents the uart configuration ports.
 */
console_tbl Console_Configuration_Ports[] = {
#ifdef TMS570_CONFIG_CONSOLE
  {
    .sDeviceName = "/dev/ttyS0",
    .deviceType = SERIAL_NS16550_WITH_FDR,
    .pDeviceFns = &ns16550_fns,
    .deviceProbe = NULL,
    .pDeviceFlow = NULL,
    .ulMargin = 16,
    .ulHysteresis = 8,
    .pDeviceParams = (void *) TMS570_UART_BAUD,
    .ulCtrlPort1 = UART0_BASE_ADDR,
    .ulCtrlPort2 = 0,
    .ulDataPort = UART0_BASE_ADDR,
    .getRegister = tms570_uart_get_register,
    .setRegister = tms570_uart_set_register,
    .getData = NULL,
    .setData = NULL,
    .ulClock = TMS570_PCLK,
    .ulIntVector = TMS570_IRQ_UART_0
  },
#endif
#ifdef TMS570_CONFIG_UART_1
  {
    .sDeviceName = "/dev/ttyS1",
    .deviceType = SERIAL_NS16550_WITH_FDR,
    .pDeviceFns = &ns16550_fns,
    .deviceProbe = tms570_uart_probe_1,
    .pDeviceFlow = NULL,
    .ulMargin = 16,
    .ulHysteresis = 8,
    .pDeviceParams = (void *) TMS570_UART_BAUD,
    .ulCtrlPort1 = UART1_BASE_ADDR,
    .ulCtrlPort2 = 0,
    .ulDataPort = UART1_BASE_ADDR,
    .getRegister = tms570_uart_get_register,
    .setRegister = tms570_uart_set_register,
    .getData = NULL,
    .setData = NULL,
    .ulClock = TMS570_PCLK,
    .ulIntVector = TMS570_IRQ_UART_1
  },
#endif
#ifdef TMS570_CONFIG_UART_2
  {
    .sDeviceName = "/dev/ttyS2",
    .deviceType = SERIAL_NS16550_WITH_FDR,
    .pDeviceFns = &ns16550_fns,
    .deviceProbe = tms570_uart_probe_2,
    .pDeviceFlow = NULL,
    .ulMargin = 16,
    .ulHysteresis = 8,
    .pDeviceParams = (void *) TMS570_UART_BAUD,
    .ulCtrlPort1 = UART2_BASE_ADDR,
    .ulCtrlPort2 = 0,
    .ulDataPort = UART2_BASE_ADDR,
    .getRegister = tms570_uart_get_register,
    .setRegister = tms570_uart_set_register,
    .getData = NULL,
    .setData = NULL,
    .ulClock = TMS570_PCLK,
    .ulIntVector = TMS570_IRQ_UART_2
  },
#endif
#ifdef TMS570_CONFIG_UART_3
  {
    .sDeviceName = "/dev/ttyS3",
    .deviceType = SERIAL_NS16550_WITH_FDR,
    .pDeviceFns = &ns16550_fns,
    .deviceProbe = tms570_uart_probe_3,
    .pDeviceFlow = NULL,
    .ulMargin = 16,
    .ulHysteresis = 8,
    .pDeviceParams = (void *) TMS570_UART_BAUD,
    .ulCtrlPort1 = UART3_BASE_ADDR,
    .ulCtrlPort2 = 0,
    .ulDataPort = UART3_BASE_ADDR,
    .getRegister = tms570_uart_get_register,
    .setRegister = tms570_uart_set_register,
    .getData = NULL,
    .setData = NULL,
    .ulClock = TMS570_PCLK,
    .ulIntVector = TMS570_IRQ_UART_3
  },
#endif
};

#define TMS570_UART_COUNT ( sizeof( Console_Configuration_Ports ) \
                             / sizeof( Console_Configuration_Ports[ 0 ] ) )

unsigned long Console_Configuration_Count = TMS570_UART_COUNT;
