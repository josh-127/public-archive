#include "pic.h"
#include "video.h"
#include "x86.h"
#include "x86-interrupts.h"

#define KBD_DATA        0x60
#define KBD_STATUS      0x64
#define KBD_CMD         0x64

void keyboard_wait_read() {
    while ((__x86_inb(KBD_STATUS) & 0x1) == 0) {}
}

void keyboard_wait_write() {
    while ((__x86_inb(KBD_STATUS) & 0x10) == 0) {}
}

void keyboard_init() {
    // Flush out keyboard's output buffer.
    while (__x86_inb(KBD_STATUS) & 0x1)
        __x86_inb(KBD_DATA);

    // Enable first PS/2 port.
    keyboard_wait_write();
    __x86_outb(0xAE, KBD_CMD);

    // Configure PS/2 controller.
    keyboard_wait_write();
    __x86_outb(0x20, KBD_CMD);              // Tell PS/2 controller that we're
                                            // gonna read the configuration.

    keyboard_wait_read();

    uint8_t config = __x86_inb(KBD_DATA);   // Read configuration.
    config |= 0x1;                          // Enable first PS/2 port interrupt.
    config &= ~0x10;                        // Enable first PS/2 port clock.

    keyboard_wait_write();
    __x86_outb(0x60, KBD_CMD);              // Tell PS/2 controller that we're
                                            // gonna write to the configuration.
    __x86_outb(config, KBD_DATA);           // Write configuration.

    // Enable scanning (keyboard will send scan codes).
    __x86_outb(0xF4, KBD_DATA);
}

void isr_timer() {
    __x86_outb(0x20, PIC_MASTER_CMD);
}

void isr_keyboard() {
    uint8_t scancode = __x86_inb(0x60);

    if ((scancode & 0x80) == 0) {
        switch (scancode) {
        case 0x2: putchar('1'); break;
        case 0x3: putchar('2'); break;
        case 0x4: putchar('3'); break;
        case 0x5: putchar('4'); break;
        case 0x6: putchar('5'); break;
        case 0x7: putchar('6'); break;
        case 0x8: putchar('7'); break;
        case 0x9: putchar('8'); break;
        case 0xA: putchar('9'); break;
        case 0xB: putchar('0'); break;

        case 0xC: putchar('-'); break;
        case 0xD: putchar('='); break;
        case 0xE: rmchar();     break;
        case 0xF: puts("    "); break;

        case 0x10: putchar('Q'); break;
        case 0x11: putchar('W'); break;
        case 0x12: putchar('E'); break;
        case 0x13: putchar('R'); break;
        case 0x14: putchar('T'); break;
        case 0x15: putchar('Y'); break;
        case 0x16: putchar('U'); break;
        case 0x17: putchar('I'); break;
        case 0x18: putchar('O'); break;
        case 0x19: putchar('P'); break;
        case 0x1A: putchar('['); break;
        case 0x1B: putchar(']'); break;
        case 0x1C: putchar('\n'); break;

        case 0x1E: putchar('A'); break;
        case 0x1F: putchar('S'); break;
        case 0x20: putchar('D'); break;
        case 0x21: putchar('F'); break;
        case 0x22: putchar('G'); break;
        case 0x23: putchar('H'); break;
        case 0x24: putchar('J'); break;
        case 0x25: putchar('K'); break;
        case 0x26: putchar('L'); break;
        case 0x27: putchar(';'); break;
        case 0x28: putchar('\''); break;
        case 0x29: putchar('`'); break;

        case 0x2B: putchar('\\'); break;
        case 0x2C: putchar('Z'); break;
        case 0x2D: putchar('X'); break;
        case 0x2E: putchar('C'); break;
        case 0x2F: putchar('V'); break;
        case 0x30: putchar('B'); break;
        case 0x31: putchar('N'); break;
        case 0x32: putchar('M'); break;
        case 0x33: putchar(','); break;
        case 0x34: putchar('.'); break;
        case 0x35: putchar('/'); break;

        case 0x39: putchar(' '); break;

        default:
            puts("Received scancode: 0x");
            putchar("0123456789ABCDEF"[(scancode & 0xF0) >> 4]);
            putchar("0123456789ABCDEF"[scancode & 0xF]);
            puts("\n");
            break;
        }
    }

    __x86_outb(0x20, PIC_MASTER_CMD);
}

void kmain() {
    clear_screen();
    puts("Hello World!\n");

    enable_interrupt(0x20, __isr_timer);
    enable_interrupt(0x21, __isr_keyboard);
    flush_idt();

    pic_init();
    keyboard_init();

    __x86_sti();

    for (;;) {}
}
