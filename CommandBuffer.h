#ifndef COMMANDBUFFER_H
#define COMMANDBUFFER_H

#include "inttypes.h"
#include "Actor.h"
#include "Command.h"

#define OFFSETOF(TYPE, ELEMENT) ((uint32_t)&(((TYPE*)0)->ELEMENT))
#define COMMAND_MAX 64

typedef struct {
    /* 0x000 */ uint32_t count; // number of commands to be processed on the next CommandBuffer_Update
    /* 0x004 */ uint32_t pad;
    /* 0x008 */ Command commands[COMMAND_MAX]; // data for commands that will be processed on the next CommandBuffer_Update
    /* 0xA08 */ CommandReturn returns[COMMAND_MAX]; // return data from commands that were processed (MAKE SURE TO CLEAER THESE AFTER HANDLING THEM!)
} CommandBuffer; /* sizeof = 0x1008 */

extern CommandBuffer cmdBuffer;

extern void dCcS_Move(void* this); // use for caving draw
extern void* f_op_overlap_mng__IsPeek(void); // use for caving execute
extern int32_t memcpy(void* dest, void*  src, uint32_t length);

uint32_t CommandBuffer_Update(void*);


#endif

