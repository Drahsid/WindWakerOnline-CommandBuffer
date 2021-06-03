#ifndef ACTOR_H
#define ACTOR_H

#include "Vec3.h"
#include "inttypes.h"

extern uint32_t ActorManager_SearchByID(uint32_t id, uint32_t* result);
extern struct ActorManager_Params* ActorManager_CreateAppend(uint32_t parameters, Vec3f* pPos, int roomNo, Vec3s* pAngle, Vec3f* pScale, uint8_t subtype, uint32_t);
extern void Actor_Despawn(void* this);
extern uint32_t ActorManager_Create(int16_t procName, uint32_t parameters, Vec3f* pPos, int roomNo, Vec3s* pAngle, Vec3f* pScale, uint8_t subtype, void* param_8);
extern uint32_t ActorManager_CreateFast(uint16_t actorID, uint32_t parameters, Vec3f* pPos, int roomNo, Vec3s* pAngle, Vec3f* pScale, uint8_t subtype, void* pCallBack, void* pCallBackUserData);
extern uint32_t f_pc_layer__CurrentLayer(void);
extern uint32_t f_pc_stdcreate_req__Request(uint32_t param_1, int16_t param_2,uint32_t param_3, uint32_t param_4, uint32_t param_5);

typedef enum GbaNames {
    Bokoblin = 1,
    Stalfos = 4,
    Magtail = 5,
    YellowChuChu = 10,
    DarkChuChu = 16,
    RedChuChu = 21,
    GreenChuChu = 22,
    Rat = 24,
    BlueChuChu = 30,
    PushableBlock = 61
} GbaNames;

typedef struct {
    /* 0x00 */ long parameters;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3s rot;
    /* 0x16 */ uint16_t enemyNo;
    /* 0x18 */ uint8_t scaleX;
    /* 0x19 */ uint8_t scaleY;
    /* 0x1A */ uint8_t scaleZ;
    /* 0x1B */ enum GbaNames gbaName;
    /* 0x1C */ uint32_t parentPcId;
    /* 0x20 */ uint8_t subtype;
    /* 0x21 */ uint8_t roomNo;
    /* 0x22 */ uint8_t unk_0x22;
    /* 0x23 */ uint8_t unk_0x23;
    /* 0x24 */ uint32_t unk_0x24;
    /* 0x28 */ uint32_t unk_0x28;
    /* 0x2C */ uint32_t unk_0x2C;
    /* 0x30 */ uint32_t unk_0x30;
    /* 0x34 */ uint32_t unk_0x34;
    /* 0x38 */ uint32_t unk_0x38;
    /* 0x3C */ uint32_t uuid;
    /* 0x40 */ uint32_t unk_0x40;
    /* 0x44 */ uint32_t unk_0x44;
    /* 0x48 */ uint32_t callbackFn0;
    /* 0x4C */ uint32_t callbackFn1;
} ActorManager_Params;

typedef struct {
    /* 0x00 */ Vec3f position;
    /* 0x0C */ Vec3s rotation;
    /* 0x12 */ uint16_t pad;
} ActorParams; /* sizeof = 0x14 */

typedef union {
    Vec3s rot;
    uint64_t dirty;
    struct {
        uint32_t dirtyl;
        uint32_t dirtyh;
    };
} ActorAux; /* sizeof = 0x08 */

typedef struct {
    /* 0x00 */ void* actor;
} ActorDespawnParams; /* sizeof = 0x04 */

#endif

