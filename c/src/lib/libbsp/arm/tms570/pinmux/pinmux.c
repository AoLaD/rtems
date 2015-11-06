#include <bsp/tms570.h>
#include <bsp/tms570-pinmux.h>

void
tms570_bsp_pin_set_function(int pin_num, int pin_fnc)
{
  unsigned int pin_shift;

  if (pin_fnc == TMS570_PIN_FNC_AUTO) {
    pin_fnc = (pin_num & TMS570_PIN_FNC_MASK) >> TMS570_PIN_FNC_SHIFT;
    pin_num = (pin_num & TMS570_PIN_NUM_MASK) >> TMS570_PIN_NUM_SHIFT;
  }

  typeof(TMS570_IOMM.PINMUX.PINMMR0) *pinmmrx = &TMS570_IOMM.PINMUX.PINMMR0;
  pinmmrx += (pin_num >> 2);
  pin_shift = (pin_num & 0x3)*8;
  *pinmmrx = (*pinmmrx & ~(0xff << pin_shift))|(1<<(pin_fnc+pin_shift));
}

void
tms570_bsp_pin_clear_function(int pin_num, int pin_fnc)
{
  unsigned int pin_shift;

  if (pin_fnc == TMS570_PIN_FNC_AUTO) {
    pin_fnc = (pin_num & TMS570_PIN_FNC_MASK) >> TMS570_PIN_FNC_SHIFT;
    pin_num = (pin_num & TMS570_PIN_NUM_MASK) >> TMS570_PIN_NUM_SHIFT;
  }

  typeof(TMS570_IOMM.PINMUX.PINMMR0) *pinmmrx = &TMS570_IOMM.PINMUX.PINMMR0;
  pinmmrx += (pin_num >> 2);
  pin_shift = (pin_num & 0x3)*8;
  *pinmmrx = (*pinmmrx & ~(1<<(pin_fnc+pin_shift)));
}
