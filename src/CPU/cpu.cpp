/*
命令の処理を行う関数
命令処理の内容はoperation_set.cpp
割込み処理の内容はinterrupt.cpp
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <iostream>

#include "operation_set.h"
#include "nes_manager.h"
#include "interrupt.h"

CPU_Emulator* create_cpu() {
    CPU_Emulator* cpu = new CPU_Emulator;
    cpu->cpu_mem = new uint8_t[256*256];
    memset(cpu->cpu_mem, 0, 256 * 256);

    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->PC = 0x8000;
    cpu->SP = 0x01FD;
    cpu->N = false;
    cpu->V = false;
    cpu->B = false;
    cpu->D = false;
    cpu->I = true;
    cpu->Z = false;
    cpu->C = false;

    return cpu;
}

unsigned int CPU(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    NES_Manager* mgr = nes->Mgr;
    unsigned int cycle = 0;

    uint8_t ope = cpu->cpu_mem[cpu->PC];

    if (operations[ope] == NULL) {
        printf("Not found operation of 0x%x. PC:%x\n", ope, cpu->PC);
        mgr->error = true;
        cpu->PC += 1;
        return 1;
    }

    //命令実行
    cycle = operations[ope](nes);

    //割込み処理
    InterruptFunction(cpu, &mgr->NMIpin, &mgr->IRQpin);

    return cycle;
}