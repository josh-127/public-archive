#include "stdint.h"
#include "video.h"
#include "x86.h"
#include "x86-interrupts.h"

#define PIC_MASTER_CMD  0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD   0xA0
#define PIC_SLAVE_DATA  0xA1

void __handle_irq_impl_0x20() {
    puts("Received IRQ 0x20.\n");

    // OCW2 - Send end-of-interrupt (EOI) code.
    __x86_outb(0x20, PIC_MASTER_CMD);
}

void __handle_irq_impl_0x21() {
    puts("Received IRQ 0x21.\n");

    // OCW2 - Send end-of-interrupt (EOI) code.
    __x86_outb(0x20, PIC_MASTER_CMD);
}

void kmain(void* multiboot_params, uint32_t magic) {
    clear_screen();
    puts("Hello World!\n");

    enable_interrupt(0x20, __handle_irq_0x20);
    enable_interrupt(0x21, __handle_irq_0x21);
    flush_idt();

    //
    // Here, we initialize the 8259 Programmable Interrupt Controller (PIC).
    //
    // Refer to Section 5.8.2 - Initialization Command Words (ICWx)
    // from Intel(R) 7 Series / C216 Chipset Family Platform Controller Hub (PCH) - Datasheet.
    //
    // Also refer to Section 13.4 - 8259 Interrupt Controller (PIC) Registers
    // from the same document for info about ICW bits.
    //

    __x86_outb(0x11, PIC_MASTER_CMD);  // ICW1 - Indicates initialization.
    __x86_outb(0x20, PIC_MASTER_DATA); // ICW2 - Master will emit IRQs 0x20-0x27.
    __x86_outb(0x4, PIC_MASTER_DATA);  // ICW3 - Points to slave PIC (must be 0x4; refer to Section 5.8 - Table 5-13).
    __x86_outb(0x1, PIC_MASTER_DATA);  // ICW4 - More parameters.

    __x86_outb(0x11, PIC_SLAVE_CMD);   // ICW1 - Ditto.
    __x86_outb(0x28, PIC_SLAVE_DATA);  // ICW2 - Slave will emit IRQs 0x28-0x2F.
    __x86_outb(0x2, PIC_SLAVE_DATA);   // ICW3 - Points to master PIC (can be 0x2, 0x4, or 0x8; refer to the same table).
    __x86_outb(0x1, PIC_SLAVE_DATA);   // ICW4 - More parameters.

    __x86_outb(0x0, PIC_MASTER_DATA);  // OCW1 - Clears IR mask (this is redundant, but whatever).
    __x86_outb(0x0, PIC_SLAVE_DATA);   // OCW1 - Ditto.

    __x86_sti();

    for (;;) {}
}
