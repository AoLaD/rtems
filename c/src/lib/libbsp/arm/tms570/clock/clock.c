/*  ckinit.c
 *
 *  This file provides a template for the clock device driver initialization.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#include <stdlib.h>

#include <rtems.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/tms570-rti.h>

void Clock_exit( void );
rtems_isr Clock_isr( rtems_vector_number vector );


/*
 *  The interrupt vector number associated with the clock tick device
 *  driver.
 */

#define CLOCK_VECTOR    4 //not true

/*
 *  Clock_driver_ticks is a monotonically increasing counter of the
 *  number of clock ticks since the driver was initialized.
 */

volatile uint32_t         Clock_driver_ticks;

/*
 *  Clock_isrs is the number of clock ISRs until the next invocation of
 *  the RTEMS clock tick routine.  The clock tick device driver
 *  gets an interrupt once a millisecond and counts down until the
 *  length of time between the user configured microseconds per tick
 *  has passed.
 */

uint32_t         Clock_isrs;              /* ISRs until next tick */

/*
 * These are set by clock driver during its init
 */

rtems_device_major_number rtems_clock_major = ~0;
rtems_device_minor_number rtems_clock_minor;

/*
 *  The previous ISR on this clock tick interrupt vector.
 */

rtems_isr_entry  Old_ticker;

void Clock_exit( void );

/* to avoid including the bsp */
rtems_isr_entry set_vector( rtems_isr_entry, rtems_vector_number, int );


/*
 *  Isr Handler
 */

rtems_isr Clock_isr(
  rtems_vector_number vector
)
{
/*
 * bump the number of clock driver ticks since initialization
 *
 * determine if it is time to announce the passing of tick as configured
 * to RTEMS through the rtems_clock_tick directive
 *
 * perform any timer dependent tasks
 */
   TMS570_RTI.RTIINTFLAG = 0x00000001;
   ++Clock_driver_ticks;
   /* TMS570_RTI.RTICOMP0 += 1000; */

   if ( Clock_isrs <= 1 ) {
     rtems_clock_tick();
     Clock_isrs = rtems_configuration_get_microseconds_per_tick() / 1000;
   }
   else
     Clock_isrs -= 1;

}

static void tms570_clock_handler_install(void)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;

  sc = rtems_interrupt_handler_install(
    TMS570_IRQ_TIMER_0,
    "Clock",
    RTEMS_INTERRUPT_UNIQUE,
    (rtems_interrupt_handler) Clock_isr,
    NULL
  );
  if (sc != RTEMS_SUCCESSFUL) {
    rtems_fatal_error_occurred(0xdeadbeef);
  }
}

/*
 *  Install_clock
 *
 *  Install a clock tick handler and reprograms the chip.  This
 *  is used to initially establish the clock tick.
 */

void Install_clock(
  rtems_isr_entry clock_isr
)
{
  /*
   *  Initialize the clock tick device driver variables
   */

  Clock_driver_ticks = 0;
  Clock_isrs = rtems_configuration_get_microseconds_per_tick() / 1000;

  tms570_clock_handler_install();

  //Old_ticker = (rtems_isr_entry) set_vector( clock_isr, TMS570_IRQ_TIMER_0, 1 );
  /*
   *  Hardware specific initialize goes here
   */

  TMS570_RTI.RTIGCTRL = 0;
  TMS570_RTI.RTICPUC0 = 160 / 2; //prescaler
  TMS570_RTI.RTITBCTRL = 2;
  TMS570_RTI.RTICAPCTRL = 0;
  TMS570_RTI.RTICOMPCTRL = 0;
  /* set counter to zero */
  TMS570_RTI.RTIUC0 = 0;
  TMS570_RTI.RTIFRC0 = 0;
  /* clear interrupts*/
  TMS570_RTI.RTICLEARINTENA = 0x00070f0f;
  TMS570_RTI.RTIINTFLAG = 0x0007000f;
  /* set timer */
  TMS570_RTI.RTICOMP0 = TMS570_RTI.RTIFRC0 + 1000;
  TMS570_RTI.RTICOMP0CLR = TMS570_RTI.RTICOMP0 + 500;
  TMS570_RTI.RTIUDCP0 = 1000;
  TMS570_RTI.RTISETINTENA = 0x1; //enable interupt

  TMS570_RTI.RTIGCTRL = 1; //enable timer


  /*
   *  Schedule the clock cleanup routine to execute if the application exits.
   */

  atexit( Clock_exit );
}

/*
 *  Clean up before the application exits
 */

void Clock_exit( void )
{
  /* XXX: turn off the timer interrupts */

  TMS570_RTI.RTICLEARINTENA = 0x20000; //lets hope so. Need to verify

  /* XXX: If necessary, restore the old vector */
  //set_vector( Old_ticker, TMS570_IRQ_TIMER_0, 1 );
}

/*
 *  Clock_initialize
 *
 *  Device driver entry point for clock tick driver initialization.
 */

rtems_device_driver Clock_initialize(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void *pargp
)
{
  Install_clock( Clock_isr );

  /*
   * make major/minor avail to others such as shared memory driver
   */

  rtems_clock_major = major;
  rtems_clock_minor = minor;

  return RTEMS_SUCCESSFUL;
}
