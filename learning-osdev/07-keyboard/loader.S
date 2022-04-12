
%define MAGIC    0x1BADB002
%define FLAGS    0x3
%define CHECKSUM -(MAGIC + FLAGS)

global __loader
extern kmain
extern flush_idt

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


section .text
    __loader:
        cli
        lgdt [__gdtptr]
        jmp 0x8:.flush_gdt
    .flush_gdt:
        call flush_idt

        mov esp, __kernel_stack
        push eax
        push ebx
        call kmain
    .idle:
        cli
        hlt
        jmp .idle


section .rodata
    __gdtptr:
        dw __gdt_table_end - __gdt_table - 1
        dd __gdt_table

    __gdt_table:
        ; Null Descriptor
        dd 0
        dd 0
        ; Code Descriptor
        dw 0xFFFF
        dw 0
        db 0
        db 0b10011010
        db 0b11001111
        db 0
        ; Data Descriptor
        dw 0xFFFF
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0
    __gdt_table_end:


section .bss
    resb 0x200000
    __kernel_stack:
