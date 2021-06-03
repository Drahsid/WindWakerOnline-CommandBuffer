#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include "inttypes.h"
#include "Command.h"
#include "CommandBuffer.h"

#define OFFSETOF(TYPE, ELEMENT) ((uint32_t)&(((TYPE*)0)->ELEMENT))

extern void dCcS_Move(void* this);
void CommandBuffer_Update(void*);

__attribute__((aligned(0x20))) void CommandBuffer_Update(void* that) {
    uint32_t index;
    uint32_t qndex;
    uint32_t layer;
    uint32_t request;
    uint32_t actorPointer = 0;
    ActorManager_Params* actorParams = 0;
    Command* command;
    CommandReturn* rvalue;

    // Since we are codecaving this function call, we need to actually call it with its original arguments before doing our stuff
    dCcS_Move(that);

    // iterate through the current active commands on the command buffer
    for (index = 0; index < cmdBuffer.count; index++) {
        // shortcut to current command
        command = &cmdBuffer.commands[index];

        // process this command based on its type
        switch(command->type) {
            // if the command is empty, assume there is nothing to do
            case COMMAND_TYPE_NONE:
                break;

            // if the command is puppet spawn
            case COMMAND_TYPE_PUPPET_SPAWN:
                // check for free return slots (we need to return the pointer to the puppet, so it is important that we can actually do so)
                for (qndex = 0; qndex < COMMAND_MAX; qndex++) {
                    // if the uuid in this slot is 0
                    if (cmdBuffer.returns[qndex].returnUUID == 0) {
                        // we will use this slot
                        break;
                    }
                }

                // if free return slot, spawn actor and set the data to the resulting pointer
                if (qndex != COMMAND_MAX) {
                    /*
                        This way sucks, we're doing it manually
                        // set the return pointer to the result of Actor_Spawn
                        //cmdBuffer.returns[qndex].data[0] = Actor_Spawn(0xB5, 0, (Vec3f*)0x803E440C, *((uint8_t*)0x803F6A78), 0, 0, 0, 0);
                    */

                    actorParams = ActorManager_CreateAppend(0, (Vec3f*)0x803E440C, *((uint8_t*)0x803F6A78), 0, 0, 0, 0xFFFFFFFF);
                    layer = f_pc_layer__CurrentLayer();
                    request = f_pc_stdcreate_req__Request(layer, 0xB5, 0, 0, actorParams);

                    // prepare to wait for actor spawn
                    if (actorParams) {
                        cmdBuffer.returns[qndex].data[0] = actorParams->uuid; // store this, it might be useful for the future
                        cmdBuffer.returns[qndex].data[1] = command->returnUUID; // shovel return uuid into data so wwo doesn't think it is ready
                        cmdBuffer.returns[qndex].data[2] = 0; // use as a framecount
                        cmdBuffer.returns[qndex].type = COMMAND_TYPE_PUPPET_SPAWNING; //command->type;
                        cmdBuffer.returns[qndex].returnUUID = 0;
                    }
                    else {
                        // something went wrong, we won't be waiting for this actor
                        cmdBuffer.returns[qndex].data[0] = -1;
                        cmdBuffer.returns[qndex].data[1] = 0xDEADDEAD;
                        cmdBuffer.returns[qndex].data[2] = actorParams->uuid;
                    }
                }

                break;

            // if the command is puppet despawn
            case COMMAND_TYPE_PUPPET_DESPAWN:
                // despawn the actor given the command data
                Actor_Despawn(command->data.puppetDespawn.params.actor);
                break;
        }

        // clear the current command so that it doesn't get reprocessed
        command->type = COMMAND_TYPE_NONE;
    }

    // we iterated through all of the commands, assume there are no more commands to process
    cmdBuffer.count = 0;

    for (index = 0; index < COMMAND_MAX; index++) {
        rvalue = &cmdBuffer.returns[index];

        switch (rvalue->type) {
            // if actor is spawning
            case COMMAND_TYPE_PUPPET_SPAWNING:
                // search for entity using uuid
                if (ActorManager_SearchByID(rvalue->data[0], &actorPointer)) {
                    if (actorPointer) {
                        rvalue->data[2] = rvalue->data[0]; // entity uuid
                        rvalue->returnUUID = rvalue->data[1];
                        rvalue->type = COMMAND_TYPE_PUPPET_SPAWN;
                        rvalue->data[0] = actorPointer;
                        rvalue->data[1] = 0xBEEFBEEF;
                    }
                }
                else {
                    rvalue->data[2]++; // Another frame without the actor
                }
                break;
        }
    }

    return;
}

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif