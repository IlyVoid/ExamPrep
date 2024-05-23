#include <unistd.h>
#include <stdarg.h>

void    put_str(char *s, int *l)
{
    if (!s)
        s = "(null)";
    while (*s)
        *l += write(1, s++, 1);
}

void    put_digit(long long int nbr, int base, int *l)
{
    char    *hexa = "0123456789abcdef";

    if (nbr < 0)
    {
        nbr *= -1;
        l += write(1, "-", 1);
    }
    if (nbr >= base)
        put_digit((nbr / base), base, l);
    *l += write(1, &hexa[nbr % base], 1);
}

int ft_printf(const char *f, ...)
{
    int l;

    va_list list;
    va_start(list, f);
    while (*f)
    {
        if ((*f == '%') && ((*(f + 1) == 's') || (*(f + 1) == 'd') || (*(f + 1) == 'x')))
        {
            f++;
            if (*f == 's')
                put_str(va_arg(list, char *), &l);
            else if (*f == 'd')
                put_digit((long long int)va_arg(list, int), 10, &l);
            else if (*f == 'x')
                put_digit((long long int)va_arg(list, unsigned int), 16, &l);
        }
        else
            l += write(1, f, 1);
        f++;
    }
    return (va_end(list), l);
}

int main()
{
    ft_printf("%s\n", "this is 42 with hexadecimal 2a");
    ft_printf("%d\n", 42);
    ft_printf("%x\n", 42);
}