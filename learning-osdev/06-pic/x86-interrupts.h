#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__
#include "stdint.h"

extern void enable_interrupt(uint8_t num, void(*handler)());
extern void disable_interrupt(uint8_t num);
extern void flush_idt();

extern void __handle_irq_0x20();
extern void __handle_irq_impl_0x20();
extern void __handle_irq_0x21();
extern void __handle_irq_impl_0x21();

#endif
