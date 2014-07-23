/**
 * @file
 *
 * @ingroup tms570
 *
 * @brief Startup code.
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


#include <bsp.h>
#include <bsp/linker-symbols.h>

#define TMS570_POM_REGIONS 32

#define TMS570_POM_REGSIZE_DISABLED 0
#define TMS570_POM_REGSIZE_64B      1
#define TMS570_POM_REGSIZE_128B     2
#define TMS570_POM_REGSIZE_256B     3
#define TMS570_POM_REGSIZE_5120B    4
#define TMS570_POM_REGSIZE_1KB      5
#define TMS570_POM_REGSIZE_2KB      6
#define TMS570_POM_REGSIZE_4KB      7
#define TMS570_POM_REGSIZE_8KB      8
#define TMS570_POM_REGSIZE_16KB     9
#define TMS570_POM_REGSIZE_32KB   0xa
#define TMS570_POM_REGSIZE_64KB   0xb
#define TMS570_POM_REGSIZE_128KB  0xc
#define TMS570_POM_REGSIZE_256KB  0xd

#define TMS570_POM_REGADDRMASK    ((1<<23)-1)

#define TMS570_POM_GLBCTRL_ENABLE 0x000000a0a

typedef struct tms570_pom_region_t {
  uint32_t PROGSTART;
  uint32_t OVLSTART;
  uint32_t REGSIZE;
  uint32_t res0;
} tms570_pom_region_t;

typedef struct tms570_pom_t {
  uint32_t GLBCTRL;     /* 000h Global Control Register */
  uint32_t REV;         /* 004h Revision ID */
  uint32_t CLKCTRL;     /* 008h Clock Gate Control Register */
  uint32_t FLG;         /* 00Ch Status Register */
  uint32_t res0[0x1f0/4];
  tms570_pom_region_t REG[TMS570_POM_REGIONS]; /* 200h Program Regions */
  uint32_t res1[0xb00/4];
  uint32_t ITCTRL;	/* F00h Integration Control Register */
  uint32_t res2[0x09c/4];
  uint32_t CLAIMSET;	/* FA0h Claim Set Register */
  uint32_t CLAIMCLR;	/* FA4h Claim Clear Register */
  uint32_t res3[0x008/4];
  uint32_t LOCKACCESS;	/* FB0h Lock Access Register */
  uint32_t LOCKSTATUS;	/* FB4h Lock Status Register */
  uint32_t AUTHSTATUS;	/* FB8h Authentication Status Register */
  uint32_t res4[0x00c/4];
  uint32_t DEVID;	/* FC8h Device ID Register */
  uint32_t DEVTYPE;	/* FCCh Device Type Register */
  uint32_t PERIPHERALID4;	/* FD0h Peripheral ID 4 Register */
  uint32_t PERIPHERALID5;	/* FD4h Peripheral ID 5 Register */
  uint32_t PERIPHERALID6;	/* FD8h Peripheral ID 6 Register */
  uint32_t PERIPHERALID7;	/* FDCh Peripheral ID 7 Register */
  uint32_t PERIPHERALID0;	/* FE0h Peripheral ID 0 Register */
  uint32_t PERIPHERALID1;	/* FE4h Peripheral ID 1 Register */
  uint32_t PERIPHERALID2;	/* FE8h Peripheral ID 2 Register */
  uint32_t PERIPHERALID3;	/* FECh Peripheral ID 3 Register */
  uint32_t COMPONENTID0;	/* FF0h Component ID 0 Register */
  uint32_t COMPONENTID1;	/* FF4h Component ID 1 Register */
  uint32_t COMPONENTID2;	/* FF8h Component ID 2 Register */
  uint32_t COMPONENTID3;	/* FFCh Component ID 3 Register */
} tms570_pom_t;

#define TMS570_POM (*(volatile tms570_pom_t*)0xffa04000)


//bsp_start_vector_table_begin



int mem_dump(void *buf, unsigned long start, unsigned long len, int blen)
{
  unsigned long addr=start;
  volatile unsigned char *p=buf;
  int i;

  while(len){
    printk("%08lX:",addr);
    i=len>16?16:len;
    addr+=i;
    len-=i;
    while(i>0){
      i -= blen;
      switch(blen){
        case 4:
          printk("%08lX%c",(unsigned long)*(volatile uint32_t*)p,i>0?' ':'\n');
          break;
        case 2:
          printk("%04X%c",*(volatile uint16_t*)p,i>0?' ':'\n');
          break;
        default:
          printk("%02X%c",*(volatile uint8_t*)(p),i>0?' ':'\n');
          break;
      }
      p += blen;
    }
  }
  return 0;
}

void tms570_pom_remap(void)
{

    int i;
    uint32_t vec_overlay_start = 0x08000000;
    volatile uint32_t *p32 = (uint32_t *)vec_overlay_start;

    memcpy((void*)vec_overlay_start, bsp_start_vector_table_begin, 64);

    TMS570_POM.GLBCTRL = 0;

    for (i = 0; i < TMS570_POM_REGIONS; i++)
        TMS570_POM.REG[i].REGSIZE = TMS570_POM_REGSIZE_DISABLED;

    TMS570_POM.REG[0].PROGSTART = 0x0 & TMS570_POM_REGADDRMASK;
    TMS570_POM.REG[0].OVLSTART = vec_overlay_start & TMS570_POM_REGADDRMASK;
    TMS570_POM.REG[0].REGSIZE = TMS570_POM_REGSIZE_64B;

    TMS570_POM.GLBCTRL = TMS570_POM_GLBCTRL_ENABLE |
                         (vec_overlay_start & ~TMS570_POM_REGADDRMASK);

  #ifdef POM_REMAP_TEST
    p32[1] = 0xe12fff1e;

    mem_dump((uint8_t *)0x00000000, 0x00000000, 256, 1);

    printk("Probing call to address 0x00000004\n");
    ((void(*)(void))4)();
    printk("POM call really returned\n");
  #endif /*POM_REMAP_TEST*/
}



void bsp_pretasking_hook( void )
{

}

void bsp_start( void )
{

    /* set the cpu mode to supervisor and big endian */
    arm_cpu_mode = 0x213;

    tms570_pom_remap();

    /* Interrupts */
    bsp_interrupt_initialize();

}
