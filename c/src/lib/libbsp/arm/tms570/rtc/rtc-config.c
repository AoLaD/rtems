/**
 * @file
 *
 * @ingroup tms570
 *
 * @brief RTC configuration.
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


#include <libchip/rtc.h>
#include <bsp/io.h>


void bsp_rtc_initialize( void );
int bsp_rtc_get_time( rtems_time_of_day *tod );
int bsp_rtc_set_time( const rtems_time_of_day *tod );
bool bsp_rtc_probe( void );

/**
 * @brief Initialize the rtc device.
 */
void bsp_rtc_initialize( void )
{
}

/**
 * @brief Gets the information according to the current time.
 *
 * @param  tod Value to be modified.
 * @return  0
 */
int bsp_rtc_get_time( rtems_time_of_day *tod )
{
  return 0;
}

/**
 * @brief Sets the information according to the current time.
 *
 * @param  tod Value to get the new information.
 * @return  0
 */
int bsp_rtc_set_time( const rtems_time_of_day *tod )
{
  return 0;
}

/**
 * @brief Used to probe. At the moment is not used.
 *
 * @return true.
 */
bool bsp_rtc_probe( void )
{
  return true;
}

/**
 * @brief Represents the real time clock options.
 */
const rtc_fns tms570_rtc_ops = {
  .deviceInitialize = (void *) bsp_rtc_initialize,
  .deviceGetTime = (void *) bsp_rtc_get_time,
  .deviceSetTime = (void *) bsp_rtc_set_time
};


