#include "video.h"
#include "stdint.h"

#define VIDEO_MEM ((uint16_t*) 0xB8000)
#define SCREEN_W 80
#define SCREEN_H 25

static int __curx = 0;
static int __cury = 0;

void clear_screen() {
    __curx = 0;
    __cury = 0;
    for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
        VIDEO_MEM[i] = 0x1F00;
}

void puts(const char* str) {
    while (*str != 0) {
        if (*str == '\n') {
            __curx = 0;
            ++__cury;
        }
        else if (*str == '\r') {
            __curx = 0;
        }
        else {
            if (__curx >= SCREEN_W) {
                __curx = 0;
                ++__cury;
            }

            if (__cury >= SCREEN_H) {
                clear_screen();
            }

            int index = __curx + __cury * SCREEN_W;
            VIDEO_MEM[index] &= 0xFF00;
            VIDEO_MEM[index] |= *str;

            ++__curx;
        }

        ++str;
    }
}
