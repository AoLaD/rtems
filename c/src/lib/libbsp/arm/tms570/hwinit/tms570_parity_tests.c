#include <stdint.h>
#include <stddef.h>
#include <bsp/tms570.h>
#include <rtems.h>
#include "tms570_selftest.h"
#include "tms570_parity_tests.h"

const tms570_esm_partest_desc_t
  tms570_partest_het1_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 7,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = HET1PARITYCHECK_FAIL1,
  .ram_loc       = &NHET1RAMLOC,
  .par_loc       = &NHET1RAMPARLOC,
  .par_xor       = 0x00000001,
  .par_cr_reg    = &TMS570_NHET1.PCR,
  .par_cr_test   = TMS570_NHET_PCR_TEST,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_htu1_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 8,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = HTU1PARITYCHECK_FAIL1,
  .ram_loc       = &HTU1RAMLOC,
  .par_loc       = &HTU1PARLOC,
  .par_xor       = 0x00000001,
  .par_cr_reg    = &TMS570_HTU1.PCR,
  .par_cr_test   = TMS570_HTU_PCR_TEST,
  .par_st_reg    = &TMS570_HTU1.PAR,
  .par_st_clear  = TMS570_HTU_PAR_PEFT,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_het2_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 7,
  .esm_sec_grp   = 1,
  .esm_sec_chan  = 34,
  .fail_code     = HET2PARITYCHECK_FAIL1,
  .ram_loc       = &NHET2RAMLOC,
  .par_loc       = &NHET2RAMPARLOC,
  .par_xor       = 0x00000001,
  .par_cr_reg    = &TMS570_NHET2.PCR,
  .par_cr_test   = TMS570_NHET_PCR_TEST,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_htu2_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 8,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = HTU2PARITYCHECK_FAIL1,
  .ram_loc       = &HTU2RAMLOC,
  .par_loc       = &HTU2PARLOC,
  .par_xor       = 0x00000001,
  .par_cr_reg    = &TMS570_HTU2.PCR,
  .par_cr_test   = TMS570_HTU_PCR_TEST,
  .par_st_reg    = &TMS570_HTU2.PAR,
  .par_st_clear  = TMS570_HTU_PAR_PEFT,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_adc1_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 19,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = ADC1PARITYCHECK_FAIL1,
  .ram_loc       = &adcRAM1,
  .par_loc       = &adcPARRAM1,
  .par_xor       = 0xffffffff,
  .par_cr_reg    = &TMS570_ADC1.PARCR,
  .par_cr_test   = TMS570_ADC_PARCR_TEST,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_adc2_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 1,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = ADC2PARITYCHECK_FAIL1,
  .ram_loc       = &adcRAM2,
  .par_loc       = &adcPARRAM2,
  .par_xor       = 0xffffffff,
  .par_cr_reg    = &TMS570_ADC2.PARCR,
  .par_cr_test   = TMS570_ADC_PARCR_TEST,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_can1_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 21,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = CAN1PARITYCHECK_FAIL1,
  .ram_loc       = &canRAM1,
  .par_loc       = &canPARRAM1,
  .par_xor       = 0x00001000,
  .par_cr_reg    = NULL,
  .par_cr_test   = 0,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_can,
  .fnc_data      = &TMS570_DCAN1
};

const tms570_esm_partest_desc_t
  tms570_partest_can2_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 23,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = CAN2PARITYCHECK_FAIL1,
  .ram_loc       = &canRAM2,
  .par_loc       = &canPARRAM2,
  .par_xor       = 0x00001000,
  .par_cr_reg    = NULL,
  .par_cr_test   = 0,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_can,
  .fnc_data      = &TMS570_DCAN2
};

const tms570_esm_partest_desc_t
  tms570_partest_can3_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 22,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = CAN3PARITYCHECK_FAIL1,
  .ram_loc       = &canRAM3,
  .par_loc       = &canPARRAM3,
  .par_xor       = 0x00001000,
  .par_cr_reg    = NULL,
  .par_cr_test   = 0,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_can,
  .fnc_data      = &TMS570_DCAN3
};

const tms570_esm_partest_desc_t
  tms570_partest_vim_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 15,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = VIMPARITYCHECK_FAIL1,
  .ram_loc       = &VIMRAMLOC,
  .par_loc       = &VIMRAMPARLOC,
  .par_xor       = 0x00000001,
  .par_cr_reg    = &TMS570_VIM.PARCTL,
  .par_cr_test   = TMS570_VIM_PARCTL_TEST,
  .par_st_reg    = &TMS570_VIM.PARFLG,
  .par_st_clear  = TMS570_VIM_PARFLG_PARFLG,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_dma_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 3,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = DMAPARITYCHECK_FAIL1,
  .ram_loc       = &DMARAMLOC,
  .par_loc       = &DMARAMPARLOC,
  .par_xor       = 0x00000001,
  .par_cr_reg    = &TMS570_DMA.DMAPCR,
  .par_cr_test   = TMS570_DMA_DMAPCR_TEST,
  .par_st_reg    = &TMS570_DMA.DMAPAR,
  .par_st_clear  = TMS570_DMA_DMAPAR_EDFLAG,
  .partest_fnc   = tms570_partest_check_std,
  .fnc_data      = NULL
};

const tms570_esm_partest_desc_t
  tms570_partest_spi1_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 17,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = MIBSPI1PARITYCHECK_FAIL1,
  .ram_loc       = &MIBSPI1RAMLOC,
  .par_loc       = &mibspiPARRAM1,
  .par_xor       = 0x00000001,
  .par_cr_reg    = NULL,
  .par_cr_test   = 0,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_mibspi,
  .fnc_data      = &TMS570_SPI1
};

const tms570_esm_partest_desc_t
  tms570_partest_spi3_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 18,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = MIBSPI3PARITYCHECK_FAIL1,
  .ram_loc       = &MIBSPI3RAMLOC,
  .par_loc       = &mibspiPARRAM3,
  .par_xor       = 0x00000001,
  .par_cr_reg    = NULL,
  .par_cr_test   = 0,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_mibspi,
  .fnc_data      = &TMS570_SPI3
};

const tms570_esm_partest_desc_t
  tms570_partest_spi5_desc = {
  .esm_prim_grp  = 1,
  .esm_prim_chan = 24,
  .esm_sec_grp   = 0,
  .esm_sec_chan  = 0,
  .fail_code     = MIBSPI5PARITYCHECK_FAIL1,
  .ram_loc       = &MIBSPI5RAMLOC,
  .par_loc       = &mibspiPARRAM5,
  .par_xor       = 0x00000001,
  .par_cr_reg    = NULL,
  .par_cr_test   = 0,
  .par_st_reg    = NULL,
  .par_st_clear  = 0,
  .partest_fnc   = tms570_partest_check_mibspi,
  .fnc_data      = &TMS570_SPI5
};

void tms570_partest_check_run(
  const tms570_esm_partest_desc_t *
  const *desc_arr,
  int    desc_cnt
)
{
  int                              i;
  const tms570_esm_partest_desc_t *desc;

  for ( i = 0; i < desc_cnt; i++ ) {
    desc = desc_arr[ i ];
    desc->partest_fnc( desc );
  }
}
