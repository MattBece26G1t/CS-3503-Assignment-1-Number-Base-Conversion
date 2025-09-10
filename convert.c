// convert.c file

#include <stdio.h> // For printing and reading files
#include <stdint.h> // For uint32_t
#include <string.h> // String functions

// Method div_convert
void div_convert(uint32_t n, int base, char *out)
{
    char temporary [65]; // Temporary buffer
    int position = 0; // Write index in temp

    // Handle zero case
    if ( n == 0) 
    {
        strcpy ( out , "0");
        return;
    }

    // Extract digits from right to left
    while ( n > 0) 
    {
        int remainder = n % base;
        n = n / base;

        // Convert digit to character
        if ( remainder < 10)
        {
            temporary [ position ++] = '0' + remainder;
        }

        else
        {
            temporary [ position ++] = 'A' + ( remainder - 10);
        }
    }

    // Reverse the result
    int i = 0;
    int j = position - 1;
    
    // Copy digits in reverse order
    while (j >= 0)
    {
        out[i] = temporary[j];
        i++;
        j--;
    }

     // Null terminator
     out[i] = '\0';
}

// Method sub_convert
void sub_convert(uint32_t n, int base, char *out)
{
    int position = 0; // Write index in out

    // Handle zero case
     if (n == 0) 
     { 
        strcpy(out, "0"); 
        return; 
    }

    // Locate largest power that suits
    uint32_t power = 1;
    uint32_t limit = n / base;

    // Multiply power by base until multiple exceeds n
    while (power <= limit) 
    {
        power = power * base;
    }

    // Extract digits left to right
    while (power > 0) 
    {
        // Value of n is reduced by itself 
        // with the found digit amount times power
        uint32_t digit = n / power;
        n = n - digit * power;

        // Convert digit to character
        if (digit < 10)
        {
            out[position++] = '0' + digit;
        }

        else
        {
            out[position++] = 'A' + (digit - 10);
        }

        // Transition to the next smallest value
        power = power / base;
    }

    // Null terminator
    out[position] = '\0';
}

//Method print_tables
void print_tables(uint32_t n) 
{
    char bin[33], oct[12], hex[9];

    // Original
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    // Left Shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

    // AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);
}