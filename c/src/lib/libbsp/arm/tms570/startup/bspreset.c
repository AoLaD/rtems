/**
 * @file bspreset.c
 *
 * @ingroup tms570
 *
 * @brief Reset code.
 */

/*
 * Copyright (c) 2015 Taller Technologies.
 *
 * @author Martin Galvan <martin.galvan@tallertechnologies.com>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/bootcard.h>
#include <bsp/tms570.h>
#include <bsp/start.h>

#define SYSECR (*(uint32_t *)0xFFFFFFE0u) /* System Exception Control Register */
#define SYSECR_RESET 0x80000u

static void handle_esm_errors(uint32_t esm_irq_channel)
{
   /* ESMR3 errors don't generate interrupts. */
   if (esm_irq_channel < 0x20u) {
     TMS570_ESM.SR[0] = 1 << esm_irq_channel;
   } else if (esm_irq_channel < 0x40u) {
     TMS570_ESM.SR[1] = 1 << (esm_irq_channel - 32u);
   } else if (esm_irq_channel < 0x60u) {
     TMS570_ESM.SR4 = 1 << (esm_irq_channel - 64u);
   }
}

void bsp_reset(void)
{
   uint32_t esm_irq_channel = TMS570_ESM.IOFFHR - 1;

   if (esm_irq_channel) {
     handle_esm_errors(esm_irq_channel);
   }

   /* Reset the board */
   SYSECR = SYSECR_RESET;
}
