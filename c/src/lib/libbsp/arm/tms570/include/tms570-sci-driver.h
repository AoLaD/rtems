#ifndef TMS570_SCI_DRIVER
#define TMS570_SCI_DRIVER

#include <rtems/termiostypes.h>

#include <bsp/tms570-sci.h>

/* Low-level driver specific data structure */
typedef struct {
  const char *device_name;
  volatile tms570_sci_t *regs;
  int tx_chars_in_hw;
  /* More stuff */
} tms570_sci_context;

extern const rtems_termios_device_handler tms570_sci_handler_polled;

extern const rtems_termios_device_handler tms570_sci_handler_interrupt;

#endif /* MY_DRIVER_H */
