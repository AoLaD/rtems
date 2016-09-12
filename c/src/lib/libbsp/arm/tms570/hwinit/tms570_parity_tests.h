#ifndef LIBBSP_ARM_TMS570_PARITY_TESTS_H
#define LIBBSP_ARM_TMS570_PARITY_TESTS_H

#include <stdint.h>

#define TMS570_PARTEST_CR_KEY 0xA

typedef struct tms570_esm_partest_desc tms570_esm_partest_desc_t;

typedef void tms570_partest_fnc_t( const tms570_esm_partest_desc_t *desc );

struct tms570_esm_partest_desc {
  unsigned char esm_prim_grp;
  unsigned char esm_prim_chan;
  unsigned char esm_sec_grp;
  unsigned char esm_sec_chan;
  int fail_code;
  volatile uint32_t *ram_loc;
  volatile uint32_t *par_loc;
  uint32_t par_xor;
  volatile uint32_t *par_cr_reg;
  uint32_t par_cr_test;
  volatile uint32_t *par_st_reg;
  uint32_t par_st_clear;
  tms570_partest_fnc_t *partest_fnc;
  volatile void *fnc_data;
};

extern const tms570_esm_partest_desc_t
  tms570_partest_het1_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_htu1_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_het2_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_htu2_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_adc1_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_adc2_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_can1_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_can2_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_can3_desc;
extern const tms570_esm_partest_desc_t
  tms570_partest_vim_desc;
const tms570_esm_partest_desc_t
  tms570_partest_dma_desc;
const tms570_esm_partest_desc_t
  tms570_partest_spi1_desc;
const tms570_esm_partest_desc_t
  tms570_partest_spi3_desc;
const tms570_esm_partest_desc_t
  tms570_partest_spi5_desc;

extern const tms570_esm_partest_desc_t *const
tms570_esm_partest_list[];

extern const int tms570_esm_partest_list_size;

void tms570_partest_check_std( const tms570_esm_partest_desc_t *desc );

void tms570_partest_check_can( const tms570_esm_partest_desc_t *desc );

void tms570_partest_check_mibspi( const tms570_esm_partest_desc_t *desc );

void tms570_partest_check_run(
  const tms570_esm_partest_desc_t *
  const *desc_arr,
  int    desc_cnt
);

#endif /* LIBBSP_ARM_TMS570_PARITY_TESTS_H */
