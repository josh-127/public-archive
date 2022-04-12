#include "gdt.h"
#include "sys.h"

void gdt_desc_init(
    uint32_t base, uint32_t limit, uint16_t flags, struct gdt_desc* desc)
{
    if ((flags & GDT_GR) && (limit & 0xFFF) != 0) {
        panic("GDT limit must be divisible by 4096.");
    }

    desc->limit_low         = limit & 0xFFFF;
    desc->base_low          = base & 0xFFFF;
    desc->base_mid          = (base & 0xFF0000) >> 16;
    desc->access            = (flags & 0xFF00) >> 8;
    desc->limit_high_flags  = (flags & 0xF0);
    desc->limit_high_flags |= (limit & 0xF00) >> 8;
    desc->base_high         = 0xFF000000 >> 24;
}
