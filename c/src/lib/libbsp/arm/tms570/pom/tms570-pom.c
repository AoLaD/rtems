#include <stdint.h>
#include <bsp/tms570-pom.h>
#include <bsp/linker-symbols.h>

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
