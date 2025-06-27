/*
アドレスを必要とする命令が記述されているファイル
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"
#include "addressing.h"
#include "bus.h"

void ADC(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    uint16_t result = cpu->A + val + (cpu->C ? 1 : 0);

    cpu->C = result > 0xFF;
    cpu->Z = (result & 0xFF) == 0;
    cpu->N = (result & 0x80) != 0;
    cpu->V = (~(cpu->A ^ val) & (cpu->A ^ result) & 0x80) != 0;

    cpu->A = result & 0xFF;
}

void SBC(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m) ^ 0xFF;
    uint16_t result = cpu->A + val + (cpu->C ? 1 : 0);

    cpu->C = result > 0xFF;
    cpu->Z = (result & 0xFF) == 0;
    cpu->N = (result & 0x80) != 0;
    cpu->V = ((cpu->A ^ result) & (val ^ result) & 0x80) != 0;

    cpu->A = result & 0xFF;
}

void AND(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t a = cpu->A;
    uint8_t val = read_data(nes, m);
    cpu->A = (a & val);

    cpu->N = ((cpu->A & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->A == 0) ? true : false;
}

void ORA(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t a = cpu->A;
    uint8_t val = read_data(nes, m);
    cpu->A = (a | val);

    cpu->N = ((cpu->A & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->A == 0) ? true : false;
}

void EOR(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t a = cpu->A;
    uint8_t val = read_data(nes, m);
    cpu->A = (a ^ val);

    cpu->N = ((cpu->A & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->A == 0) ? true : false;
}

void ASL(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->C = ((*m & 0b10000000) != 0);
    *m = *m << 1;

    cpu->Z = (*m == 0);
    cpu->N = ((*m & 0b10000000) != 0);
}

void LSR(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->C = ((*m & 0x01) != 0);
    *m >>= 1;

    cpu->Z = (*m == 0);
    cpu->N = false;
}

void ROL(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;

    bool old_bit7 = (*m & 0x80) != 0;
    *m = ((*m << 1) | (cpu->C ? 1 : 0));

    cpu->C = old_bit7;
    cpu->Z = (*m == 0);
    cpu->N = ((*m & 0x80) != 0);
}

void ROR(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;

    bool old_bit0 = ((*m & 0x01) != 0);
    *m = ((*m >> 1) | (cpu->C ? 0x80 : 0x00));

    cpu->C = old_bit0;
    cpu->Z = (*m == 0);
    cpu->N = ((*m & 0x80) != 0);
}

void BIT(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    uint8_t and_result = (cpu->A & val);

    cpu->N = ((val & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (and_result == 0) ? true : false;
    cpu->V = ((val & 0b01000000) == 0b01000000) ? true : false;
}

void JMP(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    cpu->PC = (uint16_t)(m - cpu->cpu_mem);
}


void CMP(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t cmp = cpu->A - *m;

    cpu->N = ((cmp & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cmp == 0) ? true : false;
    cpu->C = (cpu->A >= *m) ? true : false;
}

void CPX(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t cmp = cpu->X - *m;

    cpu->N = ((cmp & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cmp == 0) ? true : false;
    cpu->C = (cpu->X >= *m) ? true : false;
}

void CPY(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t cmp = cpu->Y - *m;

    cpu->N = ((cmp & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cmp == 0) ? true : false;
    cpu->C = (cpu->Y >= *m) ? true : false;
}

void INC(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    *m += 1;

    cpu->N = ((*m & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (*m == 0) ? true : false;
}

void DEC(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    *m -= 1;

    cpu->N = ((*m & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (*m == 0) ? true : false;
}

void LDA(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    cpu->A = val;
    cpu->N = ((cpu->A & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->A == 0) ? true : false;
}

void LDX(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    cpu->X = val;

    cpu->N = ((cpu->X & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->X == 0) ? true : false;
}

void LDY(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    cpu->Y = val;

    cpu->N = ((cpu->Y & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->Y == 0) ? true : false;
}

void STA(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    write_data(nes, m, cpu->A);
}

void STX(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    write_data(nes, m, cpu->X);
}

void STY(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    write_data(nes, m, cpu->Y);
}

//�g�p���Ȃ�����

void LAX(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    cpu->A = val;
    cpu->X = val;

    cpu->N = ((cpu->X & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cpu->X == 0) ? true : false;
}

void SAX(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t and_result = (cpu->A & cpu->X);
    write_data(nes, m, and_result);
}

void DCP(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    *m -= 1;
    uint8_t cmp = cpu->A - *m;

    cpu->N = ((cmp & 0b10000000) == 0b10000000) ? true : false;
    cpu->Z = (cmp == 0) ? true : false;
    cpu->C = (cpu->A >= *m) ? true : false;
}

void ISC(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m) + 1;
    write_data(nes, m, val);

    uint8_t a = cpu->A;
    uint16_t result = (uint16_t)a - (uint16_t)val - (1 - cpu->C);

    cpu->C = result < 0x100;
    cpu->Z = (result & 0xFF) == 0;
    cpu->N = (result & 0x80) != 0;
    cpu->V = ((a ^ val) & 0x80) && ((a ^ result) & 0x80);

    cpu->A = result & 0xFF;
}


void SLO(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    cpu->C = (val & 0x80) != 0;
    val <<= 1;
    write_data(nes, m, val);

    cpu->A |= val;

    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) != 0;
}

void RLA(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    bool old_c = cpu->C;

    cpu->C = (val & 0x80) != 0;
    val = (val << 1) | (old_c ? 1 : 0);
    write_data(nes, m, val);

    cpu->A &= val;
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) != 0;
}

void SRE(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    cpu->C = (val & 0x01) != 0;

    val >>= 1;
    write_data(nes, m, val);

    cpu->A ^= val;
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) != 0;
}

void RRA(NES_Emulator* nes, uint8_t* m) {
    CPU_Emulator* cpu = nes->Cpu;
    uint8_t val = read_data(nes, m);
    bool old_c = cpu->C;

    cpu->C = (val & 0x01) != 0;
    val = (val >> 1) | (old_c ? 0x80 : 0x00);
    write_data(nes, m, val);

    uint16_t result = (uint16_t)cpu->A + val + (cpu->C ? 1 : 0);
    cpu->V = (~(cpu->A ^ val) & (cpu->A ^ result) & 0x80) != 0;
    cpu->C = result > 0xFF;
    cpu->A = result & 0xFF;
    cpu->Z = (cpu->A == 0);
    cpu->N = (cpu->A & 0x80) != 0;
}