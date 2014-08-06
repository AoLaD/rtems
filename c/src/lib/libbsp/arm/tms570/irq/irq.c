/**
 * @file
 *
 * @ingroup bsp_interrupt
 *
 * @brief TMS570 interrupt support.
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

#include <rtems/score/armv4.h>

#include <bsp.h>
#include <bsp/irq-generic.h>
#include <bsp/tms570-vim.h>
#include <bsp/irq.h>
#include <rtems/score/armv4.h>


static inline bool tms570_irq_is_valid(rtems_vector_number vector)
{
  return (vector <= BSP_INTERRUPT_VECTOR_MAX) &&
         (vector > BSP_INTERRUPT_VECTOR_MIN);
}

unsigned int priorityTable[BSP_INTERRUPT_VECTOR_MAX+1];//will be deleted

void tms570_irq_set_priority(rtems_vector_number vector, unsigned priority){
  if (tms570_irq_is_valid(vector)) {
    priorityTable[vector] = priority;
  }
}

unsigned tms570_irq_get_priority(rtems_vector_number vector){
  if (tms570_irq_is_valid(vector)) {
   return priorityTable[vector];
 }
 //not much save
}

void bsp_interrupt_dispatch(void)
{

  rtems_vector_number vector = TMS570_VIM.IRQINDEX-1;

  bsp_interrupt_handler_dispatch(vector);
}

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
  if(!tms570_irq_is_valid(vector))
    return RTEMS_INVALID_ID;

  TMS570_VIM.REQENASET[vector >> 5] = 1 << (vector & 0x1f);

  return RTEMS_SUCCESSFUL;
}



rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  if(!tms570_irq_is_valid(vector))
    return RTEMS_INVALID_ID;

  TMS570_VIM.REQENACLR[vector >> 5] = 1 << (vector & 0x1f);

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_facility_initialize(void)
{
  void (**vim_vec)(void) = (void (**)(void)) 0xFFF82000;
  unsigned int value = 0x00010203;
  unsigned int i = 0;
  uint32_t sctlr;

  /* disable interrupts */
  for(i = 0; i < 3; i++)
    TMS570_VIM.REQENACLR[i] = 0xffffffff;
  /* map default events on interrupt vectors */
  for(i=0;i<24;i+=1,value += 0x04040404)
    TMS570_VIM.CHANCTRL[i] = value;
  /* set all vectors as IRQ (not FIR) */
  TMS570_VIM.FIRQPR[0] = 3;
  TMS570_VIM.FIRQPR[1] = 0;
  TMS570_VIM.FIRQPR[2] = 0;

  /*_CPU_ISR_install_vector(ARM_EXCEPTION_IRQ, _ARMV4_Exception_interrupt, NULL);*/
  for(i = 0; i <= 94; i++)
    vim_vec[i] = _ARMV4_Exception_interrupt;

  /* Clear bit VE in SCTLR register to not use VIM IRQ exception bypass*/
  asm volatile ("mrc p15, 0, %0, c1, c0, 0\n": "=r" (sctlr));
  sctlr &= ~(1 << 24);
  asm volatile ("mcr p15, 0, %0, c1, c0, 0\n": : "r" (sctlr));

  return RTEMS_SUCCESSFUL;
}



