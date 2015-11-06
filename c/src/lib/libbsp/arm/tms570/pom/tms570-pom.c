/**
 * @file tms570-pom.c
 *
 * @ingroup tms570
 *
 * @brief TMS570 Parameter Overlay Module functions definitions.
 */

 /*
 * Copyright (c) 2014 Pavel Pisa <pisa@cmp.felk.cvut.cz>
 *
 * Czech Technical University in Prague
 * Zikova 1903/4
 * 166 36 Praha 6
 * Czech Republic
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <stdint.h>
#include <bsp/tms570-pom.h>
#include <bsp/linker-symbols.h>
#include <rtems/score/armv4.h>
#include <bsp.h>

typedef struct{
  uint32_t reserved;
  uint32_t undefEntry;
  uint32_t svcEntry;
  uint32_t prefetchEntry;
  uint32_t dabort;
  uint32_t reservedEntry;
  uint32_t IRQVECREG;
  uint32_t FIQVECREG;
}vec_remap_table;
void block(void);
void block(void){
  while(1);
}

/**
 * @brief remaps vector table
 *
 * transfer the rtems start vector table to address 0x0
 *
 * @retval Void
 */
void tms570_pom_remap(void)
{
  int i;
  uint32_t vec_overlay_start = 0x08000000;
  //uint32_t temp = 0;

  memcpy((void*)vec_overlay_start, bsp_start_vector_table_begin, 64);
  vec_remap_table* vec_table = (vec_remap_table*)(vec_overlay_start+32);
  vec_table->undefEntry = (uint32_t)&block;
  vec_table->svcEntry = (uint32_t)&block;
  vec_table->prefetchEntry = (uint32_t)&block;//_ARMV4_Exception_prefetch_abort;
  vec_table->dabort = (uint32_t)&block;//_ARMV4_Exception_data_abort;
  vec_table->IRQVECREG = (uint32_t)&_ARMV4_Exception_interrupt;
  vec_table->FIQVECREG = (uint32_t)&block;//_ARMV4_Exception_interrupt;
  //memcpy((void*)vec_overlay_start, bsp_start_vector_table_begin, 64);

  TMS570_POM.GLBCTRL = 0;

  for ( i = 0; i < TMS570_POM_REGIONS; ++i ) {
    TMS570_POM.REG[i].REGSIZE = TMS570_POM_REGSIZE_SIZE(TMS570_POM_REGSIZE_DISABLED);
  }

  TMS570_POM.REG[0].PROGSTART = TMS570_POM_PROGSTART_STARTADDRESS(64);
  TMS570_POM.REG[0].OVLSTART = TMS570_POM_OVLSTART_STARTADDRESS(vec_overlay_start);
  TMS570_POM.REG[0].REGSIZE = TMS570_POM_REGSIZE_SIZE(TMS570_POM_REGSIZE_64B);
  TMS570_POM.GLBCTRL = TMS570_POM_GLBCTRL_ON_OFF(0xa) |
                       TMS570_POM_GLBCTRL_ETO(0xa) |
                       (TMS570_POM_GLBCTRL_OTADDR(~0) & vec_overlay_start);
}
