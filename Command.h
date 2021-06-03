#ifndef COMMAND_H
#define COMMAND_H

#include "inttypes.h"
#include "Actor.h"

enum {
    COMMAND_TYPE_NONE,
    COMMAND_TYPE_PUPPET_SPAWN,
    COMMAND_TYPE_PUPPET_DESPAWN,
    COMMAND_TYPE_COUNT
};

typedef struct {
    /* 0x00 */ ActorParams params;
    /* 0x14 */ ActorAux aux;
} PuppetSpawnData; /* sizeof = 0x1C */

typedef struct {
    /* 0x00 */ ActorDespawnParams params;
} PuppetDespawnData; /* sizeof = 0x04 */

typedef union {
    PuppetSpawnData puppetSpawn; // this can be entirely ignored if you do not want to instanciate a puppet with any default data
    PuppetDespawnData puppetDespawn; // you must provide the pointer to despawn!
} CommandData; /* sizeof = 0x1C (unions are the size of the largest member) */

typedef struct {
    /* 0x00 */ uint32_t type; // type of command
    /* 0x04 */ uint32_t returnUUID; // uuid of command, nonzero if applicable
    /* 0x08 */ CommandData data; // data relevant to command
} Command; /* sizeof = 0x28 */

typedef struct {
    /* 0x00 */ uint32_t type; // original type of command
    /* 0x04 */ uint32_t returnUUID; // uuid of command, nonzero if applicable
    /* 0x08 */ uint32_t data[4]; // data returned by command
} CommandReturn; /* sizeof = 0x18 */

#endif

