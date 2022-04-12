#include "stdint.h"
#include "sys.h"
#include "video.h"

void kmain(void* multiboot_params, uint32_t magic_number) {
    clear_screen();
    puts("Hello World!\n");

    for (;;) {}
}
