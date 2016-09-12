#include <stdint.h>
#include <stddef.h>
#include <bsp/tms570.h>
#include "tms570_selftest.h"
#include "tms570_parity_tests.h"

void tms570_partest_check_std( const tms570_esm_partest_desc_t *desc )
{
  volatile uint32_t test_read_data;
  uint32_t          par_cr_bak = *desc->par_cr_reg;
  int               perr;

  /* Set TEST mode and enable parity checking */
  *desc->par_cr_reg = desc->par_cr_test | TMS570_PARTEST_CR_KEY;

  /* flip parity bit */
  *desc->par_loc ^= desc->par_xor;

  /* Disable TEST mode */
  *desc->par_cr_reg = TMS570_PARTEST_CR_KEY;

  /* read to cause parity error */
  test_read_data = *desc->ram_loc;
  (void) test_read_data;

  /* check if ESM channel is flagged */
  perr = tms570_esm_channel_sr_get( desc->esm_prim_grp, desc->esm_prim_chan );

  if ( desc->esm_sec_grp )
    perr |= tms570_esm_channel_sr_get( desc->esm_sec_grp, desc->esm_sec_chan );

  if ( !perr ) {
    /* RAM parity error was not flagged to ESM. */
    bsp_seftest_fail_notification( desc->fail_code );
  } else {
    /* If periperal has it own parity status register, clear it */
    if ( desc->par_st_reg != NULL )
      *desc->par_st_reg = desc->par_st_clear;

    /* clear ESM flag */
    tms570_esm_channel_sr_clear( desc->esm_prim_grp, desc->esm_prim_chan );

    if ( desc->esm_sec_grp )
      tms570_esm_channel_sr_clear( desc->esm_sec_grp, desc->esm_sec_chan );

    /* Set TEST mode and enable parity checking */
    *desc->par_cr_reg = desc->par_cr_test | TMS570_PARTEST_CR_KEY;

    /* Revert back to correct data by flipping parity location */
    *desc->par_loc ^= desc->par_xor;
  }

  /* Restore Parity comtrol register */
  *desc->par_cr_reg = par_cr_bak;
}
