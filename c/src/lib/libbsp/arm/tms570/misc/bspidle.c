/**
 * @file
 *
 * @ingroup tms570
 *
 * @brief Idle task.
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

#include <bsp.h>
#include <bsp/tms570.h>

void*bsp_idle_thread( const uintptr_t ignored )
{
  while ( true ) {
  }
}
