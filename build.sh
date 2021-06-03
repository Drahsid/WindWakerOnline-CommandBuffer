rm *.o *.elf
powerpc-linux-gnu-gcc-10 -c CommandBuffer.c -g -Og -nostdlib -mbig-endian -mcpu=750 -std=gnu11 -G 0 -DUSE_DRAW_CODECAVE -o CommandBuffer.elf
powerpc-linux-gnu-ld -T CommandBuffer.ld -o CommandBuffer.o CommandBuffer.elf