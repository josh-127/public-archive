#!/bin/bash

nasm -fbin -opayload.bin payload.asm

echo -e "\n\n ==== DISASSEMBLY ==== "
objdump -bbinary -D -mi386:x86-64 payload.bin

echo -e "\n\n ==== HEX DATA ==== "
xxd -g1 payload.bin

echo -e "\n\n\n"
