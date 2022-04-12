#include "video.h"
#include "stdint.h"

#define VIDEO_MEM ((uint16_t*) 0xB8000)
#define SCREEN_W 80
#define SCREEN_H 25

static int __cur_x = 0;
static int __cur_y = 0;

void clear_screen() {
    for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
        VIDEO_MEM[i] = 0x1F00;
}

void puts(const char* str) {
    while (*str != 0) {
        if (*str == '\n') {
            __cur_x = 0;
            ++__cur_y;
        }
        else if (*str == '\r') {
            __cur_x = 0;
        }
        else {
            if (__cur_x >= SCREEN_W) {
                __cur_x = 0;
                ++__cur_y;
            }

            int index = __cur_x + __cur_y * SCREEN_W;

            VIDEO_MEM[index] &= 0xFF00;
            VIDEO_MEM[index] |= *str;
            ++__cur_x;
        }

        ++str;
    }
}
