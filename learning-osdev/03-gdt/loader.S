
%define MAGIC     0x1BADB002
%define FLAGS     0x3
%define CHECKSUM -(MAGIC + FLAGS)

extern kmain
global __loader


section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


section .text
    __loader:
        lgdt [__gdtptr]
        jmp 0x8:.L1
    .L1:

        mov esp, kernel_stack
        push eax
        push ebx
        call kmain
    .idle:
        cli
        hlt
        jmp .idle

section .rodata
    __gdtptr:
        dw __gdt_data_end - __gdt_data - 1
        dd __gdt_data

    __gdt_data:
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
    __gdt_data_end:


section .bss
    resb 0x200000
    kernel_stack:
