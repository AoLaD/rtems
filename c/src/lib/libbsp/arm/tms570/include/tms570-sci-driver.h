/**
 * @file tms570-sci-driver.h
 *
 * @ingroup tms570
 *
 * @brief Declaration of serial's driver inner structure.
 */
#ifndef TMS570_SCI_DRIVER
#define TMS570_SCI_DRIVER

#include <rtems/termiostypes.h>
#include <rtems/irq.h>
#include <bsp/tms570-sci.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Low-level driver specific data structure */
typedef struct {
  const char *device_name;
  volatile tms570_sci_t *regs;
  int tx_chars_in_hw;
  rtems_vector_number irq;
} tms570_sci_context;

extern const rtems_termios_device_handler tms570_sci_handler_polled;

extern const rtems_termios_device_handler tms570_sci_handler_interrupt;

extern const tms570_sci_context driver_context_table[];

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TMS570_SCI_DRIVER */
