#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// The function checks if the character 'ch' belongs to the specified number system 'base'
int isSymbInBase(char ch, int base) {
    if (base <= 10) {
        // For bases from 2 to 10, we check whether the character is a digit within a base
        return ch >= '0' && ch < '0' + base;
    } else if (base == 16) {
        // For hexadecimal system we check digits and letters A-F
        return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F');
    } else {
        // Basis outside of acceptable values
        return 0;
    }
}

// The function checks whether the string 'numStr' is a number in the specified number system 'base'
int isNumInBase(const char* numStr, int base) {
    int i = 0;

    // Check every character in the string
    while (numStr[i] != '\0') {
        // If at least one character does not belong to the number system, return 0 (false)
        if (!isSymbInBase(numStr[i], base)) {
            return 0;
        }
        i++;
    }

    return 1; // If all characters are valid, return 1 (true)
}

// The function converts a string from a binary number system to a decimal number
int from_bi(char ch[]) {
    char *endptr;
    // strtol converts the string 'ch' to an integer in a system with base 2
    int dec = strtol(ch, &endptr, 2);
    return dec;
}

// The function converts a string from the octal number system to a decimal number
int from_oct(char ch[]) {
    char *endptr;
    // strtol converts the string 'ch' to an integer in a system with base 8
    int dec = strtol(ch, &endptr, 8);
    return dec;
}

// The function converts a string from hexadecimal number system to a decimal number
int from_hex(char ch[]) {
    char *endptr;
    // strtol converts the string 'ch' to an integer in a system with base 16
    int dec = strtol(ch, &endptr, 16);
    return dec;
}

int main() {
    FILE *file;
    char n[256], S[256], A[256];  //Variables for storing strings from the file

    // Open the file for reading
    file = fopen("input.txt", "r");

    // Read lines from the file
    fgets(n, sizeof(n), file);
    fgets(S, sizeof(S), file);
    fgets(A, sizeof(A), file);

    //Remove the newline character from the end of lines 'n' and 'S'
    n[strlen(n) - 1] = '\0';
    S[strlen(S) - 1] = '\0';

    // Close the file after reading
    fclose(file);

    int N;
    N = atoi(n);  //Convert the string 'n' to an integer number

    int arr_a[N];  //Array for storing number system bases
    char *arr_s[N];  // Array for storing strings of numbers

    int error_flag = 0;  // Error flag for tracking incorrect data

    int i = 0;
    int SUM = 0;  // Variable for storing the sum

    // Split the string 'A' into separate substrings (number system bases)
    char *token1 = strtok(A, " ");

    // Convert each substring to a number and write it to the array 'arr_a'
    while (token1 != NULL) {
        arr_a[i] = atoi(token1);  //Convert the string to a number and store it in an array
        i++;
        token1 = strtok(NULL, " ");  // Move on to the next substring
    }

    i = 0;
    // Split the string 'S' into separate numbers (as strings)
    char *token2 = strtok(S, " ");

    // Save each substring to the 'arr_s' array
    while (token2 != NULL) {
        arr_s[i] = token2;
        i++;
        token2 = strtok(NULL, " ");
    }

    // Check the correctness of the number of elements N
    if (1 <= N && N <= 40) {
        // Go through each number and its corresponding number system
        for (int i = 0; i < N; i++) {
            // Check if the number belongs to its number system
            if (isNumInBase(arr_s[i], arr_a[i])) {
                // If the base of the number system is 2
                if (arr_a[i] == 2) {
                    if (i % 2 == 1) {
                        SUM += (from_bi(arr_s[i]) + 10);  // If the index is odd, add 10
                    } else {
                        SUM += (from_bi(arr_s[i]) - 10);  // If the index is even, subtract 10
                    }
                // If the base of the number system is 8
                } else if (arr_a[i] == 8) {
                    if (i % 2 == 1) {
                        SUM += (from_oct(arr_s[i]) + 10);  // If the index is odd, add 10
                    } else {
                        SUM += (from_oct(arr_s[i]) - 10);  // If the index is even, subtract 10
                    }
                    // If the base of the number system is 16
                } else if (arr_a[i] == 16) {
                    if (i % 2 == 1) {
                        SUM += (from_hex(arr_s[i]) + 10);  // If the index is odd, add 10
                    } else {
                        SUM += (from_hex(arr_s[i]) - 10);  // If the index is even, subtract 10
                    }
                    // If the base of the number system is 10
                } else if (arr_a[i] == 10) {
                    if (i % 2 == 1) {
                        SUM += (atoi(arr_s[i]) + 10);  // If the index is odd, add 10
                    } else {
                        SUM += (atoi(arr_s[i]) - 10);  // If the index is even, subtract 10
                    }
                }
            } else {
                // If the number is incorrect, set the error flag and exit the loop
                error_flag += 1;
                break;
            }
        }
    } else {
        // If the number of elements exceeds the permissible limits, set the error flag
        error_flag += 1;
    }

    // Open the file to record the result
    FILE *fileout = fopen("output.txt", "w");

    // If there were no errors, write the sum to the file
    if (error_flag == 0) {
        fprintf(fileout, "%d\n", SUM);
    } else {
        // If there are errors, write a message about incorrect data
        fprintf(fileout, "Invalid inputs\n");
    }

    // Closing the file
    fclose(fileout);

    return 0;
}