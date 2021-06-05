#ifndef REQUEST_H
#define REQUEST_H

// TODO: Very unorganized, slapped together

#include "inttypes.h"

extern struct CreateRequest* f_pc_stdcreate_req__Request(uint32_t param_1, int16_t param_2,uint32_t param_3, uint32_t param_4, uint32_t param_5);

typedef struct {
    /* 0x00 */ struct NodeClass* mpPrevNode;
    /* 0x04 */ void* mpData;
    /* 0x08 */ struct NodeClass* mpNextNode;
} NodeClass; /* sizeof = 0x0C */

typedef struct {
    /* 0x00 */ NodeClass parent;
    /* 0x0C */ struct CreateRequest* mpTagData;
    /* 0x10 */ uint8_t mbAdded;
    /* 0x11 */ uint8_t unk_0x11;
    /* 0x12 */ uint8_t unk_0x12;
    /* 0x13 */ uint8_t unk_0x13;
} CreateTagClass; /* sizeof = 0x14 */

typedef struct {
    /* 0x00 */ CreateTagClass parent;
    /* 0x14 */ void* mpFunc;
    /* 0x18 */ void* mpUserData;
} ProcessMethodTagClass; /* sizeof = 0x1C */

typedef struct {
    /* 0x00 */ CreateTagClass parent;
} CreateTag; /* sizeof = 0x14 */

typedef struct {
    /* 0x00 */ CreateTag parent;
    /* 0x14 */ uint8_t mbIsCreating;
    /* 0x15 */ uint8_t unk_0x15;
    /* 0x16 */ uint8_t unk_0x16;
    /* 0x17 */ uint8_t unk_0x17;
    /* 0x18 */ ProcessMethodTagClass mMtdTg;
    /* 0x34 */ struct CreateRequestMethodClass* mpCtRqMtd;
    /* 0x38 */ void* unk_0x38;
    /* 0x3C */ int32_t uuid;
    /* 0x40 */ struct BaseProcessClass* mpRes;
    /* 0x44 */ struct LayerClass* mpLayer;
} CreateRequest; /* sizeof = 0x48 */

#endif

