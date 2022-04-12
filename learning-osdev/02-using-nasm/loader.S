
%define MAGIC     0x1BADB002
%define FLAGS     0x3
%define CHECKSUM -(MAGIC + FLAGS)

extern kmain
global loader


section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


section .text
    loader:
        mov esp, kernel_stack
        push eax
        push ebx
        call kmain
    .idle:
        cli
        hlt
        jmp .idle


section .bss
    resb 0x200000
    kernel_stack:
