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
        VIDEO_MEM[__curx + __cury * SCREEN_W] &= 0xFF00;

        if (*str == '\n') {
            __curx = 0;
            ++__cury;
        }
        else if (*str == '\r') {
            __curx = 0;
        }
        else {
            if (__curx >= (SCREEN_W - 1)) {
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

    VIDEO_MEM[__curx + __cury * SCREEN_W] &= 0xFF00;
    VIDEO_MEM[__curx + __cury * SCREEN_W] |= '_';
}

void putchar(char c) {
    char buffer[2] = { c, 0 };
    puts(buffer);
}

void rmchar() {
    VIDEO_MEM[__curx + __cury * SCREEN_W] &= 0xFF00;

    if (__curx > 0) {
        --__curx;
    }
    else if (__cury > 0) {
        --__cury;

        __curx = SCREEN_W - 1;
        while (__curx > 0 && (VIDEO_MEM[(__curx - 1) + __cury * SCREEN_W] & 0xFF) == 0)
            --__curx;
    }

    int index = __curx + __cury * SCREEN_W;
    VIDEO_MEM[index] &= 0xFF00;
    VIDEO_MEM[index] |= '_';
}
