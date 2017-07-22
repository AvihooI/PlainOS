#ifndef _interrupts_h
#define _interrutps_h

#include "system.h"

struct idt_entry
{
    word offset_lo;
    word  cs_selector;
    byte reserved;
    byte type_attr;
    word offset_hi;
} packed;

extern struct idt_entry _idt[256];

void set_idt_entry(size_t index, dword isr, word cs_selector, byte type_attr);

asmlinkage void interrupt_handler(struct regs *r);void set_idt_entry(size_t index, dword isr, word cs_selector, byte type_attr);

#endif