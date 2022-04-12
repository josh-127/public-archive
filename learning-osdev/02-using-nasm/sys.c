#include "sys.h"
#include "video.h"

void panic_at(const char* loc, const char* msg) {
    puts(loc);
    puts(msg);
    puts("\n");
    for (;;) {}
}
