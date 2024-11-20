#ifndef PASSWORD_UTILS_H
#define PASSWORD_UTILS_H

#include <stdlib.h>
#include <string.h>

void generate_numeric(char *buffer, size_t length);
void generate_alpha(char *buffer, size_t length);
void generate_mixed(char *buffer, size_t length);
void generate_secure(char *buffer, size_t length);

#endif // PASSWORD_UTILS_H
