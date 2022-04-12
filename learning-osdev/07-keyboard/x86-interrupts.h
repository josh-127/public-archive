#ifndef __X86_INTERRUPTS_H__
#define __X86_INTERRUPTS_H__

void enable_interrupt(uint8_t num, void(*handler)());
void disable_interrupt(uint8_t num);
void flush_idt();

extern void isr_timer();
extern void __isr_timer();

extern void isr_keyboard();
extern void __isr_keyboard();

#endif
