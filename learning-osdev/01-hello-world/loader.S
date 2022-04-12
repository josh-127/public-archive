
.set MAGIC,    0x1BADB002
.set FLAGS,    (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)

.extern kmain
.global loader


.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .text
    loader:
        mov $kernel_stack, %esp
        push %eax
        push %ebx
        call kmain
    _idle:
        cli
        hlt
        jmp _idle


.section .bss
    .space 2*1024*1024
    kernel_stack:
