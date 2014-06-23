/**
 * @file bspstarthooks.c
 *
 * @ingroup tms570
 *
 * @brief First configurations and initializations to the correct
 *              functionality of the board.
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

#include <bsp.h>
#include <bsp/start.h>
#include <bsp/io.h>

/**
 * @brief Initializes the oscillator according to the tms570 board.
 */
static BSP_START_TEXT_SECTION void tms570_init_main_oscillator( void )
{
  if ( ( TMS570_SCB.scs & TMS570_SCB_SCS_OSC_STATUS ) == 0u ) {
    TMS570_SCB.scs |= TMS570_SCB_SCS_OSC_ENABLE;

    while ( ( TMS570_SCB.scs & TMS570_SCB_SCS_OSC_STATUS ) == 0u ) {
      /* Wait. */
    }
  }

  /* else implies that the oscillator is initialized. Also,
     there is nothing to do. */
}

/**
 * @brief Sets the PLL configuration.
 *
 * @param pll Value to set.
 * @param val Set value.
 */
static BSP_START_TEXT_SECTION void tms570_pll_config( const uint32_t val )
{
  ( TMS570_SCB.pll_0 ).con = val;
  /* The two register writes must be in correct sequence. */
  ( TMS570_SCB.pll_0 ).feed = TMS570_PLL0CON;
  ( TMS570_SCB.pll_0 ).feed = TMS570_PLL0CFG;
}

/**
 * @brief Sets the PLL.
 *
 * @param msel Multiplier value.
 * @param psel Divider value.
 * @param cclkdiv Divisor clock.
 */
static BSP_START_TEXT_SECTION void tms570_set_pll(
  const unsigned msel,
  const unsigned psel,
  const unsigned cclkdiv
)
{
  const uint32_t pllcfg = TMS570_PLL_SEL_MSEL( msel ) |
                          TMS570_PLL_SEL_PSEL( psel );
  const uint32_t pllstat = TMS570_PLL_STAT_PLLE | TMS570_PLL_STAT_PLOCK |
                           pllcfg;
  const uint32_t cclksel_cclkdiv = TMS570_SCB_CCLKSEL_CCLKDIV( cclkdiv );

  if ( ( TMS570_SCB.pll_0 ).stat != pllstat
       || TMS570_SCB.cclksel != cclksel_cclkdiv
       || TMS570_SCB.clksrcsel != TMS570_SCB_CLKSRCSEL_CLKSRC ) {
    tms570_pll_config( ( TMS570_SCB.pll_0 ).con & ~TMS570_PLL_CON_PLLC );

    /* Turn off USB.  */
    TMS570_SCB.usbclksel = 0u;

    /* Disable PLL. */
    tms570_pll_config( 0u );

    /* Use SYSCLK for CCLK. */
    TMS570_SCB.cclksel = TMS570_SCB_CCLKSEL_CCLKDIV( 0u );

    /* Set the CCLK, PCLK and EMCCLK divider. */
    TMS570_SCB.cclksel = cclksel_cclkdiv;

    /* Select main oscillator as clock source. */
    TMS570_SCB.clksrcsel = TMS570_SCB_CLKSRCSEL_CLKSRC;

    /* The two register writes must be in correct sequence. */
    /* Set PLL configuration. */
    ( TMS570_SCB.pll_0 ).cfg = pllcfg;
    ( TMS570_SCB.pll_0 ).feed = TMS570_PLL0CON;
    ( TMS570_SCB.pll_0 ).feed = TMS570_PLL0CFG;

    /* Enable PLL. */
    tms570_pll_config( TMS570_PLL_CON_PLLE );

    /* Wait for lock. */
    while ( ( ( TMS570_SCB.pll_0 ).stat & TMS570_PLL_STAT_PLOCK ) == 0u ) {
      /* Wait */
    }

    /* Connect PLL. */
    tms570_pll_config( ( TMS570_PLL_CON_PLLE | TMS570_PLL_CON_PLLC ) );

    /* Wait for connected and enabled. */
    while ( ( ( TMS570_SCB.pll_0 ).stat & ( TMS570_PLL_STAT_PLLE |
                                             TMS570_PLL_STAT_PLLC ) ) ==
            0u ) {
      /* Wait  */
    }
  }

  /* else implies that the pll has a wrong value. Also,
     there is nothing to do. */
}

/**
 * @brief Pll initialization.
 */
static BSP_START_TEXT_SECTION void tms570_init_pll( void )
{
#if ( TMS570_OSCILLATOR_MAIN == 12000000u )
#if ( TMS570_CCLK == 96000000U )
  tms570_set_pll( 11u, 0u, 2u );
#else
#error "unexpected CCLK"
#endif
#else
#error "unexpected main oscillator frequency"
#endif
}

/**
 * @brief Memory map initialization.
 */
static BSP_START_TEXT_SECTION void tms570_init_memory_map( void )
{
  TMS570_SCB.memmap = TMS570_SCB_MEMMAP_MAP;
}

/**
 * @brief Memory accelerator initialization.
 */
static BSP_START_TEXT_SECTION void tms570_init_memory_accelerator( void )
{
#if ( TMS570_CCLK <= 20000000U )
  TMS570_SCB.flashcfg = TMS570_SCB_FLASHCFG_FLASHTIM( 0x0U );
#elif ( TMS570_CCLK <= 40000000U )
  TMS570_SCB.flashcfg = TMS570_SCB_FLASHCFG_FLASHTIM( 0x1U );
#elif ( TMS570_CCLK <= 60000000U )
  TMS570_SCB.flashcfg = TMS570_SCB_FLASHCFG_FLASHTIM( 0x2U );
#elif ( TMS570_CCLK <= 80000000U )
  TMS570_SCB.flashcfg = TMS570_SCB_FLASHCFG_FLASHTIM( 0x3U );
#elif ( TMS570_CCLK <= 100000000U )
  TMS570_SCB.flashcfg = TMS570_SCB_FLASHCFG_FLASHTIM( 0x4U );
#else
  TMS570_SCB.flashcfg = TMS570_SCB_FLASHCFG_FLASHTIM( 0x5U );
#endif
}

/**
 * @brief Stops the gpdma device.
 */
static BSP_START_TEXT_SECTION void tms570_stop_gpdma( void )
{
#ifdef TMS570_STOP_GPDMA

  bool has_power = ( TMS570_SCB.pconp & TMS570_SCB_PCONP_GPDMA ) != 0u;

  if ( has_power ) {
    GPDMA_CONFIG = 0u;
    TMS570_SCB.pconp &= ~TMS570_SCB_PCONP_GPDMA;
  }

  /* else implies that the current module (gpdma) is turn off. Also,
     there is nothing to do. */

#endif
}

/**
 * @brief Stops the usb device.
 */
static BSP_START_TEXT_SECTION void tms570_stop_usb( void )
{
#ifdef TMS570_STOP_USB

  bool has_power = ( TMS570_SCB.pconp & TMS570_SCB_PCONP_USB ) != 0u;

  if ( has_power ) {
    OTG_CLK_CTRL = 0u;

    TMS570_SCB.pconp &= ~TMS570_SCB_PCONP_USB;
    TMS570_SCB.usbclksel = 0u;
  }

  /* else implies that the current module (usb) is turn off. Also,
     there is nothing to do. */
#endif
}

BSP_START_TEXT_SECTION void bsp_start_hook_0( void )
{
  tms570_init_main_oscillator();
  tms570_init_pll();
}

BSP_START_TEXT_SECTION void bsp_start_hook_1( void )
{
  tms570_init_memory_map();
  tms570_init_memory_accelerator();
  tms570_stop_gpdma();
  tms570_stop_usb();
  bsp_start_copy_sections();
  bsp_start_clear_bss();

  /* At this point we can use objects outside the .start section  */
}