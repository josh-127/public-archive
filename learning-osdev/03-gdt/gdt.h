#ifndef __GDT_H__
#define __GDT_H__
#include "stdint.h"

#define GDT_PR     0x8000
#define GDT_PRIVL0 0x0000
#define GDT_PRIVL1 0x2000
#define GDT_PRIVL2 0x4000
#define GDT_PRIVL3 0x6000
#define GDT_S      0x1000
#define GDT_EX     0x0800
#define GDT_DC     0x0400
#define GDT_RW     0x0200
#define GDT_AC     0x0100
#define GDT_GR     0x0080
#define GDT_SZ     0x0040

#define GDT_DEFAULT_CODE (GDT_PR | GDT_S | GDT_EX | GDT_GR | GDT_SZ)
#define GDT_DEFAULT_DATA (GDT_PR | GDT_S | GDT_RW | GDT_GR | GDT_SZ)

struct gdt_desc {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  limit_high_flags;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_table {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

void gdt_desc_init(uint32_t base, uint32_t limit, uint16_t flags, struct gdt_desc* desc);

void x86_lgdt(struct gdt_table* ptr);

#endif
