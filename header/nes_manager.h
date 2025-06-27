#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool Reset;
    bool error;
    bool NMIpin;
    bool IRQpin;

    unsigned int cycle;
} NES_Manager;

typedef struct {
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint16_t PC;
    uint16_t SP;

    bool N;
    bool V;
    bool B;
    bool D;
    bool I;
    bool Z;
    bool C;

    uint8_t* cpu_mem;
} CPU_Emulator;

typedef struct {
    bool l_addr;
    uint16_t vram_addr;
    uint8_t sprite_addr;

    uint8_t buffer;

    uint8_t* ppu_mem;
    uint8_t* sprite;
    uint8_t* OAM_buffer;
    uint8_t* bank;

    uint8_t OAM_num;
    uint8_t mapper;

    bool Vblank_trigger;
    bool Nametable_arrangement;
    bool sprite0_hit_flag;
} PPU_Emulator;

typedef struct {
    bool signal;
    bool trigger;
    uint8_t reg;

    uint8_t index;
} Controller_Emulator;

typedef struct {
    CPU_Emulator* Cpu;
    PPU_Emulator* Ppu;
    NES_Manager* Mgr;
    Controller_Emulator* Con;
} NES_Emulator;

typedef struct {
    unsigned int line;
    uint8_t* screen;

    bool complete;
    bool drawing;
} Screen;