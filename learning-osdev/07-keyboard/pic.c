#include "pic.h"

void pic_init() {
    __x86_outb(0x11, PIC_MASTER_CMD);
    __x86_outb(0x20, PIC_MASTER_DATA);
    __x86_outb(0x4, PIC_MASTER_DATA);
    __x86_outb(0x1, PIC_MASTER_DATA);

    __x86_outb(0x11, PIC_SLAVE_CMD);
    __x86_outb(0x28, PIC_SLAVE_DATA);
    __x86_outb(0x2, PIC_SLAVE_DATA);
    __x86_outb(0x1, PIC_SLAVE_DATA);

    __x86_outb(0x0, PIC_MASTER_DATA);
    __x86_outb(0x0, PIC_SLAVE_DATA);
}
