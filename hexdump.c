#include "hexdump.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


void hexdump(char const *buffer, size_t length)
{
    // Canonical hex+ASCII hexdump(1) style.
    size_t address = 0;
    size_t width = 16;
    size_t group = 8;
    struct hexdump *h = hexdump_create(address, width, group);
    hexdump_append(h, buffer, length);
    hexdump_destroy(h);
}

struct hexdump {
    size_t address;
    size_t width;
    size_t group;
    size_t column;
    char *output;
};

static void emit_separator(struct hexdump *self)
{
    if (self->group && self->column && (self->column % self->group) == 0) {
        putchar(' ');
    }
}

static void emit_octet(struct hexdump *self, char c)
{
    self->output[self->column] = isprint(c) ? c : '.';
    emit_separator(self);
    printf(" %02x", c & 0xFF);
}

static void emit_blank(struct hexdump *self)
{
    self->output[self->column] = 0;
    emit_separator(self);
    printf("   ");
}

static void emit_line(struct hexdump *self)
{
    self->output[self->width] = 0;
    printf("  |%s|\n", self->output);
}

struct hexdump *hexdump_create(size_t address, size_t width, size_t group)
{
    struct hexdump *self = (struct hexdump *)malloc(sizeof(struct hexdump));
    self->address = address;
    self->width = width;
    self->group = group;
    self->column = 0;
    self->output = (char *)malloc(width + 1);
    return self;
}

void hexdump_append(struct hexdump *self, char const *buffer, size_t length)
{
    while (length-- > 0) {
        if (self->column == 0) {
            printf("%08lx ", self->address);
        }

        emit_octet(self, *buffer++);
        self->address++;
        self->column++;

        // End of line.
        if (self->column == self->width) {
            emit_line(self);
            self->column = 0;
        }
    }
}

void hexdump_destroy(struct hexdump *self)
{
    if (self->address) {
        if (self->column) {
            // End of data.
            while (self->column < self->width) {
                emit_blank(self);
                self->column++;
            }

            emit_line(self);
            self->column = 0;
        }

        printf("%08lx\n", self->address);
    }

    free(self->output);
    self->output = NULL;
    free(self);
}
