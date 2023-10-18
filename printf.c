#include "main.h"
#include <stdio.h>

/**
 * _printf - Emulate a simplified version of printf.
 * @format: The format string.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int count = 0;
	const char *p = format;

	while (*p)
	{
		if (*p == '%')
		{
			p++;
			if (*p == 'c')
			{
				int character = va_arg(args, int);
				putchar(character);
				count++;
			}
			else if (*p == 's')
			{
				const char *str = va_arg(args, const char *);
				for (int i = 0; str[i] != '\0'; i++)
				{
					putchar(str[i]);
					count++;
				}
			}
			else if (*p == '%')
			{
				putchar('%');
				count++;
			}
		}
		else
		{
			putchar(*p);
			count++;
		}
		p++;
	}

	va_end(args);
	return count;
}
