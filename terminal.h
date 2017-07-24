#ifndef _terminal_h
#define _terminal_h

#include "system.h"

#define VGA_BLACK   0 //Turns into dark gray with bright bit
#define VGA_BLUE    1
#define VGA_GREEN   2
#define VGA_CYAN    3
#define VGA_RED     4
#define VGA_MAGENTA 5
#define VGA_BROWN   6
#define VGA_GRAY    7 //Turns into white with bright bit

byte vga_color(byte fg_color, byte fg_bright, byte bg_color, byte bg_bright);

word vga_entry(byte vga_color, char character);

void terminal_clear(byte vga_color);

void terminal_put_entry(word vga_entry, size_t x, size_t y);

void terminal_put_character(char c, size_t x, size_t y);

void terminal_put_color(byte vga_color, size_t x, size_t y);

void terminal_increment();

void terminal_return();

void terminal_scroll();

void terminal_set_color(byte color);

void terminal_goto(size_t column, size_t row);

void terminal_insert_character(char c);

void terminal_insert_string(const char *str);

#endif
