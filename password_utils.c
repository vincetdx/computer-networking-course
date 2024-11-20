#include "password_utils.h" 
#include <time.h>           
#include <ctype.h>          

/*
 * Generates a numeric password consisting only of digits (0-9).
 * Parameters:
 * - buffer: Pointer to the character array where the generated password is stored.
 * - length: Desired length of the password.
 */
void generate_numeric(char *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        buffer[i] = '0' + rand() % 10; // Generate a random digit and assign it to the buffer
    }
    buffer[length] = '\0'; // Null-terminate the string
}

/*
 * Generates an alphabetic password consisting only of lowercase letters (a-z).
 * Parameters:
 * - buffer: Pointer to the character array where the generated password is stored.
 * - length: Desired length of the password.
 */
void generate_alpha(char *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        buffer[i] = 'a' + rand() % 26; // Generate a random lowercase letter
    }
    buffer[length] = '\0'; // Null-terminate the string
}

/*
 * Generates a mixed password consisting of lowercase letters (a-z) and digits (0-9).
 * Parameters:
 * - buffer: Pointer to the character array where the generated password is stored.
 * - length: Desired length of the password.
 */
void generate_mixed(char *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (rand() % 2) { // Randomly decide between a letter and a digit
            buffer[i] = 'a' + rand() % 26; // Generate a random lowercase letter
        } else {
            buffer[i] = '0' + rand() % 10; // Generate a random digit
        }
    }
    buffer[length] = '\0'; // Null-terminate the string
}

/*
 * Generates a secure password consisting of uppercase letters, lowercase letters,
 * digits, and special characters.
 * Parameters:
 * - buffer: Pointer to the character array where the generated password is stored.
 * - length: Desired length of the password.
 */
void generate_secure(char *buffer, size_t length) {
    // Character set for secure passwords
    const char charset[] = 
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    size_t charset_len = strlen(charset); // Length of the character set

    for (size_t i = 0; i < length; i++) {
        buffer[i] = charset[rand() % charset_len]; // Randomly select a character from the set
    }
    buffer[length] = '\0'; // Null-terminate the string
}
