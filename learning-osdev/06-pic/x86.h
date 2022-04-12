#ifndef __X86_H__
#define __X86_H__
#include "stdint.h"

extern void __x86_cli();
extern void __x86_sti();

extern void __x86_outb(uint8_t value, uint16_t port);
extern void __x86_outw(uint16_t value, uint16_t port);
extern void __x86_outd(uint32_t value, uint16_t port);
extern uint8_t __x86_inb(uint16_t port);
extern uint16_t __x86_inw(uint16_t port);
extern uint32_t __x86_ind(uint16_t port);

#endif
