
#define VIDEO_MEM   ((unsigned short*) 0xB8000)

void clear_screen() {
    for (int i = 0; i < 80*25; ++i)
        VIDEO_MEM[i] = 0x1F00;
}

void puts(const char* str) {
    for (int i = 0; str[i] != 0; ++i) {
        VIDEO_MEM[i] &= 0xFF00;
        VIDEO_MEM[i] |= str[i];
    }
}

void kmain(void* multiboot_params, unsigned magic_number) {
    clear_screen();
    puts("Hello World!");

    for (;;) {}
}
