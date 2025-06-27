/*
やや特殊な受け渡しをする関数が記述されているファイル
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"

uint8_t* fetch(CPU_Emulator* cpu, uint16_t index) {
    uint8_t* addr;
    addr = &cpu->cpu_mem[index];
    return addr;
}

void push(CPU_Emulator* cpu, uint8_t data) {
    uint16_t index = cpu->SP;
    cpu->cpu_mem[index] = data;
    cpu->SP -= 1;
}

uint8_t pop(CPU_Emulator* cpu) {
    cpu->SP += 1;
    uint16_t index = cpu->SP;
    return *fetch(cpu, index);
}

void Interrupt_Stuck(CPU_Emulator* cpu) {
    uint16_t h_16 = cpu->PC >> 8;
    uint16_t l_16 = cpu->PC % 256;
    uint8_t h_8 = (uint8_t)h_16;
    uint8_t l_8 = (uint8_t)l_16;
    push(cpu, h_8);
    push(cpu, l_8);
    uint8_t status;
    status = (cpu->N * 128) + (cpu->V * 64) + 32 + (cpu->B * 16) + (cpu->D * 8) + (cpu->I * 4) + (cpu->Z * 2) + cpu->C;
    push(cpu, status);
}