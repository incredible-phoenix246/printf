#include "main.h"

/**
 * handle_print - Handle format specifier and print content
 * @format: The format string
 * @i: Pointer to the current index in the format string
 * @list: The va_list of arguments
 * @buffer: The output buffer
 * @spec: The format specifier information
 * Return: Number of characters printed
 */
int handle_print(const char *format, int *i, va_list list, char buffer[], FormatSpec spec) {
    int printed_chars = 0;

    if (format[*i] == 'd') {
        int value = va_arg(list, int);
        char num_buffer[12]; // For a 32-bit integer in base 10
        int len = snprintf(num_buffer, sizeof(num_buffer), "%d", value);
        // Copy the formatted number to the output buffer
        for (int j = 0; j < len; j++) {
            buffer[(*i)++] = num_buffer[j];
            printed_chars++;
        }
    } else if (format[*i] == 's') {
        char *str = va_arg(list, char *);
        if (str == NULL)
            str = "(null)";
        while (*str) {
            buffer[(*i)++] = *str;
            printed_chars++;
            str++;
        }
    }

    return printed_chars;
}

/**
 * get_flags - Extract and return flags from the format string
 * @format: The format string
 * @i: Pointer to the current index in the format string
 * Return: The combined flags value
 */
int get_flags(const char *format, int *i) {
    int flags = 0;

    while (format[*i] == '-' || format[*i] == '+' || format[*i] == '0' || format[*i] == '#' || format[*i] == ' ') {
        // Update the 'flags' variable based on the flags in the format string
        (*i)++;
    }

    return flags;
}

/**
 * get_width - Extract and return width from the format string
 * @format: The format string
 * @i: Pointer to the current index in the format string
 * @list: The va_list of arguments
 * Return: The width value
 */
int get_width(const char *format, int *i, va_list list) {
    int width = 0;

    if (format[*i] == '*') {
        width = va_arg(list, int);
        (*i)++;
    } else {
        // Read and convert numeric width from format
        while (format[*i] >= '0' && format[*i] <= '9') {
            width = width * 10 + (format[(*i)++] - '0');
        }
    }

    return width;
}

/**
 * get_precision - Extract and return precision from the format string
 * @format: The format string
 * @i: Pointer to the current index in the format string
 * @list: The va_list of arguments
 * Return: The precision value
 */
int get_precision(const char *format, int *i, va_list list) {
    int precision = -1;

    // Implementation for extracting precision (e.g., .10, .* for dynamic precision)
    if (format[*i] == '.') {
        (*i)++; // Move past the '.'
        if (format[*i] == '*') {
            precision = va_arg(list, int);
            (*i)++;
        } else {
            precision = 0;
            // Read and convert numeric precision from format
            while (format[*i] >= '0' && format[*i] <= '9') {
                precision = precision * 10 + (format[(*i)++] - '0');
            }
        }
    }

    return precision;
}

/**
 * get_size - Extract and return size from the format string
 * @format: The format string
 * @i: Pointer to the current index in the format string
 * Return: The size value
 */
int get_size(const char *format, int *i) {
    int size = 0;

    if (format[*i] == 'h' || format[*i] == 'l') {
        size = format[(*i)++];
    }

    return size;
}
