# 07 - Keyboard

Writing a driver for a PS/2 Keyboard and the 8042 PS/2 Controller.

## Note

This will only run on a VM, not modern hardware. This is because modern
hardware no longer has a PS/2 controller (the Intel Chipset Datasheets don't
even mention the 8042 PS/2 Controller for this reason). Instead, it relies on
USB keyboards.
