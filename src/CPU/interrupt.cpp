/*
ソフトウェア割込みを除いた割込み処理のファイル
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"
#include "base_function.h"

void RESET(CPU_Emulator* cpu) {
    cpu->I = true;

    uint8_t l_PC = cpu->cpu_mem[0xFFFC];
    uint8_t h_PC = cpu->cpu_mem[0xFFFD];

    cpu->PC = (uint16_t)l_PC + ((uint16_t)h_PC << 8);
}

void NMI(CPU_Emulator* cpu) {
    cpu->B = false;
    
    Interrupt_Stuck(cpu);

    cpu->I = true;

    uint8_t l_PC = cpu->cpu_mem[0xFFFA];
    uint8_t h_PC = cpu->cpu_mem[0xFFFB];

    cpu->PC = (uint16_t)l_PC + ((uint16_t)h_PC << 8);
}

void IRQ(CPU_Emulator* cpu) {
    if (!(cpu->I)) {
        cpu->B = false;

        Interrupt_Stuck(cpu);

        cpu->I = true;

        uint8_t l_PC = cpu->cpu_mem[0xFFFE];
        uint8_t h_PC = cpu->cpu_mem[0xFFFF];

        cpu->PC = (uint16_t)l_PC + ((uint16_t)h_PC << 8);
    }
}

void InterruptFunction(CPU_Emulator* cpu, bool* NMIpin, bool* IRQpin) {
    if (!*NMIpin) {
        NMI(cpu);
        *NMIpin = true;
    }
    if (!*IRQpin) {
        IRQ(cpu);
        *IRQpin = true;
    }
}