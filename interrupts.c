#include "interrupts.h"

void set_idt_entry(size_t index, dword isr, word cs_selector, byte type_attr)
{
    _idt[index].reserved = 0;
    _idt[index].cs_selector = cs_selector;
    _idt[index].type_attr = type_attr;
    _idt[index].offset_lo = (word)((isr) & 0xffff);
    _idt[index].offset_hi = (word)((isr) >> (2*8));
}

extern void processor_interrupt_handler(struct regs *r);
extern void hardware_interrupt_handler(struct regs *r);
extern void user_interrupt_handler(struct regs *r);

asmlinkage void interrupt_handler(struct regs *r)
{
    /*
        There are three general cases:
        int_no < 32 - an exception interrupt (processor generated interrupts due to exceptions)
        32 <= int_no < 47 - I/O interrupts (IRQs)
        int_no > 47 - software generated interrupts

        The purpose of this function is to channel the interrupt to a function that's dealing with the particular type
    */

    if (r->int_no < 32)
    {
        //processor interrupts
        processor_interrupt_handler(r);

    }
    else if (r->int_no < 47)
    {
        //hardware IRQs
        hardware_interrupt_handler(r);
    }
    else
    {
        //user interrutps
        user_interrupt_handler(r);
    }
}