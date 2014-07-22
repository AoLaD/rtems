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
#include <bsp/irq.h>
#include <bsp/irq-generic.h>
//#include <bsp/vim.h>


typedef struct{
    int PARFLG; 	//InterruptVectorTableParityFlagRegister
    int PARCTL; 	//InterruptVectorTableParityControlRegister
    int ADDERR; 	//AddressParityErrorRegister
    int FBPARERR; 	//Fall-BackAddressParityErrorRegister
    int reserved1 [0x4/4];
    int IRQINDEX; 	//IRQIndexOffsetVectorRegister
    int FIQINDEX; 	//FIQIndexOffsetVectorRegister
    int reserved2 [0x8/4];
    int FIRQPR0; 	//FIQ/IRQProgramControlRegister0
    int FIRQPR1; 	//FIQ/IRQProgramControlRegister1
    int FIRQPR2; 	//FIQ/IRQProgramControlRegister2
    int reserved3 [0x4/4];
    int INTREQ0; 	//PendingInterruptReadLocationRegister0
    int INTREQ1; 	//PendingInterruptReadLocationRegister1
    int INTREQ2; 	//PendingInterruptReadLocationRegister2
    int reserved4 [0x4/4];
    int REQENASET0; 	//InterruptEnableSetRegister0
    int REQENASET1; 	//InterruptEnableSetRegister1
    int REQENASET2; 	//InterruptEnableSetRegister2
    int reserved5 [0x4/4];
    int REQENACLR0; 	//InterruptEnableClearRegister0
    int REQENACLR1; 	//InterruptEnableClearRegister1
    int REQENACLR2; 	//InterruptEnableClearRegister2
    int reserved6 [0x4/4];
    int WAKEENASET0; 	//Wake-upEnableSetRegister0
    int WAKEENASET1; 	//Wake-upEnableSetRegister1
    int WAKEENASET2; 	//Wake-upEnableSetRegister2
    int reserved7 [0x4/4];
    int WAKEENACLR0; 	//Wake-upEnableClearRegister0
    int WAKEENACLR1; 	//Wake-upEnableClearRegister1
    int WAKEENACLR2; 	//Wake-upEnableClearRegister2
    int reserved8 [0x4/4];
    int IRQVECREG; 	//IRQInterruptVectorRegister
    int FIQVECREG; 	//FIQInterruptVectorRegister
    int CAPEVT; 	//CaptureEventRegister
    int CHANCTRL [0x5c/4]; //VIM Interrupt Control Register (PARSER ERROR)
}VIM;
VIM* vim = (VIM*)0xFFFFFDEC;

static inline bool tms570_irq_is_valid(rtems_vector_number vector)
{
  return vector <= BSP_INTERRUPT_VECTOR_MAX && vector > BSP_INTERRUPT_VECTOR_MIN;
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
	
  rtems_vector_number vector = vim->IRQINDEX-1;
     
  bsp_interrupt_handler_dispatch(vector);
}

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
  unsigned int * enable_reg;
  
  if(!tms570_irq_is_valid(vector))
	 return RTEMS_INVALID_ID;  
  
  if(vector<32)
	 enable_reg = vim->REQENASET0;
  else if(vector<64 && vector >= 32)
     enable_reg = vim->REQENASET1;
  else if(vector<96 && vector >= 64)
     enable_reg = vim->REQENASET2;
  else
	 return RTEMS_INVALID_ID;
	 
  *enable_reg |= (1<<(vector%32));    
  return RTEMS_SUCCESSFUL;
}



rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  unsigned int * disable_reg;
  
  if(!tms570_irq_is_valid(vector))
    return RTEMS_INVALID_ID; 
  
  if(vector<32)
	 disable_reg = vim->REQENACLR0;
  else if(vector<64 && vector >= 32)
     disable_reg = vim->REQENACLR1;
  else if(vector<96 && vector >= 64)
     disable_reg = vim->REQENACLR2;
  else
	 return RTEMS_INVALID_ID;
	 
  *disable_reg |= (1<<(vector%32));    
  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_facility_initialize(void)
{
	/*disable interrupts*/
  vim->REQENACLR0 = 0xffffffff;
  vim->REQENACLR1 = 0xffffffff;
  vim->REQENACLR2 = 0xffffffff;
    /*map default events on interrupt vectors*/
  unsigned int value = 0x00010203,i=0;
  for(i=0;i<24;i+=1,value += 0x01010101){
	  vim->CHANCTRL[i] = value;
  }
    /*set all vectors as IRQ (not FIR)*/
  vim->FIRQPR0 = 3;
  vim->FIRQPR1 = 0;
  vim->FIRQPR2 = 0;

  //_CPU_ISR_install_vector(ARM_EXCEPTION_IRQ, _ARMV4_Exception_interrupt, NULL);

  return RTEMS_SUCCESSFUL;
}



