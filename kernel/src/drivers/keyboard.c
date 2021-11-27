#include <stdbool.h>
#include "drivers/keyboard.h"
#include "cpu/ports.h"
#include "cpu/isr.h"
#include "drivers/vga.h"
#include "util.h"
#include "kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '\b', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

void fun1()
{
    putstr("\rddd \n", COLOR_WHT, COLOR_RED);
}

void keyboard_callback(registers *reg)
{
    uint8_t scancode = byte_in(0x60);
    if (scancode > SC_MAX)
        return;
    /*if (scancode == BACKSPACE)
    {
        if (backspace(key_buffer))
        {
            // print_backspace();
        }
    }
    else if (scancode == ENTER)
    {
        // print_nl();
        // execute_command(key_buffer);
        key_buffer[0] = '\0';
    }
    else
    {
        char letter = sc_ascii[(int)scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        putstr(str, COLOR_GRN, COLOR_BLK);
    }*/
    if (scancode == ENTER)
    {
        execute_command(key_buffer);
        key_buffer[0] = '\0';
    }
    else
    {
        char letter = sc_ascii[(int)scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        putstr(str, COLOR_GRN, COLOR_BLK);
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}