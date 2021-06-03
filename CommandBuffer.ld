OUTPUT_FORMAT ("elf32-powerpc")
OUTPUT_ARCH (powerpc)
EXTERN (CommandBuffer_Update)

SECTIONS
{
    . = 0x80000000;
    ActorManager_SearchByID = 0x800241C0;
    ActorManager_CreateAppend = 0x80024320;
    Actor_Despawn = 0x80024478;
    ActorManager_Create = 0x8002451C;
    ActorManager_CreateFast = 0x80024614;
    f_pc_layer__CurrentLayer = 0x8003D96C;
    f_pc_stdcreate_req__Request = 0x8004086C;
    dCcS_Move = 0x800AE81C;

    . = 0x81800000;
    CommandBuffer_Update = 0x81800000;

    cmdBuffer = 0x81801000;
}
