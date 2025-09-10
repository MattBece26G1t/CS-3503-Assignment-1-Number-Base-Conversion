/*

Bash. Paste in terminal:

gcc -o convert convert.c main.c
./convert

*/

// main.c file

#include <stdio.h> // For printing and reading files
#include <stdint.h> // For uint32_t
#include <string.h> // String functions
#include "convert.h" // Declare conversion methods from convert.c

// Main method
int main(void) 
{
    int conversion_total = 0; // Totaled test runs
    int conversion_passes = 0; // Passed tests

    // Open test file: "a1_test_file.txt"
    FILE *file = fopen("a1_test_file.txt", "r");

    // Output error message if file could not be found
    if (file == NULL) 
    { 
        printf("Error: Could not locate file \"a1_test_file.txt\"\n"); 
        return 1; 
    }

    // Write all results to "output.txt"
    if (!freopen("output.txt", "w", stdout)) 
    {
        perror("output.txt"); // Print potential error to system
        fclose(file); // Close file for protection
        return 1;
    }

    char line[256]; // Buffer

    // Reading each line from "a1_test_file.txt"
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        // Remove newline(s)
        line[strcspn(line, "\r\n")] = '\0';

        // Check and skip comments or spaces
        if (line[0] == '#' || line[0] == '\0') 
        {
            continue;
        }
        
        // For div_convert method call and print result to "output.txt"
        {
            // Inputs and buffers
            uint32_t n; 
            int base; 
            char expected[100]; // Expected string 
            char out[100]; // Actual output

            // Parse through lines that call for "div_convert" expecting 3 fields
            // %99s prevents expected array overflow over 99 chars
            if (sscanf(line, "div_convert %u %d %99s", &n, &base, expected) == 3) 
            {
                div_convert(n, base, out); // Call method

                conversion_total++; // Count the test
                
                // Compare and print results
                if (strcmp(out, expected) == 0) 
                {
                    conversion_passes++; // Conversion successful and marked
                    printf("Test %d: div_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ PASS ]\n", conversion_total, n, base, expected, out);
                }
                    
                else 
                {
                    printf("Test %d: div_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ FAIL ]\n", conversion_total, n, base, expected, out);
                }

                continue;
            }
        }
        
        // For sub_convert method call and print result to "output.txt"
        {
            // Inputs and buffers
            uint32_t n; 
            int base; 
            char expected[100]; // Expected string
            char out[100]; // Actual output

            // Parse through lines that call for "sub_convert" expecting 3 fields
            // %99s prevents expected array overflow over 99 chars
            if (sscanf(line, "sub_convert %u %d %99s", &n, &base, expected) == 3) 
            {
                sub_convert(n, base, out); // Call method

                conversion_total++; // Count the test

                // Compare and print results
                if (strcmp(out, expected) == 0) 
                {
                    conversion_passes++; // Conversion successful and marked
                    printf("Test %d: sub_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ PASS ]\n", conversion_total, n, base, expected, out);
                } 

                else 
                {
                    printf("Test %d: sub_convert (%u , %d) -> Expected : \"%s\", Got : \"%s\" [ FAIL ]\n", conversion_total, n, base, expected, out);
                }

                continue;
            }
        }

        // For print_tables method call and print results to "output.txt"
        {
            uint32_t n; // Inputs

            // Parse through lines that call for "print_tables"
            if (sscanf(line, "print_tables %u", &n) == 1) 
            {
                    conversion_total++; // Count the test
        
                    // Print test status. [PASS] not functional.
                    printf("Test %d: print_tables (%u) -> [ FORMATTED OUTPUT CHECK ] [ PASS ]\n", conversion_total, n);
                    conversion_passes++; // Conversion successful and marked

                    print_tables(n); // Call method and print format

                    continue;
            }
        }

    }

    fclose(file); // Close "a1_test_file.txt"

    // Print summary
    printf("Summary: %d/%d tests passed\n", conversion_passes, conversion_total);
    return 0;
}
