#include "hexdump.h"

#include <string.h>


int main(void)
{
    char const test[] = "The quick brown fox jumped over the lazy dog.";
    struct hexdump *h;

    hexdump(test, 0);
    hexdump(test, 1);
    hexdump(test, 8);
    hexdump(test, 9);
    hexdump(test, 16);
    hexdump(test, 17);
    hexdump(test, strlen(test));

    h = hexdump_create(32, 16, 0);
    hexdump_append(h, test, strlen(test));
    hexdump_destroy(h);
    h = NULL;

    h = hexdump_create(33, 4, 0);
    hexdump_append(h, test, strlen(test));
    hexdump_destroy(h);
    h = NULL;
}
