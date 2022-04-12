
%macro HANDLE_IRQ 1
    global __handle_irq_%1
    extern __handle_irq_impl_%1
    __handle_irq_%1:
        pushad
        call __handle_irq_impl_%1
        popad
        iretd
%endmacro

%macro IDT_DESC 0
    dw 0
    dw 0x8
    db 0
    db 0b00001110
    dw 0
%endmacro

%macro IDT_DESC_8 0
    IDT_DESC
    IDT_DESC
    IDT_DESC
    IDT_DESC
    IDT_DESC
    IDT_DESC
    IDT_DESC
    IDT_DESC
%endmacro

%macro IDT_DESC_64 0
    IDT_DESC_8
    IDT_DESC_8
    IDT_DESC_8
    IDT_DESC_8
    IDT_DESC_8
    IDT_DESC_8
    IDT_DESC_8
    IDT_DESC_8
%endmacro

%macro IDT_DESC_256 0
    IDT_DESC_64
    IDT_DESC_64
    IDT_DESC_64
    IDT_DESC_64
%endmacro


global enable_interrupt
global disable_interrupt
global flush_idt


section .text
    HANDLE_IRQ 0x80
    HANDLE_IRQ 0x81

    enable_interrupt:
        push ebp
        mov ebp, esp
        mov ecx, DWORD [ebp + 0x8]
        mov edx, DWORD [ebp + 0xC]
        mov WORD [__idt_table + ecx * 8], dx
        shr edx, 16
        mov WORD [__idt_table + ecx * 8 + 6], dx
        mov dl, 0x80
        or BYTE [__idt_table + ecx * 8 + 5], dl
        leave
        ret

    disable_interrupt:
        push ebp
        mov ebp, esp
        mov dl, 0x7F
        and BYTE [__idt_table + ecx * 8 + 5], dl
        leave
        ret

    flush_idt:
        push ebp
        mov ebp, esp
        lidt [__idtptr]
        leave
        ret


section .data
    __idtptr:
        dw __idt_table_end - __idt_table - 1
        dd __idt_table

    __idt_table:
        IDT_DESC_256
    __idt_table_end:
