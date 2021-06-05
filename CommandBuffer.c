#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include "inttypes.h"
#include "Command.h"
#include "CommandBuffer.h"

__attribute__((aligned(0x20))) uint32_t CommandBuffer_Update(void* that) {
    uint32_t index;
    uint32_t qndex;
    uint32_t layer;
    uint32_t request;
    uint32_t returnIsPeek;
    uint32_t temp;
    uint32_t actorPointer = 0;
    ActorManager_Params* actorParams = 0;
    Command* command = 0;
    CommandReturn* retCommand = 0;

    // Since we are codecaving this function call, we need to actually call it with its original arguments before doing our stuff
#ifdef USE_DRAW_CODECAVE
    dCcS_Move(that);
    {
#else
    returnIsPeek = f_op_overlap_mng__IsPeek();
    if (returnIsPeek) {
#endif

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
                            retCommand = &cmdBuffer.returns[qndex];
                            break;
                        }
                    }

                    // if free return slot, spawn actor and set the data to the resulting pointer
                    if (qndex != COMMAND_MAX) {
                        // use CreateAppend to get the game's unique id to detect when the actor is supposed to be spawned
                        // we are spawning at Link's location, in Link's room
                        actorParams = ActorManager_CreateAppend(0, (Vec3f*)0x803E440C, *((uint8_t*)0x803F6A78), 0, 0, 0, 0xFFFFFFFF);
                        temp = actorParams->uuid; // this also didn't work
                        layer = f_pc_layer__CurrentLayer();
                        request = f_pc_stdcreate_req__Request(layer, 0xB5, 0, 0, actorParams);

                        if (actorParams) {
                            retCommand->data[0] = temp; // store this, it might be useful for the future
                            retCommand->data[1] = command->returnUUID; // shovel return uuid into data so wwo doesn't think it is ready
                            retCommand->data[2] = 0; // use as a framecount
                            retCommand->data[3] = -1; // used for error and safety
                            retCommand->type = COMMAND_TYPE_PUPPET_SPAWNING; //command->type;
                            retCommand->returnUUID = 0;
                        }
                        else {
                            // something went wrong, we won't be waiting for this actor
                            retCommand->data[0] = -1;
                            retCommand->data[1] = 0xDEADDEAD;
                            retCommand->data[2] = temp;
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
            retCommand = &cmdBuffer.returns[index];

            switch (retCommand->type) {
                // if actor is spawning
                case COMMAND_TYPE_PUPPET_SPAWNING:
                    // search for entity using uuid

                    // reusing request, effectively is a boolean for the isCreating call
                    request = f_pc_manager__IsCreating(retCommand->data[0]);
                    retCommand->data[2]++;
                    if (retCommand->data[3] == -1) {
                        if (request) retCommand->data[3] = 0;
                    }
                    else {
                        // Still waiting???
                        if (request) {
                            retCommand->data[3] = 0x00BADBAD;
                        }

                        // assume we can just get the actor pointer at this point
                        actorPointer = f_op_actor_iter__Judge(f_pc_searcher__JudgeByID, retCommand->data[0]);

                        if (actorPointer) {
                            retCommand->data[2] = retCommand->data[0]; // entity uuid
                            retCommand->returnUUID = retCommand->data[1];
                            retCommand->type = COMMAND_TYPE_PUPPET_SPAWN;
                            retCommand->data[0] = actorPointer;
                            retCommand->data[1] = 0xBEEFBEEF;
                        }
                        else {
                            retCommand->data[3] = 2;
                        }
                    }

                    break;
            }
        }
    }

    return returnIsPeek;
}

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

