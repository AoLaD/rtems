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

#include <bspopts.h>

#include <libchip/sersupp.h>
#include <bsp/tms570-sci.h>
#include <bsp/tms570-sci-driver.h>
#include <rtems/console.h>
#include <bsp.h>
#include <bsp/fatal.h>
#include <bsp/irq.h>

#define TMS570_SCI_BUFFER_SIZE 10
#define TMS570_CONTEXT_TABLE_SIZE 2

tms570_sci_context driver_context_table[] = {{
    .device_name = "/dev/console",
    .regs = &TMS570_SCI,
    .irq = TMS570_IRQ_SCI_LEVEL_0,
    },
    {
    .device_name = "/dev/ttyS1",
    .regs = &TMS570_SCI2,
    .irq = TMS570_IRQ_SCI2_LEVEL_0,
    }   
    };

#define TMS570_CONSOLE_USE_INTERRUPTS
rtems_device_driver console_initialize(
  rtems_device_major_number  major,
  rtems_device_minor_number  minor,
  void                      *arg
)
{
  rtems_status_code sc;
#ifdef TMS570_CONSOLE_USE_INTERRUPTS
  const rtems_termios_device_handler *handler = &tms570_sci_handler_interrupt;
#else
  const rtems_termios_device_handler *handler = &tms570_sci_handler_polled;
#endif

  /*
   * Initialize the Termios infrastructure.  If Termios has already
   * been initialized by another device driver, then this call will
   * have no effect.
   */
  rtems_termios_initialize();

  /* Initialize each device */
  for (
    minor = 0;
    minor < RTEMS_ARRAY_SIZE(driver_context_table);
    ++minor
  ) {
    tms570_sci_context *ctx = &driver_context_table[minor];

    /*
     * Install this device in the file system and Termios.  In order
     * to use the console (i.e. being able to do printf, scanf etc.
     * on stdin, stdout and stderr), one device must be registered as
     * "/dev/console" (CONSOLE_DEVICE_NAME).
     */
    sc = rtems_termios_device_install(
      ctx->device_name,
      major,
      minor,
      handler,
      ctx
    );
    if (sc != RTEMS_SUCCESSFUL) {
      bsp_fatal(BSP_FATAL_CONSOLE_NO_DEV);
    }
  }
  return RTEMS_SUCCESSFUL;
}



static int tms570_sci_read_received_chars(
  tms570_sci_context * ctx,
  char * buf,
  int N)
{
  if(N<1)return 0;
  if(ctx->regs->SCIRD != 0){
     buf[0] = ctx->regs->SCIRD;
    return 1;
  }
  return 0;
}

static void tms570_sci_enable_interrupts(tms570_sci_context * ctx){
  ctx->regs->SCISETINT = (1<<9);
}

static void tms570_sci_disable_interrupts(tms570_sci_context * ctx){
  ctx->regs->SCICLEARINT = (1<<9);
}

static int tms570_sci_transmitted_chars(tms570_sci_context * ctx)
{
  int ret;
  ret = ctx->tx_chars_in_hw;
  if(ret == 1){
    ctx->tx_chars_in_hw = 0;
    return 1;
  }
  return ret;
}

static bool tms570_sci_set_attributes(
  rtems_termios_tty    *tty,
  const struct termios *t
)
{
  //tms570_sci_context *ctx = rtems_termios_get_device_context(tty);
  //rtems_interrupt_lock_context lock_context;
  
  //rtems_termios_interrupt_lock_acquire(tty, &lock_context);

  //switch (t->c_cflag & (PARENB|PARODD)) {
    //case (PARENB|PARODD):
      ///* Odd parity */
      //ctx->regs->SCIGCR1 &= !(1<<3); 
      //ctx->regs->SCIGCR1 |= (1<<2);       
      //break;
      
    //case PARENB:
      ///* Even parity */
      //ctx->regs->SCIGCR1 |= (1<<3);
      //ctx->regs->SCIGCR1 |= (1<<2);
      //break;

    //default:
    //case 0:
    //case PARODD:
      ///* No Parity */
      //ctx->regs->SCIGCR1 &= !(1<<2);
  //}
  
  ///* Baud rate */
  //ctx->regs->BRS |= 0xFF00001A;
    
  //rtems_termios_interrupt_lock_release(tty, &lock_context);

  return true;
}
static void tms570_sci_interrupt_handler(void * arg){
  rtems_termios_tty *tty = arg;
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);
  char buf[TMS570_SCI_BUFFER_SIZE];
  size_t n;

  /*
   * Check if we have received something.  The function reads the
   * received characters from the device and stores them in the
   * buffer.  It returns the number of read characters.
   */
   if((ctx->regs->SCIFLR & (1<<9)) == (1<<9)){
      n = tms570_sci_read_received_chars(ctx, buf, TMS570_SCI_BUFFER_SIZE);
      if (n > 0) {
        /* Hand the data over to the Termios infrastructure */
        rtems_termios_enqueue_raw_characters(tty, buf, n);
      }
    }
  /*
   * Check if we have something transmitted.  The functions returns
   * the number of transmitted characters since the last write to the
   * device.
   */
  if((ctx->regs->SCIFLR & (1<<8)) == (1<<8)){
    n = tms570_sci_transmitted_chars(ctx);
    if (n > 0) {
      /*
       * Notify Termios that we have transmitted some characters.  It
       * will call now the interrupt write function if more characters
       * are ready for transmission.
       */
      rtems_termios_dequeue_characters(tty, n);
    }
  }
}

