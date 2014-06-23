/**
 * @file timer.c
 *
 * @ingroup tms570
 *
 * @brief Timer controller for the mbed tms570ls3137 board.
 */

/*
 * Copyright (c) 2014 Taller Technologies.
 *
 * @author  Boretto Martin    (martin.boretto@tallertechnologies.com)
 * @author  Diaz Marcos (marcos.diaz@tallertechnologies.com)
 * @author  Lenarduzzi Federico  (federico.lenarduzzi@tallertechnologies.com)
 * @author  Daniel Chicco  (daniel.chicco@tallertechnologies.com)
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <stdio.h>
#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/io.h>
#include <bsp/timer.h>

/**
 * @brief Represents all the timers.
 */
const tms570_timer timers[ TMS570_TIMER_COUNT ] =
{
  {
    .device = (tms570_timer_device *) TMS570_TMR0_BASE_ADDR,
    .module = TMS570_MODULE_TIMER_0,
    .pinselcap = TMS570_TIMER0_CAPTURE_PORTS,
    .pinselemat = TMS570_TIMER0_EMATCH_PORTS,
  },
  {
    .device = (tms570_timer_device *) TMS570_TMR1_BASE_ADDR,
    .module = TMS570_MODULE_TIMER_1,
    .pinselcap = TMS570_TIMER1_CAPTURE_PORTS,
    .pinselemat = TMS570_TIMER1_EMATCH_PORTS,
  },
  {
    .device = (tms570_timer_device *) TMS570_TMR2_BASE_ADDR,
    .module = TMS570_MODULE_TIMER_2,
    .pinselcap = TMS570_TIMER2_CAPTURE_PORTS,
    .pinselemat = TMS570_TIMER2_EMATCH_PORTS,
  },
  {
    .device = (tms570_timer_device *) TMS570_TMR3_BASE_ADDR,
    .module = TMS570_MODULE_TIMER_3,
    .pinselcap = TMS570_TIMER3_CAPTURE_PORTS,
    .pinselemat = TMS570_TIMER3_EMATCH_PORTS,
  }
};

/**
 * @brief Represents all the functions according to the timers.
 */
tms570_timer_functions functions_vector[ TMS570_TIMER_COUNT ] =
{
  {
    .funct_vector = NULL
  },
  {
    .funct_vector = NULL
  },
  {
    .funct_vector = NULL
  },
  {
    .funct_vector = NULL
  }
};

/**
 * @brief Calls the corresponding interrupt function and pass the timer
 *        as parameter.
 *
 * @param  timer The specific device.
 * @param  interruptnumber Interrupt number.
 */
static inline void tms570_call_desired_isr(
  const tms570_timer_number number,
  const tms570_isr_function interruptfunction
)
{
  if ( ( *functions_vector[ number ].funct_vector )[ interruptfunction ] !=
       NULL ) {
    ( *functions_vector[ number ].funct_vector )[ interruptfunction ]( number );
  }

  /* else implies that the function vector points NULL. Also,
     there is nothing to do. */
}

/**
 * @brief Gets true if the selected interrupt is pending
 *
 * @param number: the number of the timer.
 * @param interrupt: the interrupt we are checking for.
 * @return TRUE if the interrupt is pending.
 */
static inline bool tms570_timer_interrupt_is_pending(
  const tms570_timer_number tnumber,
  const tms570_isr_function function
)
{
  assert( ( tnumber < TMS570_TIMER_COUNT )
    && ( function < TMS570_ISR_FUNCTIONS_COUNT ) );

  return ( timers[ tnumber ].device->IR &
           TMS570_TIMER_INTERRUPT_SOURCE_BIT( function ) );
}

/**
 * @brief Resets interrupt status for the selected interrupt
 *
 * @param tnumber: the number of the timer
 * @param interrupt: the interrupt we are resetting
 */
static inline void tms570_timer_reset_interrupt(
  const tms570_timer_number tnumber,
  const tms570_isr_function function
)
{
  assert( ( tnumber < TMS570_TIMER_COUNT )
    && ( function < TMS570_ISR_FUNCTIONS_COUNT ) );
  timers[ tnumber ].device->IR =
    TMS570_TIMER_INTERRUPT_SOURCE_BIT( function );
}

inline rtems_status_code tms570_timer_reset(
  const tms570_timer_number tnumber )
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    timers[ tnumber ].device->TCR = TMS570_TIMER_RESET;
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

inline rtems_status_code tms570_timer_set_mode(
  const tms570_timer_number tnumber,
  const tms570_timer_mode   mode
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    timers[ tnumber ].device->CTCR = mode;
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

inline rtems_status_code tms570_timer_start(
  const tms570_timer_number tnumber )
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    timers[ tnumber ].device->TCR = TMS570_TIMER_START;
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

inline rtems_status_code tms570_timer_is_started(
  const tms570_timer_number tnumber,
  bool                      *is_started
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    *is_started = ( timers[ tnumber ].device->TCR & TMS570_TIMER_START ) ==
                  TMS570_TIMER_START;
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

inline rtems_status_code tms570_timer_set_resolution(
  const tms570_timer_number tnumber,
  const tms570_microseconds resolution
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    timers[ tnumber ].device->PR = ( TMS570_CCLK /
                                     TMS570_TIMER_PRESCALER_DIVISOR ) *
                                   resolution;
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

rtems_status_code tms570_timer_match_config(
  const tms570_timer_number   tnumber,
  const tms570_match_port     match_port,
  const tms570_match_function function,
  const uint32_t               match_value
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( ( tnumber < TMS570_TIMER_COUNT )
       && ( match_port < TMS570_EMATCH_PORTS_COUNT )
       && ( function < TMS570_TIMER_MATCH_FUNCTION_COUNT ) ) {
    timers[ tnumber ].device->MCR =
      TMS570_SET_MCR( timers[ tnumber ].device->MCR,
        match_port, function );
    timers[ tnumber ].device->MR[ match_port ] = match_value;
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number, or a match port or a function
      is invalid. Also, an invalid number is returned. */

  return status_code;
}

inline rtems_status_code tms570_timer_capture_config(
  const tms570_timer_number     tnumber,
  const tms570_capture_port     capture_port,
  const tms570_capture_function function
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( ( tnumber < TMS570_TIMER_COUNT )
       && ( capture_port < TMS570_CAPTURE_PORTS_COUNT )
       && ( function < TMS570_TIMER_CAPTURE_FUNCTION_COUNT ) ) {
    timers[ tnumber ].device->CCR =
      TMS570_SET_CCR( timers[ tnumber ].device->CCR,
        capture_port, function );
    tms570_pin_select( timers[ tnumber ].pinselcap[ capture_port ],
      TMS570_PIN_FUNCTION_11 );
  }

  /* else implies that the timer number or the capture port is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

inline rtems_status_code tms570_timer_external_match_config(
  const tms570_timer_number       number,
  const tms570_match_port         match_port,
  const tms570_ext_match_function function
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( ( number < TMS570_TIMER_COUNT )
       && ( match_port < TMS570_EMATCH_PORTS_COUNT ) ) {
    timers[ number ].device->EMR =
      TMS570_SET_EMR( timers[ number ].device->EMR,
        match_port, function );
    tms570_pin_select( timers[ number ].pinselemat[ match_port ],
      TMS570_PIN_FUNCTION_11 );
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number or the match port is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

inline uint32_t tms570_timer_get_capvalue(
  const tms570_timer_number number,
  const tms570_capture_port capture_port
)
{
  assert( ( number < TMS570_TIMER_COUNT )
    && ( capture_port < TMS570_CAPTURE_PORTS_COUNT ) );

  return timers[ number ].device->CR[ capture_port ];
}

inline uint32_t tms570_timer_get_timer_value(
  const tms570_timer_number tnumber )
{
  assert( tnumber < TMS570_TIMER_COUNT );

  return timers[ tnumber ].device->TC;
}

inline rtems_status_code tms570_timer_set_timer_value(
  const tms570_timer_number tnumber,
  const uint32_t             timer_value
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    timers[ tnumber ].device->TC = timer_value;
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the timer number is invalid. Also,
     an invalid number is returned. */

  return status_code;
}

void tms570_timer_isr( void *arg )
{
  const tms570_timer_number tnumber = (tms570_timer_number) arg;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    tms570_isr_function i;

    for ( i = 0; i < TMS570_ISR_FUNCTIONS_COUNT; ++i ) {
      if ( tms570_timer_interrupt_is_pending( tnumber, i ) ) {
        tms570_call_desired_isr( tnumber, i );
        tms570_timer_reset_interrupt( tnumber, i );
      }

      /* else implies that the current timer is not pending. Also,
         there is nothing to do. */
    }
  }

  /* else implies that the timer number is not valid. Also,
     there is nothing to do. */
}

rtems_status_code tms570_timer_init( const tms570_timer_number tnumber )
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( tnumber < TMS570_TIMER_COUNT ) {
    status_code = tms570_module_enable( timers[ tnumber ].module,
      TMS570_MODULE_PCLK_DEFAULT );
    RTEMS_CHECK_SC( status_code, "Enabling the timer module." );

    status_code = tms570_timer_reset( tnumber );
    status_code = tms570_timer_set_mode( tnumber,
      TMS570_TIMER_MODE_TIMER );
    status_code = tms570_timer_set_resolution( tnumber,
      TMS570_TIMER_DEFAULT_RESOLUTION );

    timers[ tnumber ].device->MCR = TMS570_TIMER_CLEAR_FUNCTION;
    timers[ tnumber ].device->CCR = TMS570_TIMER_CLEAR_FUNCTION;
    timers[ tnumber ].device->EMR = TMS570_TIMER_CLEAR_FUNCTION;
  }

  /* else implies that the timer number is not valid. Also,
     an invalid number is returned. */

  return status_code;
}

rtems_status_code tms570_timer_init_with_interrupt(
  const tms570_timer_number            tnumber,
  const tms570_isr_funct_vector *const vector
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  char isrname[ TMS570_ISR_NAME_STRING_SIZE ];

  snprintf( isrname, TMS570_ISR_NAME_STRING_SIZE, "TimerIsr%d", tnumber );

  if ( tnumber < TMS570_TIMER_COUNT && vector != NULL ) {
    functions_vector[ tnumber ].funct_vector = vector;

    status_code = tms570_timer_init( tnumber );
    status_code = rtems_interrupt_handler_install(
      TMS570_TIMER_VECTOR_NUMBER( tnumber ),
      isrname,
      RTEMS_INTERRUPT_UNIQUE,
      tms570_timer_isr,
      (void *) tnumber );
  }

  return status_code;
}