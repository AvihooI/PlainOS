#include "isr.h"
#include "interrupts.h"
#include "terminal.h"
#include "string.h"

/*
    Note that these functions aren't declared in a header file.
    The reason is that they should not be called from anywhere in code.
    They're only called by the processer through the IDT.
*/

//A minor sacrifice to the boilerplate god
extern void _isr_0();
extern void _isr_1();
extern void _isr_2();
extern void _isr_3();
extern void _isr_4();
extern void _isr_5();
extern void _isr_6();
extern void _isr_7();
extern void _isr_8();
extern void _isr_9();
extern void _isr_10();
extern void _isr_11();
extern void _isr_12();
extern void _isr_13();
extern void _isr_14();
extern void _isr_15();
extern void _isr_16();
extern void _isr_17();
extern void _isr_18();
extern void _isr_19();
extern void _isr_20();
extern void _isr_21();
extern void _isr_22();
extern void _isr_23();
extern void _isr_24();
extern void _isr_25();
extern void _isr_26();
extern void _isr_27();
extern void _isr_28();
extern void _isr_29();
extern void _isr_30();
extern void _isr_31();


static const dword isrs[32] = 
{
    (dword)_isr_0,(dword)_isr_1,(dword)_isr_2,(dword)_isr_3,
    (dword)_isr_4,(dword)_isr_5,(dword)_isr_6,(dword)_isr_7,
    (dword)_isr_8,(dword)_isr_9,(dword)_isr_10,(dword)_isr_11,
    (dword)_isr_12,(dword)_isr_13,(dword)_isr_14,(dword)_isr_15,
    (dword)_isr_16,(dword)_isr_17,(dword)_isr_18,(dword)_isr_19,
    (dword)_isr_20,(dword)_isr_21,(dword)_isr_22,(dword)_isr_23,
    (dword)_isr_24,(dword)_isr_25,(dword)_isr_26,(dword)_isr_27,
    (dword)_isr_28,(dword)_isr_29,(dword)_isr_30,(dword)_isr_31
};

extern void load_idt();

void isr_init()
{
    size_t i;

    for (i = 0; i < 31; i++)
    {
        set_idt_entry(i, isrs[i], 0x08, 0x8e);
    }
}

static const char * isr_exception_message[] =
{
    "Divide by zero",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "No math coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TSS",
    "Segment not present",
    "Stack segment fault",
    "General Protection",
    "Page Fault",
    "Reserved", //15
    "Floating Point",
    "Alignment Check",
    "Machine Check",
    "SIMD",
    "Virtualization",
    "Reserved", //21
    "Reserved", //22
    "Reserved", //23
    "Reserved", //24
    "Reserved", //25
    "Reserved", //26
    "Reserved", //27
    "Reserved", //28
    "Reserved", //29
    "Reserved", //30
    "Reserved"  //31
};


inline void print_regs(struct regs *r)
{
    char strb[9];
    
    terminal_insert_string("eax: ");
    dwordtostr(r->eax, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" ebx: ");
    dwordtostr(r->ebx, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" ecx: ");
    dwordtostr(r->ecx, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" edx: ");
    dwordtostr(r->edx, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" esi: ");
    dwordtostr(r->esi, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" edi: ");
    dwordtostr(r->edi, strb);
    terminal_insert_string(strb);
    terminal_insert_character('\n');
    
    terminal_insert_string("esp: ");
    dwordtostr(r->esp, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" ebp: ");
    dwordtostr(r->ebp, strb);
    terminal_insert_string(strb);
    terminal_insert_character('\n');

    terminal_insert_string("cs: ");
    dwordtostr(r->cs, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" ds: ");
    dwordtostr(r->ds, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" ss: ");
    dwordtostr(r->ss, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" fs: ");
    dwordtostr(r->fs, strb);
    terminal_insert_string(strb);
    terminal_insert_string(" gs: ");
    dwordtostr(r->gs, strb);
    terminal_insert_string(strb);
    terminal_insert_character('\n');
}

void processor_interrupt_handler(struct regs *r)
{
    dword cpl;

    cpl = (r->eflags & ((1 << 12) | (1 << 13))) >> 12;

    //if the interrupt came from kernel mode, we want to print an error message (effectively a BSOD) and halt the system
    if (!cpl)
    {
        char strb[9];
        terminal_clear(vga_color(VGA_GRAY, 1, VGA_BLUE,0));

        terminal_insert_string(isr_exception_message[r->int_no]);
        terminal_insert_string(" exception @ ");
        dwordtostr(r->eip, strb);
        terminal_insert_string(strb);
        terminal_insert_character('\n');

        print_regs(r);

        goto halt;
    }
    //else, do something else such as terminate the offending program (not yet implemented)
    else
    {

    }

    return;

    halt:

    for(;;)
    {
        asm("hlt");
    }
}