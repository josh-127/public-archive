
global __x86_cli
global __x86_sti
global __x86_outb
global __x86_outw
global __x86_outd
global __x86_inb
global __x86_inw
global __x86_ind

section .text
    __x86_cli:
        push ebp
        mov ebp, esp
        cli
        leave
        ret

    __x86_sti:
        push ebp
        mov ebp, esp
        sti
        leave
        ret

    __x86_outb:
        push ebp
        mov ebp, esp
        mov al, BYTE [ebp + 0x8]
        mov dx, WORD [ebp + 0xC]
        out dx, al
        leave
        ret

    __x86_outw:
        push ebp
        mov ebp, esp
        mov ax, WORD [ebp + 0x8]
        mov dx, WORD [ebp + 0xC]
        out dx, ax
        leave
        ret

    __x86_outd:
        push ebp
        mov ebp, esp
        mov eax, DWORD [ebp + 0x8]
        mov dx, WORD [ebp + 0xC]
        out dx, eax
        leave
        ret

    __x86_inb:
        push ebp
        mov ebp, esp
        xor eax, eax
        mov dx, WORD [ebp + 0x8]
        in al, dx
        leave
        ret

    __x86_inw:
        push ebp
        mov ebp, esp
        xor eax, eax
        mov dx, WORD [ebp + 0x8]
        in ax, dx
        leave
        ret

    __x86_ind:
        push ebp
        mov ebp, esp
        mov dx, WORD [ebp + 0x8]
        in eax, dx
        leave
        ret
