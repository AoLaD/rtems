/**
 * @file io.c
 *
 * @ingroup tms570
 *
 * @brief Input/output module methods.
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

#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/io.h>
#include <bsp/start.h>
#include <bsp/system-clocks.h>

/**
 * @brief Modules table according to the TMS570
 */
static const tms570_module_entry tms570_module_table[] = {
  TMS570_MODULE_ENTRY( TMS570_MODULE_WD, 0, 1, 0 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_ADC, 1, 1, 12 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_CAN_0, 1, 1, 13 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_CAN_1, 1, 1, 14 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_DAC, 0, 1, 11 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_GPDMA, 1, 1, 29 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_GPIO, 0, 1, 15 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_I2S, 1, 1, 27 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_MCI, 1, 1, 28 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_MCPWM, 1, 1, 17 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_PCB, 0, 1, 18 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_PWM_0, 1, 1, 5 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_PWM_1, 1, 1, 6 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_QEI, 1, 1, 18 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_RTC, 1, 1, 9 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_SYSCON, 0, 1, 30 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_TIMER_0, 1, 1, 1 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_TIMER_1, 1, 1, 2 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_TIMER_2, 1, 1, 22 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_TIMER_3, 1, 1, 23 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_UART_0, 1, 1, 3 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_UART_1, 1, 1, 4 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_UART_2, 1, 1, 24 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_UART_3, 1, 1, 25 ),
  TMS570_MODULE_ENTRY( TMS570_MODULE_USB, 1, 0, 31 )
};

inline void tms570_pin_select(
  const uint32_t             pin,
  const tms570_pin_function function
)
{
  assert( pin <= TMS570_IO_INDEX_MAX
    && function < TMS570_PIN_FUNCTION_COUNT );
  const uint32_t           pin_selected = TMS570_PIN_SELECT( pin );
  volatile uint32_t *const pinsel = &TMS570_PINSEL[ pin_selected ];
  const uint32_t           shift = TMS570_PIN_SELECT_SHIFT( pin );
  *pinsel = SET_FIELD( *pinsel, function,
    TMS570_PIN_SELECT_MASK << shift, shift );
}

/**
 * @brief Checks if the module has power.
 *
 * @param has_power Power.
 * @param index Index to shift.
 * @param turn_on Turn on/off the power.
 * @param level Interrupts value.
 */
static rtems_status_code check_power(
  const bool            has_power,
  const unsigned        index,
  const bool            turn_on,
  rtems_interrupt_level level
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( index <= TMS570_MODULE_BITS_COUNT ) {
    if ( has_power ) {
      rtems_interrupt_disable( level );

      if ( turn_on ) {
        TMS570_SCB.pconp |= 1u << index;
      } else {
        TMS570_SCB.pconp &= ~( 1u << index );
      }

      rtems_interrupt_enable( level );
    }

    /* else implies that the module has not power. Also,
       there is nothing to do. */

    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies an invalid index number. Also, the function
     does not return successful. */

  return status_code;
}

/**
 * @brief Sets the correct value according to the specific peripheral clock.
 *
 * @param  is_first_pclksel Represents the first pclksel.
 * @param  clock The clock to set for this module.
 * @param  clock_shift Value to clock shift.
 */
static inline void set_pclksel_value(
  const uint32_t             pclksel,
  const tms570_module_clock clock,
  const unsigned             clock_shift
)
{
  assert( pclksel < TMS570_SCB_PCLKSEL_COUNT );
  const uint32_t setclock = ( clock << clock_shift );
  const uint32_t mask = ~( TMS570_MODULE_CLOCK_MASK << clock_shift );
  TMS570_SCB.pclksel[ pclksel ] = ( TMS570_SCB.pclksel[ pclksel ] & mask ) |
                                   setclock;
}

/**
 * @brief Checks if the module has clock.
 *
 * @param has_clock Clock.
 * @param index Index to shift.
 * @param clock The clock to set for this module.
 * @param level Interrupts value.
 */
static rtems_status_code check_clock(
  const bool                 has_clock,
  const unsigned             index,
  const tms570_module_clock clock,
  rtems_interrupt_level      level
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( index <= TMS570_MODULE_BITS_COUNT ) {
    if ( has_clock ) {
      unsigned clock_shift = 2u * index;
      rtems_interrupt_disable( level );

      if ( clock_shift < TMS570_MODULE_BITS_COUNT ) {
        /* Sets the pclksel 0. */
        set_pclksel_value( TMS570_SCB_PCLKSEL0, clock, clock_shift );
      } else {
        /* Sets the pclksel 1. */
        clock_shift -= TMS570_MODULE_BITS_COUNT;
        set_pclksel_value( TMS570_SCB_PCLKSEL1, clock, clock_shift );
      }

      rtems_interrupt_enable( level );
    }

    /* else implies that the module has not clock. Also,
       there is nothing to do. */

    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies an invalid index number. Also, the function
     does not return successful. */

  return status_code;
}

/**
 * @brief Checks the usb module.
 *
 * @return RTEMS_SUCCESFUL if the usb module is correct.
 */
static rtems_status_code check_usb_module( void )
{
  rtems_status_code status_code = RTEMS_INCORRECT_STATE;
  const uint32_t    pllclk = tms570_pllclk();
  const uint32_t    usbclk = TMS570_USB_CLOCK;

  if ( pllclk % usbclk == 0u ) {
    const uint32_t usbdiv = pllclk / usbclk;

    TMS570_SCB.usbclksel = TMS570_SCB_USBCLKSEL_USBDIV( usbdiv ) |
                            TMS570_SCB_USBCLKSEL_USBSEL( 1 );
    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the module has an incorrect pllclk or usbclk value.
      Also, there is nothing to do. */

  return status_code;
}

/**
 * @brief Enables the current module.
 *
 * @param  module  Current module to enable/disable.
 * @param  clock The clock to set for this module.
 * @param enable TRUE if the module is enable.
 * @return RTEMS_SUCCESSFULL if the module was enabled successfully.
 */
static rtems_status_code enable_disable_module(
  const tms570_module       module,
  const tms570_module_clock clock,
  const bool                 enable
)
{
  rtems_status_code     status_code;
  rtems_interrupt_level level = 0u;

  const bool     has_power = tms570_module_table[ module ].power;
  const bool     has_clock = tms570_module_table[ module ].clock;
  const unsigned index = tms570_module_table[ module ].index;

  assert( index <= TMS570_MODULE_BITS_COUNT );

  /* Enable or disable module */
  if ( enable ) {
    status_code = check_power( has_power, index, true, level );
    RTEMS_CHECK_SC( status_code,
      "Checking index shift to turn on power of the module." );

    if ( module != TMS570_MODULE_USB ) {
      status_code = check_clock( has_clock, index, clock, level );
      RTEMS_CHECK_SC( status_code,
        "Checking index shift to set pclksel to the current module." );
    } else {
      status_code = check_usb_module();
      RTEMS_CHECK_SC( status_code,
        "Checking pll clock to set usb clock to the current module." );
    }
  } else {
    status_code = check_power( has_power, index, false, level );
    RTEMS_CHECK_SC( status_code,
      "Checking index shift to turn off power of the module." );
  }

  return status_code;
}

/**
 * @brief Enables the module power and clock.
 *
 * @param  module Device to enable.
 * @param  clock  The clock to set for this module.
 * @param  enable Enable or disable the module.
 * @return RTEMS_SUCCESSFULL if the module was enabled succesfully.
 */
static rtems_status_code tms570_module_do_enable(
  const tms570_module module,
  tms570_module_clock clock,
  const bool           enable
)
{
  rtems_status_code status_code = RTEMS_SUCCESSFUL;

  if ( (unsigned) module >= TMS570_MODULE_COUNT ) {
    return RTEMS_INVALID_ID;
  }

  /* else implies that the module has a correct value. Also,
     there is nothing to do. */

  if ( clock == TMS570_MODULE_PCLK_DEFAULT ) {
#if ( TMS570_PCLKDIV == 1u )
    clock = TMS570_MODULE_CCLK;
#elif ( TMS570_PCLKDIV == 2u )
    clock = TMS570_MODULE_CCLK_2;
#elif ( TMS570_PCLKDIV == 4u )
    clock = TMS570_MODULE_CCLK_4;
#elif ( TMS570_PCLKDIV == 8u )
    clock = TMS570_MODULE_CCLK_8;
#else
#error "Unexpected clock divisor."
#endif
  }

  /* else implies that the clock has a correct divisor. */

  if ( ( clock & ~TMS570_MODULE_CLOCK_MASK ) == 0u ) {
    status_code = enable_disable_module( module, clock, enable );
    RTEMS_CHECK_SC( status_code, "Checking the module to enable/disable." );
  } else {
    status_code = RTEMS_INVALID_CLOCK;
  }

  return status_code;
}

inline rtems_status_code tms570_module_enable(
  const tms570_module module,
  tms570_module_clock clock
)
{
  return tms570_module_do_enable( module, clock, true );
}

inline rtems_status_code tms570_module_disable( const tms570_module module )
{
  return tms570_module_do_enable( module,
    TMS570_MODULE_PCLK_DEFAULT,
    false );
}

bool tms570_module_is_enabled( const tms570_module module )
{
  assert( (unsigned) module < TMS570_MODULE_COUNT );

  const bool has_power = tms570_module_table[ module ].power;
  bool       enabled;

  if ( has_power ) {
    const unsigned index = tms570_module_table[ module ].index;
    const uint32_t pconp = TMS570_SCB.pconp;

    enabled = ( pconp & ( 1u << index ) ) != 0u;
  } else {
    enabled = true;
  }

  return enabled;
}
