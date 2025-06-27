/*
アドレッシング処理を行うファイル
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"
#include "base_function.h"

uint8_t* Immidiate(CPU_Emulator* cpu) {
    uint8_t* addr;
    addr = &cpu->cpu_mem[cpu->PC];
    return addr;
}

uint8_t* Absolute(CPU_Emulator* cpu) {
    uint8_t l = cpu->cpu_mem[cpu->PC];
    cpu->PC += 1;
    uint8_t h = cpu->cpu_mem[cpu->PC];
    uint16_t addr = static_cast<uint16_t>(l) | (static_cast<uint16_t>(h) << 8);
    return &cpu->cpu_mem[addr];
}

uint8_t* ZeroPage(CPU_Emulator* cpu) {
    uint8_t l = cpu->cpu_mem[cpu->PC];
    uint8_t* addr;
    addr = &cpu->cpu_mem[(uint16_t)l];
    return addr;
}

uint8_t* IndexZeroPage(CPU_Emulator* cpu, uint8_t add) {
    uint8_t l = cpu->cpu_mem[cpu->PC];
    l += add;
    uint8_t* addr;
    addr = &cpu->cpu_mem[(uint16_t)l];
    return addr;
}

uint8_t* IndexAbsolute(CPU_Emulator* cpu, uint8_t add) {
    uint8_t l = cpu->cpu_mem[cpu->PC];
    cpu->PC += 1;
    uint8_t h = cpu->cpu_mem[cpu->PC];
    uint16_t m = (uint16_t)l + ((uint16_t)h << 8);
    uint8_t* addr;
    addr = &cpu->cpu_mem[(uint16_t)(m + (uint16_t)add)];
    return addr;
}

uint8_t* Relative(CPU_Emulator* cpu) {
    int8_t offset = cpu->cpu_mem[cpu->PC];
    uint16_t m = cpu->PC + 1 + offset;
    uint8_t* addr;
    addr = &cpu->cpu_mem[m];
    return addr;
}

uint8_t* XIndirect(CPU_Emulator* cpu) {
    uint8_t indir_l = cpu->cpu_mem[cpu->PC];
    indir_l += cpu->X;
    uint8_t l = cpu->cpu_mem[(uint16_t)indir_l];
    indir_l += 1;
    uint8_t h = cpu->cpu_mem[(uint16_t)indir_l];
    uint8_t* addr;
    addr = &cpu->cpu_mem[(uint16_t)((uint16_t)l + ((uint16_t)h << 8))];
    return addr;
}

uint8_t* YIndirect(CPU_Emulator* cpu) {
    uint8_t indir_l = cpu->cpu_mem[cpu->PC];
    uint8_t l = cpu->cpu_mem[(uint16_t)indir_l];
    indir_l += 1;
    uint8_t h = cpu->cpu_mem[(uint16_t)indir_l];
    uint16_t m = (uint16_t)l + ((uint16_t)h << 8);
    uint8_t* addr;
    addr = &cpu->cpu_mem[(uint16_t)(m + (uint16_t)cpu->Y)];
    return addr;
}

uint8_t* AbsoluteIndirect(CPU_Emulator* cpu) {
    uint8_t indir_l = cpu->cpu_mem[cpu->PC];
    cpu->PC += 1;
    uint8_t indir_h = cpu->cpu_mem[cpu->PC];
    uint16_t indir = (uint16_t)indir_l + ((uint16_t)indir_h << 8);
    uint8_t l = cpu->cpu_mem[indir];
    indir_l += 1;
    indir = (uint16_t)indir_l + ((uint16_t)indir_h << 8);
    uint8_t h = cpu->cpu_mem[indir];
    uint8_t* addr;
    addr = &cpu->cpu_mem[(uint16_t)((uint16_t)l + ((uint16_t)h << 8))];
    return addr;
}