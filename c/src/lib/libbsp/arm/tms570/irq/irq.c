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


#include <bsp.h>

/**
 * @brief Checks if the current interrupt vector lenght is valid or not.
 *
 * @param  vector The current interrupt vector lenght .
 * @return  TRUE if valid.
 *          FALSE otherwise.
 */
static inline bool tms570_irq_is_valid( const rtems_vector_number vector )
{
  return 0;
}

void tms570_irq_set_priority(
  const rtems_vector_number vector,
  unsigned                  priority
)
{
  
}

unsigned tms570_irq_get_priority( const rtems_vector_number vector )
{
  unsigned priority;

  return priority;
}
