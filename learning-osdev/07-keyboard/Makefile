
QEMU_TARGET	:= qemu-image.img
KERNEL		:= kernel

CFLAGS		:= -m32 -nostdlib -fno-builtin -fno-leading-underscore
ASFLAGS		:= -felf32
LDFLAGS		:= -melf_i386

OFILES		:= kernel.o pic.o video.o x86.o x86-interrupts.o loader.o
GRUB_CFG	:= grub.cfg

.PHONY: all qemu clean

all: $(KERNEL)

qemu: $(QEMU_TARGET)
	qemu-system-i386 $(QEMU_TARGET)

clean:
	rm *.o $(KERNEL) $(QEMU_TARGET)

$(QEMU_TARGET): $(KERNEL) $(GRUB_CFG)
	mkdir -p qemu-image/boot/grub
	cp $(KERNEL) qemu-image/boot/
	cp $(GRUB_CFG) qemu-image/boot/grub/
	grub-mkrescue --output=$@ qemu-image
	rm -r qemu-image

$(KERNEL): linker.ld $(OFILES)
	ld $(LDFLAGS) -T$< -o$@ $(OFILES)

%.o: %.c
	gcc $(CFLAGS) -o$@ -c $<

%.o: %.S
	nasm $(ASFLAGS) -o$@ $<
