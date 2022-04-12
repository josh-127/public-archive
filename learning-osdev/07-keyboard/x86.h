#ifndef __X86_H__
#define __X86_H__
#include "stdint.h"

void __x86_cli();
void __x86_sti();

void __x86_outb(uint8_t value, uint16_t port);
void __x86_outw(uint16_t value, uint16_t port);
void __x86_outd(uint32_t value, uint16_t port);
uint8_t __x86_inb(uint16_t port);
uint16_t __x86_inw(uint16_t port);
uint32_t __x86_ind(uint16_t port);

#endif
