/*
全命令（アドレッシング分け済み）を記述しているファイル
アドレッシングに関してはaddressing.cpp
アドレッシングを必要とする命令に関してはaddressing_operation.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "addressing_operation.h"
#include "addressing.h"
#include "nes_manager.h"
#include "operation_set.h"
#include "base_function.h"
#include "bus.h"

operation_func_t* operations[256];

unsigned int Imm_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    ADC(nes, m);
    cpu->PC += 1;

    return 2;
}

unsigned int ZePa_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    ADC(nes, m);
    cpu->PC += 1;

    return 3;
}

unsigned int X_ZePa_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    ADC(nes, m);
    cpu->PC += 1;

    return 4;
}

unsigned int Abs_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    ADC(nes, m);
    cpu->PC += 1;

    return 4;
}

unsigned int X_Abs_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    ADC(nes, m);
    cpu->PC += 1;

    return 4;
}

unsigned int Y_Abs_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    ADC(nes, m);
    cpu->PC += 1;

    return 4;
}

unsigned int X_Indir_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    ADC(nes, m);
    cpu->PC += 1;

    return 6;
}

unsigned int Y_Indir_ADC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    ADC(nes, m);
    cpu->PC += 1;

    return 5;
}

unsigned int Imm_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    SBC(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    SBC(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    SBC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    SBC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    SBC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    SBC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    SBC(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Y_Indir_SBC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    SBC(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Imm_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    AND(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    AND(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    AND(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    AND(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    AND(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    AND(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    AND(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Y_Indir_AND(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    AND(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Imm_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    ORA(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    ORA(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    ORA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    ORA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    ORA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    ORA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    ORA(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Y_Indir_ORA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    ORA(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Imm_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    EOR(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    EOR(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    EOR(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    EOR(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    EOR(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    EOR(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    EOR(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Y_Indir_EOR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    EOR(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Accum_ASL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    ASL(nes, &(cpu->A));
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_ASL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    ASL(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int X_ZePa_ASL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    ASL(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Abs_ASL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    ASL(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int X_Abs_ASL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    ASL(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Accum_LSR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    LSR(nes, &(cpu->A));
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_LSR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    LSR(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int X_ZePa_LSR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    LSR(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Abs_LSR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    LSR(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int X_Abs_LSR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    LSR(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Accum_ROL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    ROL(nes, &(cpu->A));
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_ROL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    ROL(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int X_ZePa_ROL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    ROL(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Abs_ROL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    ROL(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int X_Abs_ROL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    ROL(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Accum_ROR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    ROR(nes, &(cpu->A));
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_ROR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    ROR(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int X_ZePa_ROR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    ROR(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Abs_ROR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    ROR(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int X_Abs_ROR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    ROR(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int BCC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (cpu->C) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int BCS(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (!(cpu->C)) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int BEQ(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (!(cpu->Z)) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int BNE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (cpu->Z) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int BVC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (cpu->V) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int BVS(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (!(cpu->V)) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int BPL(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (cpu->N) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int BMI(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    if (!(cpu->N)) {
        cpu->PC += 2;
        return 3;
    }
    else {
        cpu->PC += 1;
        uint8_t* m = Relative(cpu);
        cpu->PC = (uint16_t)(m - cpu->cpu_mem);
        return 2;
    }
}

unsigned int ZePa_BIT(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    BIT(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int Abs_BIT(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    BIT(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_JMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    JMP(nes, m);
    return 3;
}

unsigned int Indir_JMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = AbsoluteIndirect(cpu);
    JMP(nes, m);
    return 5;
}

unsigned int JSR(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    uint16_t h_16 = cpu->PC >> 8;
    uint16_t l_16 = cpu->PC % 256;
    uint8_t h_8 = (uint8_t)h_16;
    uint8_t l_8 = (uint8_t)l_16;
    push(cpu, h_8);
    push(cpu, l_8);
    cpu->PC = (uint16_t)(m - cpu->cpu_mem);
    return 6;
}

unsigned int RTS(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t l_8 = pop(cpu);
    uint8_t h_8 = pop(cpu);
    uint16_t addr = (uint16_t)h_8 << 8;
    addr += (uint16_t)l_8;
    cpu->PC = addr;
    cpu->PC += 1;
    return 6;
}

unsigned int BRK(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 2;
    cpu->B = true;
    Interrupt_Stuck(cpu);
    cpu->I = true;
    uint8_t l_8 = *fetch(cpu, 0xFFFE);
    uint8_t h_8 = *fetch(cpu, 0xFFFF);
    cpu->PC = (uint16_t)l_8;
    cpu->PC += (uint16_t)h_8 << 8;
    return 7;
}

unsigned int RTI(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t status = pop(cpu);
    if (status % 2 == 1) cpu->C = true;
    else cpu->C = false;
    status /= 2;
    if (status % 2 == 1) cpu->Z = true;
    else cpu->Z = false;
    status /= 2;
    if (status % 2 == 1) cpu->I = true;
    else cpu->I = false;
    status /= 2;
    if (status % 2 == 1) cpu->D = true;
    else cpu->D = false;
    status /= 2;
    if (status % 2 == 1) cpu->B = true;
    else cpu->B = false;
    status /= 2;
    status /= 2;
    if (status % 2 == 1) cpu->V = true;
    else cpu->V = false;
    status /= 2;
    if (status % 2 == 1) cpu->N = true;
    else cpu->N = false;

    uint8_t l_8 = pop(cpu);
    uint8_t h_8 = pop(cpu);
    uint16_t addr = (uint16_t)h_8 << 8;
    addr += (uint16_t)l_8;
    cpu->PC = addr;
    return 6;
}

unsigned int Imm_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    CMP(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    CMP(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    CMP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    CMP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    CMP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    CMP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    CMP(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Y_Indir_CMP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    CMP(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Imm_CPX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    CPX(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_CPX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    CPX(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int Abs_CPX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    CPX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Imm_CPY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    CPY(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_CPY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    CPY(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int Abs_CPY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    CPY(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int ZePa_INC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    INC(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int X_ZePa_INC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    INC(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Abs_INC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    INC(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int X_Abs_INC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    INC(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int ZePa_DEC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    DEC(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int X_ZePa_DEC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    DEC(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Abs_DEC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    DEC(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int X_Abs_DEC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    DEC(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int INX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->X += 1;
    cpu->N = ((cpu->X & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->X == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int DEX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->X -= 1;
    cpu->N = ((cpu->X & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->X == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int INY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->Y += 1;
    cpu->N = ((cpu->Y & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->Y == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int DEY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->Y -= 1;
    cpu->N = ((cpu->Y & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->Y == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int CLC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->C = false;
    cpu->PC += 1;
    return 2;
}

unsigned int SEC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->C = true;
    cpu->PC += 1;
    return 2;
}

unsigned int CLI(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->I = false;
    cpu->PC += 1;
    return 2;
}

unsigned int SEI(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->I = true;
    cpu->PC += 1;
    return 2;
}

unsigned int CLD(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->D = false;
    cpu->PC += 1;
    return 2;
}

unsigned int SED(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->D = true;
    cpu->PC += 1;
    return 2;
}

unsigned int CLV(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->V = false;
    cpu->PC += 1;
    return 2;
}

unsigned int Imm_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    LDA(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    LDA(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    LDA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    LDA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    LDA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    LDA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    LDA(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Y_Indir_LDA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    LDA(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Imm_LDX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    LDX(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_LDX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    LDX(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int Y_ZePa_LDX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->Y);
    LDX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_LDX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    LDX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_LDX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    LDX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Imm_LDY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    LDY(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_LDY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    LDY(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_LDY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    LDY(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_LDY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    LDY(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_LDY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    LDY(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int ZePa_STA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    STA(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_STA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    STA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_STA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    STA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_STA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    STA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_STA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    STA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_STA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    STA(nes, m);
    cpu->PC += 1;
    return 6;
}

unsigned int Y_Indir_STA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    STA(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_STX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    STX(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int Y_ZePa_STX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->Y);
    STX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_STX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    STX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int ZePa_STY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    STY(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_STY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    STY(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_STY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    STY(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int TAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->X = cpu->A;
    cpu->N = ((cpu->X & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->X == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int TXA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->A = cpu->X;
    cpu->N = ((cpu->A & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->A == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int TAY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->Y = cpu->A;
    cpu->N = ((cpu->Y & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->Y == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int TYA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->A = cpu->Y;
    cpu->N = ((cpu->A & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->A == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int TSX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->X = (uint8_t)cpu->SP;
    cpu->N = ((cpu->X & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->X == 0) ? true : false;
    cpu->PC += 1;
    return 2;
}

unsigned int TXS(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->SP = (uint16_t)cpu->X + 256;
    cpu->PC += 1;
    return 2;
}

unsigned int PHA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    push(cpu, cpu->A);
    cpu->PC += 1;
    return 3;
}

unsigned int PLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->A = pop(cpu);
    cpu->N = ((cpu->A & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->A == 0) ? true : false;
    cpu->PC += 1;
    return 4;
}

unsigned int PHP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t status;
    status = (cpu->N * 128) + (cpu->V * 64) + 32 + (cpu->B * 16) + (cpu->D * 8) + (cpu->I * 4) + (cpu->Z * 2) + cpu->C;
    push(cpu, status);
    cpu->PC += 1;
    return 3;
}

unsigned int PLP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t status = pop(cpu);

    // �r�b�g���f
    cpu->C = (bool)(status & 0x01);
    cpu->Z = (bool)((status >> 1) & 0x01);
    cpu->I = (bool)((status >> 2) & 0x01);
    cpu->D = (bool)((status >> 3) & 0x01);
    cpu->B = false;
    // Unused (bit 5) �� ���1�Ƃ��Ă���
    cpu->V = (bool)((status >> 6) & 0x01);
    cpu->N = (bool)((status >> 7) & 0x01);

    cpu->PC += 1;
    return 4;
}

unsigned int NOP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    return 2;
}

//�s�v�Ȗ���

unsigned int single_NOP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 2;
    return 3;
}

unsigned int double_NOP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 3;
    return 4;
}

unsigned int Imm_LAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    LAX(nes, m);
    cpu->PC += 1;
    return 2;
}

unsigned int ZePa_LAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    LAX(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int Y_ZePa_LAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->Y);
    LAX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_LAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    LAX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_LAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    LAX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_LAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    LAX(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Y_Indir_LAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    LAX(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_SAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    SAX(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int Y_ZePa_SAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->Y);
    SAX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_SAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    SAX(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_SAX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    SAX(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_DCP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    DCP(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_DCP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    DCP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_DCP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    DCP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_DCP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    DCP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_DCP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    DCP(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_DCP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    DCP(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Y_Indir_DCP(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    DCP(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_ISC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    ISC(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_ISC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    ISC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_ISC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    ISC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_ISC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    ISC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_ISC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    ISC(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_ISC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    ISC(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Y_Indir_ISC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    ISC(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_SLO(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    SLO(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_SLO(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    SLO(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_SLO(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    SLO(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_SLO(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    SLO(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_SLO(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    SLO(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_SLO(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    SLO(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Y_Indir_SLO(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    SLO(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_RLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    RLA(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_RLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    RLA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_RLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    RLA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_RLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    RLA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_RLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    RLA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_RLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    RLA(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Y_Indir_RLA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    RLA(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_SRE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    SRE(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_SRE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    SRE(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_SRE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    SRE(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_SRE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    SRE(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_SRE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    SRE(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_SRE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    SRE(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Y_Indir_SRE(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    SRE(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int ZePa_RRA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = ZeroPage(cpu);
    RRA(nes, m);
    cpu->PC += 1;
    return 3;
}

unsigned int X_ZePa_RRA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexZeroPage(cpu, cpu->X);
    RRA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Abs_RRA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Absolute(cpu);
    RRA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Abs_RRA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->X);
    RRA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int Y_Abs_RRA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = IndexAbsolute(cpu, cpu->Y);
    RRA(nes, m);
    cpu->PC += 1;
    return 4;
}

unsigned int X_Indir_RRA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = XIndirect(cpu);
    RRA(nes, m);
    cpu->PC += 1;
    return 5;
}

unsigned int Y_Indir_RRA(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = YIndirect(cpu);
    RRA(nes, m);
    cpu->PC += 1;
    return 5;
}

//�o�O���܂ގw��
unsigned int Y_Abs_SHX(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;

    uint16_t addr = cpu->cpu_mem[cpu->PC + 1] | (cpu->cpu_mem[cpu->PC + 2] << 8);
    uint16_t effective_addr = addr + cpu->Y;

    uint8_t value;
    if ((addr & 0xFF00) != (effective_addr & 0xFF00)) {
        value = cpu->X & (effective_addr >> 8);
    }
    else {
        value = cpu->X & ((addr >> 8) + 1);
    }

    write_data(nes, &cpu->cpu_mem[effective_addr], value);
    cpu->PC += 3;
    return 5;
}

unsigned int X_Abs_SHY(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;

    uint16_t addr = cpu->cpu_mem[cpu->PC + 1] | (cpu->cpu_mem[cpu->PC + 2] << 8);
    uint16_t effective_addr = addr + cpu->X;

    uint8_t value;
    if ((addr & 0xFF00) != (effective_addr & 0xFF00)) {
        value = cpu->Y & (effective_addr >> 8);
    }
    else {
        value = cpu->Y & ((addr >> 8) + 1);
    }

    write_data(nes, &cpu->cpu_mem[effective_addr], value);
    cpu->PC += 3;
    return 5;
}

unsigned int ANC(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC += 1;
    uint8_t* m = Immidiate(cpu);
    cpu->A = cpu->A & *m;
    cpu->C = ((cpu->A & 0x80) != 0);
    cpu->Z = (cpu->A == 0);
    cpu->N = ((cpu->A & 0x80) != 0);
    return 2;
}

void init_operations(void) {

    operations[0x00] = BRK;
    operations[0x01] = X_Indir_ORA;
    operations[0x03] = X_Indir_SLO;
    operations[0x04] = single_NOP;
    operations[0x05] = ZePa_ORA;
    operations[0x06] = ZePa_ASL;
    operations[0x07] = ZePa_SLO;
    operations[0x08] = PHP;
    operations[0x09] = Imm_ORA;
    operations[0x0A] = Accum_ASL;
    operations[0x0B] = ANC;
    operations[0x0C] = double_NOP;
    operations[0x0D] = Abs_ORA;
    operations[0x0E] = Abs_ASL;
    operations[0x0F] = Abs_SLO;
    operations[0x10] = BPL;
    operations[0x11] = Y_Indir_ORA;
    operations[0x13] = Y_Indir_SLO;
    operations[0x14] = single_NOP;
    operations[0x15] = X_ZePa_ORA;
    operations[0x16] = X_ZePa_ASL;
    operations[0x17] = X_ZePa_SLO;
    operations[0x18] = CLC;
    operations[0x19] = Y_Abs_ORA;
    operations[0x1A] = NOP;
    operations[0x1B] = Y_Abs_SLO;
    operations[0x1C] = double_NOP;
    operations[0x1D] = X_Abs_ORA;
    operations[0x1E] = X_Abs_ASL;
    operations[0x1F] = X_Abs_SLO;
    operations[0x20] = JSR;
    operations[0x21] = X_Indir_AND;
    operations[0x23] = X_Indir_RLA;
    operations[0x24] = ZePa_BIT;
    operations[0x25] = ZePa_AND;
    operations[0x26] = ZePa_ROL;
    operations[0x27] = ZePa_RLA;
    operations[0x28] = PLP;
    operations[0x29] = Imm_AND;
    operations[0x2A] = Accum_ROL;
    operations[0x2B] = ANC;
    operations[0x2C] = Abs_BIT;
    operations[0x2D] = Abs_AND;
    operations[0x2E] = Abs_ROL;
    operations[0x2F] = Abs_RLA;
    operations[0x30] = BMI;
    operations[0x31] = Y_Indir_AND;
    operations[0x33] = Y_Indir_RLA;
    operations[0x34] = single_NOP;
    operations[0x35] = X_ZePa_AND;
    operations[0x36] = X_ZePa_ROL;
    operations[0x37] = X_ZePa_RLA;
    operations[0x38] = SEC;
    operations[0x39] = Y_Abs_AND;
    operations[0x3A] = NOP;
    operations[0x3B] = Y_Abs_RLA;
    operations[0x3C] = double_NOP;
    operations[0x3D] = X_Abs_AND;
    operations[0x3E] = X_Abs_ROL;
    operations[0x3F] = X_Abs_RLA;
    operations[0x40] = RTI;
    operations[0x41] = X_Indir_EOR;
    operations[0x43] = X_Indir_SRE;
    operations[0x44] = single_NOP;
    operations[0x45] = ZePa_EOR;
    operations[0x46] = ZePa_LSR;
    operations[0x47] = ZePa_SRE;
    operations[0x48] = PHA;
    operations[0x49] = Imm_EOR;
    operations[0x4A] = Accum_LSR;
    operations[0x4C] = Abs_JMP;
    operations[0x4D] = Abs_EOR;
    operations[0x4E] = Abs_LSR;
    operations[0x4F] = Abs_SRE;
    operations[0x50] = BVC;
    operations[0x51] = Y_Indir_EOR;
    operations[0x53] = Y_Indir_SRE;
    operations[0x54] = single_NOP;
    operations[0x55] = X_ZePa_EOR;
    operations[0x56] = X_ZePa_LSR;
    operations[0x57] = X_ZePa_SRE;
    operations[0x58] = CLI;
    operations[0x59] = Y_Abs_EOR;
    operations[0x5A] = NOP;
    operations[0x5B] = Y_Abs_SRE;
    operations[0x5C] = double_NOP;
    operations[0x5D] = X_Abs_EOR;
    operations[0x5E] = X_Abs_LSR;
    operations[0x5F] = X_Abs_SRE;
    operations[0x60] = RTS;
    operations[0x61] = X_Indir_ADC;
    operations[0x63] = X_Indir_RRA;
    operations[0x64] = single_NOP;
    operations[0x65] = ZePa_ADC;
    operations[0x66] = ZePa_ROR;
    operations[0x67] = ZePa_RRA;
    operations[0x68] = PLA;
    operations[0x69] = Imm_ADC;
    operations[0x6A] = Accum_ROR;
    operations[0x6C] = Indir_JMP;
    operations[0x6D] = Abs_ADC;
    operations[0x6E] = Abs_ROR;
    operations[0x6F] = Abs_RRA;
    operations[0x70] = BVS;
    operations[0x71] = Y_Indir_ADC;
    operations[0x73] = Y_Indir_RRA;
    operations[0x74] = single_NOP;
    operations[0x75] = X_ZePa_ADC;
    operations[0x76] = X_ZePa_ROR;
    operations[0x77] = X_ZePa_RRA;
    operations[0x78] = SEI;
    operations[0x79] = Y_Abs_ADC;
    operations[0x7A] = NOP;
    operations[0x7B] = Y_Abs_RRA;
    operations[0x7C] = double_NOP;
    operations[0x7D] = X_Abs_ADC;
    operations[0x7E] = X_Abs_ROR;
    operations[0x7F] = X_Abs_RRA;
    operations[0x80] = single_NOP;
    operations[0x81] = X_Indir_STA;
    operations[0x82] = single_NOP;
    operations[0x83] = X_Indir_SAX;
    operations[0x84] = ZePa_STY;
    operations[0x85] = ZePa_STA;
    operations[0x86] = ZePa_STX;
    operations[0x87] = ZePa_SAX;
    operations[0x88] = DEY;
    operations[0x89] = single_NOP;
    operations[0x8A] = TXA;
    operations[0x8C] = Abs_STY;
    operations[0x8D] = Abs_STA;
    operations[0x8E] = Abs_STX;
    operations[0x8F] = Abs_SAX;
    operations[0x90] = BCC;
    operations[0x91] = Y_Indir_STA;
    operations[0x94] = X_ZePa_STY;
    operations[0x95] = X_ZePa_STA;
    operations[0x96] = Y_ZePa_STX;
    operations[0x97] = Y_ZePa_SAX;
    operations[0x98] = TYA;
    operations[0x99] = Y_Abs_STA;
    operations[0x9A] = TXS;
    operations[0x9C] = X_Abs_SHY;
    operations[0x9D] = X_Abs_STA;
    operations[0x9E] = Y_Abs_SHX;
    operations[0xA0] = Imm_LDY;
    operations[0xA1] = X_Indir_LDA;
    operations[0xA2] = Imm_LDX;
    operations[0xA3] = X_Indir_LAX;
    operations[0xA4] = ZePa_LDY;
    operations[0xA5] = ZePa_LDA;
    operations[0xA6] = ZePa_LDX;
    operations[0xA7] = ZePa_LAX;
    operations[0xA8] = TAY;
    operations[0xA9] = Imm_LDA;
    operations[0xAA] = TAX;
    operations[0xAB] = Imm_LAX;
    operations[0xAC] = Abs_LDY;
    operations[0xAD] = Abs_LDA;
    operations[0xAE] = Abs_LDX;
    operations[0xAF] = Abs_LAX;
    operations[0xB0] = BCS;
    operations[0xB1] = Y_Indir_LDA;
    operations[0xB3] = Y_Indir_LAX;
    operations[0xB4] = X_ZePa_LDY;
    operations[0xB5] = X_ZePa_LDA;
    operations[0xB6] = Y_ZePa_LDX;
    operations[0xB7] = Y_ZePa_LAX;
    operations[0xB8] = CLV;
    operations[0xB9] = Y_Abs_LDA;
    operations[0xBA] = TSX;
    operations[0xBC] = X_Abs_LDY;
    operations[0xBD] = X_Abs_LDA;
    operations[0xBE] = Y_Abs_LDX;
    operations[0xBF] = Y_Abs_LAX;
    operations[0xC0] = Imm_CPY;
    operations[0xC1] = X_Indir_CMP;
    operations[0xC2] = single_NOP;
    operations[0xC3] = X_Indir_DCP;
    operations[0xC4] = ZePa_CPY;
    operations[0xC5] = ZePa_CMP;
    operations[0xC6] = ZePa_DEC;
    operations[0xC7] = ZePa_DCP;
    operations[0xC8] = INY;
    operations[0xC9] = Imm_CMP;
    operations[0xCA] = DEX;
    operations[0xCC] = Abs_CPY;
    operations[0xCD] = Abs_CMP;
    operations[0xCE] = Abs_DEC;
    operations[0xCF] = Abs_DCP;
    operations[0xD0] = BNE;
    operations[0xD1] = Y_Indir_CMP;
    operations[0xD3] = Y_Indir_DCP;
    operations[0xD4] = single_NOP;
    operations[0xD5] = X_ZePa_CMP;
    operations[0xD6] = X_ZePa_DEC;
    operations[0xD7] = X_ZePa_DCP;
    operations[0xD8] = CLD;
    operations[0xD9] = Y_Abs_CMP;
    operations[0xDA] = NOP;
    operations[0xDB] = Y_Abs_DCP;
    operations[0xDC] = double_NOP;
    operations[0xDD] = X_Abs_CMP;
    operations[0xDE] = X_Abs_DEC;
    operations[0xDF] = X_Abs_DCP;
    operations[0xE0] = Imm_CPX;
    operations[0xE1] = X_Indir_SBC;
    operations[0xE2] = single_NOP;
    operations[0xE3] = X_Indir_ISC;
    operations[0xE4] = ZePa_CPX;
    operations[0xE5] = ZePa_SBC;
    operations[0xE6] = ZePa_INC;
    operations[0xE7] = ZePa_ISC;
    operations[0xE8] = INX;
    operations[0xE9] = Imm_SBC;
    operations[0xEA] = NOP;
    operations[0xEB] = Imm_SBC;
    operations[0xEC] = Abs_CPX;
    operations[0xED] = Abs_SBC;
    operations[0xEE] = Abs_INC;
    operations[0xEF] = Abs_ISC;
    operations[0xF0] = BEQ;
    operations[0xF1] = Y_Indir_SBC;
    operations[0xF3] = Y_Indir_ISC;
    operations[0xF4] = single_NOP;
    operations[0xF5] = X_ZePa_SBC;
    operations[0xF6] = X_ZePa_INC;
    operations[0xF7] = X_ZePa_ISC;
    operations[0xF8] = SED;
    operations[0xF9] = Y_Abs_SBC;
    operations[0xFA] = NOP;
    operations[0xFB] = Y_Abs_ISC;
    operations[0xFC] = double_NOP;
    operations[0xFD] = X_Abs_SBC;
    operations[0xFE] = X_Abs_INC;
    operations[0xFF] = X_Abs_ISC;
}