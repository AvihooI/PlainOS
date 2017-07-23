#include "terminal.h"

static volatile word* const TERMINAL_BUFFER = (word *)0xB8000;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const size_t VGA_SIZE = 2000;

static size_t terminal_row = 0;
static size_t terminal_column = 0;
static byte terminal_current_color = 0;

byte vga_color(byte fg_color, byte fg_bright, byte bg_color, byte bg_bright)
{
    byte result;

    result = ((fg_color & 0x00FF) << 0) |
             ((fg_bright & 1) << 3)       |
             ((bg_color & 0x00FF) << 4)   |
             ((bg_bright & 1) << 7);

    return result;
}

word vga_entry(byte vga_color, char c)
{
    word result;

    result = c | (vga_color << 8);

    return result;
}

void terminal_clear(byte vga_color)
{
    size_t i;

    terminal_column = 0;
    terminal_row = 0;

    for (i = 0; i < VGA_SIZE; i++)
    {
        TERMINAL_BUFFER[i] = vga_entry(vga_color, ' ');
    }
}

void terminal_put_entry(word vga_entry, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;

    TERMINAL_BUFFER[index] = vga_entry;
}

void terminal_put_character(char c, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;

    //preserve the color information but change the character
    TERMINAL_BUFFER[index] = c | (TERMINAL_BUFFER[index] & 0xFF00);
}

void terminal_put_color(byte vga_color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;

    //preserve the character information but change the color
    TERMINAL_BUFFER[index] = (vga_color << 8) | (TERMINAL_BUFFER[index] & 0x00FF);
}

void terminal_increment()
{
    terminal_column++;

    if (terminal_column == VGA_WIDTH)
        terminal_return();
}

void terminal_return()
{
    terminal_column = 0;
    terminal_row++;

    if (terminal_row == VGA_HEIGHT)
        terminal_scroll();
}

void terminal_scroll()
{
    size_t x,y;

    for (y = 0; y < (VGA_HEIGHT-1); y++)
    {
        for (x = 0; x < VGA_WIDTH; x++)
        {
            const size_t next_index = (y+1) * VGA_WIDTH + x;
            const size_t current_index = y * VGA_WIDTH + x;

            TERMINAL_BUFFER[current_index] = TERMINAL_BUFFER[next_index];
        }
    }

    for (x = 0; x < VGA_WIDTH; x++)
    {
        terminal_put_character(' ', x, VGA_HEIGHT - 1);
    }

    terminal_row--;
}

void terminal_set_color(byte color)
{
    terminal_current_color = color;
}

void terminal_insert_character(char c)
{
    if (c == '\n')
    {
        terminal_return();
    }
    else
    {
        terminal_put_character(c, terminal_column, terminal_row);
        terminal_increment();
    }
}

void terminal_goto(size_t column, size_t row)
{
    //making sure we don't go to an invalid place
    if (column >= VGA_WIDTH || row >= VGA_HEIGHT)
        return;

    terminal_column = column;
    terminal_row = row;
}