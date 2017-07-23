#include "terminal.h"

void kmain()
{
    terminal_clear(vga_color(VGA_GRAY, 1, VGA_BLUE,0));

    terminal_insert_string("Hello World\nHow are you\n");

    for (;;)
    {
        asm("hlt");
    }

    return;
}