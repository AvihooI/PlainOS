#ifndef _io_h
#define _io_h

extern asmlinkage void outb(byte data, word port);
extern asmlinkage byte inb(word port);

#endif