static void tms570_sci_interrupt_write(
  rtems_termios_tty *tty,
  const char *buf,
  size_t len
)
{
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);

  if (len > 0) {
    /* start UART TX, this will result in an interrupt when done */
    ctx->regs->SCITD = *buf;
    /* character written - raise count*/
    ctx->tx_chars_in_hw = 1;
    /* Enable TX interrupt (interrupt is edge-triggered) */
    ctx->regs->SCISETINT = (1<<8);

  } else {
    /* No more to send, disable TX interrupts */
    ctx->regs->SCICLEARINT = (1<<8);
    /* Tell close that we sent everything */
  }
}

static void tms570_sci_poll_write(
  rtems_termios_tty *tty,
  const char        *buf,
  size_t             n
)
{
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);
  size_t i;
  
  /* Write */ 
    
  for (i = 0; i < n; ++i) {
    while ((ctx->regs->SCIFLR & (1<<11)) == 0) {
      ;
    }
    ctx->regs->SCITD = buf[i];
  }
}

static int TMS570_sci_can_read_char(
  tms570_sci_context * ctx
)
{
  return ctx->regs->SCIFLR;
}

static char TMS570_sci_read_char(
  tms570_sci_context * ctx
)
{
  return ctx->regs->SCIRD;
}

static int tms570_sci_poll_read(rtems_termios_tty *tty)
{
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);

  /* Check if a character is available */
  if (TMS570_sci_can_read_char(ctx)) {
    /* Return the character */
    return TMS570_sci_read_char(ctx);
  } else {
    /* Return an error status */
    return -1;
  }
}

static bool tms570_sci_poll_first_open(
  rtems_termios_tty             *tty,
  rtems_libio_open_close_args_t *args
)
{
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);
  bool ok;
  /*
  ctx->regs->SCIGCR1 |= (1<<25) | (1<<24) | (1<<4);
  ctx->regs->SCIFORMAT |= 0x7;  
  ctx->regs->SCIPIO0 |= (1<<1) | (1<<2);
  */
  ctx->regs->SCISETINTLVL = 0;
  ok = tms570_sci_set_attributes(tty, rtems_termios_get_termios(tty));
  if (!ok) {    
    return false;
  }    
  return true;
}

static bool tms570_sci_interrupt_first_open(
  rtems_termios_tty             *tty,
  rtems_libio_open_close_args_t *args
){
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);
  rtems_status_code sc;
  bool ret;
  /* Register Interrupt handler */
  sc = rtems_interrupt_handler_install(ctx->irq,
                                       ctx->device_name,
                                       RTEMS_INTERRUPT_SHARED,
                                       tms570_sci_interrupt_handler,
                                       tty);
  if (sc != RTEMS_SUCCESSFUL)
    return false;

  ret = tms570_sci_poll_first_open(tty,args);
  tms570_sci_enable_interrupts(rtems_termios_get_device_context(tty));
  return ret;
}

static void tms570_sci_poll_last_close(
  rtems_termios_tty             *tty,
  rtems_libio_open_close_args_t *args
)
{
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);

  /* Here shall be peripheral HW reset, someday */   

}

static void tms570_sci_interrupt_last_close(
  rtems_termios_tty             *tty,
  rtems_libio_open_close_args_t *args
)
{
  tms570_sci_context *ctx = rtems_termios_get_device_context(tty);
  rtems_interrupt_lock_context lock_context;

  /* Turn off RX interrupts */
  rtems_termios_interrupt_lock_acquire(tty, &lock_context);
  tms570_sci_disable_interrupts(ctx);
  rtems_termios_interrupt_lock_release(tty, &lock_context);

  /**** Flush device ****/
  while ((ctx->regs->SCIFLR & (1<<11)) > 0) {
    /* Wait until all data has been sent */
  }

  /* uninstall ISR */
  rtems_interrupt_handler_remove(ctx->irq, tms570_sci_interrupt_handler, tty);

  tms570_sci_poll_last_close(tty,args);
}

const rtems_termios_device_handler tms570_sci_handler_polled = {
  .first_open = tms570_sci_poll_first_open,
  .last_close = tms570_sci_poll_last_close,
  .poll_read = tms570_sci_poll_read,
  .write = tms570_sci_poll_write,
  .set_attributes = tms570_sci_set_attributes,
  .stop_remote_tx = NULL,
  .start_remote_tx = NULL,
  .mode = TERMIOS_POLLED
};

const rtems_termios_device_handler tms570_sci_handler_interrupt  = {
  .first_open = tms570_sci_interrupt_first_open,
  .last_close = tms570_sci_interrupt_last_close,
  .poll_read = NULL,
  .write = tms570_sci_interrupt_write,
  .set_attributes = tms570_sci_set_attributes,
  //.stopRemoteTx = NULL,
  .stop_remote_tx = NULL,
  .start_remote_tx = NULL,
  .mode = TERMIOS_IRQ_DRIVEN
};
