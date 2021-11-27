
#include "cpu/isr.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "util.h"

int main()
{
    isr_install();

    init_keyboard();

    set_cursor_pos(0, 0);
    clearwin(COLOR_GRN, COLOR_BLK);

    const char *first = "\n\n\n\nWe can now handle some special characters.";

    putstr(first, COLOR_GRN, COLOR_BLK);

    const char *second = "\nLike tab \t and newline.";

    putstr(second, COLOR_GRN, COLOR_BLK);

    const char *third = "\nAnd it scrolls!";
    for (uint16_t i = 0; i < 10; i++)
    {
        putstr(third, COLOR_GRN, COLOR_BLK);
    }

    putstr("\nThis interrupt is most likely NOT a double-fault, but a problem with us not remapping IRQ 8, so it shows up on this channel\n", COLOR_GRN, COLOR_BLK);

    putstr("\n 0s > ", COLOR_GRN, COLOR_BLK);

    return 0;
}

void execute_command(char *input)
{
    if (compare_string(input, "EXIT") == 0)
    {
        putstr("\nStopping the CPU. Bye!\n", COLOR_GRN, COLOR_BLK);
        __asm__ volatile("hlt");
    }
    putstr("\nUnknown command: ", COLOR_GRN, COLOR_BLK);
    putstr(input, COLOR_GRN, COLOR_BLK);
    char str1[20];
    float f2 = get_timer() / 18.4;
    int_to_string((int)f2, str1);
    putstr("\n ", COLOR_GRN, COLOR_BLK);
    putstr(str1, COLOR_GRN, COLOR_BLK);
    putstr("s > ", COLOR_GRN, COLOR_BLK);
}
