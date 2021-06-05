#ifndef ACTOR_H
#define ACTOR_H

#include "Vec3.h"
#include "inttypes.h"

extern uint32_t ActorManager_SearchByID(uint32_t id, uint32_t* result);
extern uint32_t f_op_actor_iter__Judge(uint32_t param_1, uint32_t param_2);
extern uint32_t ActorManager_CreateAppend(uint32_t parameters, Vec3f* pPos, int roomNo, Vec3s* pAngle, Vec3f* pScale, uint8_t subtype, uint32_t);
extern void Actor_Despawn(void* this);
extern uint32_t ActorManager_Create(int16_t procName, uint32_t parameters, Vec3f* pPos, int roomNo, Vec3s* pAngle, Vec3f* pScale, uint8_t subtype, void* param_8);
extern uint32_t ActorManager_CreateFast(uint16_t actorID, uint32_t parameters, Vec3f* pPos, int roomNo, Vec3s* pAngle, Vec3f* pScale, uint8_t subtype, void* pCallBack, void* pCallBackUserData);
extern uint32_t f_pc_manager__FastCreate(uint16_t actorID, void* pCallBack, void* pCallBackUserData, struct ActorManager_Params* params);
extern int f_pc_searcher__JudgeByID(uint32_t param_1, uint32_t param_2);
extern uint32_t f_pc_layer__CurrentLayer(void);
extern int32_t f_pc_manager__IsCreating(uint16_t actorID);

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

