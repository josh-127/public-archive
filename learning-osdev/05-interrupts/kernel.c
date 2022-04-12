#include "x86-interrupts.h"
#include "stdint.h"
#include "video.h"

void __handle_irq_impl_0x80() {
    puts("Interrupt Received: 0x80.\n");
}

void __handle_irq_impl_0x81() {
    puts("Interrupt Received: 0x81.\n");
}

void kmain(void* multiboot_params, uint32_t magic) {
    clear_screen();
    puts("Hello World!\n");

    enable_interrupt(0x80, __handle_irq_0x80);
    enable_interrupt(0x81, __handle_irq_0x81);
    flush_idt();
    
    asm volatile("int $0x80");
    asm volatile("int $0x81");

    for (;;) {}
}
