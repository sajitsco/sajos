#include <stdint.h>
#include <stdbool.h>

int string_length(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = string_length(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void int_to_string(int n, char str[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void append(char s[], char n)
{
    int len = string_length(s);
    s[len] = n;
    s[len + 1] = '\0';
}

bool backspace(char s[])
{
    int len = string_length(s);
    if (len > 0)
    {
        s[len - 1] = '\0';
        return true;
    }
    else
    {
        return false;
    }
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int compare_string(char s1[], char s2[])
{
    int i;
    for (i = 0; s1[i] == s2[i]; i++)
    {
        if (s1[i] == '\0')
            return 0;
    }
    return s1[i] - s2[i];
}

//*************************************************************
// void prntnum(unsigned long n, int base, char sign, char *outbuf)
// unsigned long num = number to be printed
// int base        = number base for conversion;  decimal=10,hex=16
// char sign       = signed or unsigned output
// char *outbuf   = buffer to hold the output number
//*************************************************************

void prntnum(unsigned long num, int base, char sign, char *outbuf)
{

    int i = 12;
    int j = 0;

    do
    {
        outbuf[i] = "0123456789ABCDEF"[num % base];
        i--;
        num = num / base;
    } while (num > 0);

    if (sign != ' ')
    {
        outbuf[0] = sign;
        ++j;
    }

    while (++i < 13)
    {
        outbuf[j++] = outbuf[i];
    }

    outbuf[j] = 0;
}