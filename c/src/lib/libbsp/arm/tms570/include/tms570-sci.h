/**
 * @file
 * @ingroup tms570_sci
 * @brief UART support.
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


#ifndef LIBBSP_ARM_TMS570_SCI_H
#define LIBBSP_ARM_TMS570_SCI_H

#include <libchip/serial.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup tms570_sci UART Support
 * @ingroup arm_tms570
 * @brief UART Support
 */

extern const console_fns tms570_uart_fns;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_TMS570_SCI_H */
