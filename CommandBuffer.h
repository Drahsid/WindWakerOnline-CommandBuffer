#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include "inttypes.h"
#include "Actor.h"
#include "Command.h"

#define COMMAND_MAX 64

typedef struct {
    /* 0x000 */ uint32_t count; // number of commands to be processed on the next CommandBuffer_Update
    /* 0x004 */ uint32_t pad;
    /* 0x008 */ Command commands[COMMAND_MAX]; // data for commands that will be processed on the next CommandBuffer_Update
    /* 0xA08 */ CommandReturn returns[COMMAND_MAX]; // return data from commands that were processed (MAKE SURE TO CLEAER THESE AFTER HANDLING THEM!)
} CommandBuffer; /* sizeof = 0x1008 */

extern CommandBuffer cmdBuffer;

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif