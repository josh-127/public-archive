#ifndef __SYS_H__
#define __SYS_H__

#define panic(msg) panic_at(__FILE__ ": ", msg)

void panic_at(const char* loc, const char* msg);

#endif
