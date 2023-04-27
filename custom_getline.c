#include "main.h"
/**
 * custom_getline - reads input from user
 * Return: On success, the function returns a pointer to the input string.
 * On failure, it returns NULL.
 */
#define BUFSIZE 1024

char *custom_getline(void)
{
    static char buffer[BUFSIZE];
    static int buffer_pos = 0;
    int pos = 0;
    char c;
    char *line = NULL;

    while (1) {
        if (buffer_pos == 0) {
            int nread = read(STDIN_FILENO, buffer, BUFSIZE);
            if (nread < 1) {
                return NULL;
            }
        }

        c = buffer[buffer_pos++];
        if (c == '\n' || buffer_pos == BUFSIZE) {
            buffer[buffer_pos - 1] = '\0';
            buffer_pos = 0;
            break;
        }

        if (pos == 0) {
            line = malloc(BUFSIZE);
            if (!line) {
                return NULL;
            }
        }

        line[pos++] = c;
        if (pos == BUFSIZE) {
            char *new_line = realloc(line, pos + BUFSIZE);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
        }
    }

    return line;
}

