#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>


/// Hex dump.
/// @discussion Render @c buffer to stdout in canonical hex+ASCII hexdump(1) style.
void hexdump(char const *buffer, size_t length);

struct hexdump;

/// Constructor.
/// @discussion Creates an object used to render hex+ASCII data.
/// @param address Start address.
/// @param width Number of octets to output per line.
/// @param group Visually group octets.
/// @see hexdump_destroy
/// @return pointer To opaque instance
struct hexdump *hexdump_create(size_t address, size_t width, size_t group);

/// Append input data.
void hexdump_append(struct hexdump *, char const *buffer, size_t length);

/// Destructor.
void hexdump_destroy(struct hexdump *);

#ifdef __cplusplus
}
#endif
