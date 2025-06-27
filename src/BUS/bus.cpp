/*
PPUに関係するアドレスやその他特殊な処理を行うアドレス用のファイル
PPUのメモリに関する処理はppu.cpp
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "ppu_emu.h"
#include "nes_manager.h"

void write_data(NES_Emulator* nes, uint8_t* addr, uint8_t value) {
    CPU_Emulator* cpu = nes->Cpu;
    PPU_Emulator* ppu = nes->Ppu;
    uint16_t index = addr - cpu->cpu_mem;
    if(index < 0x8000){
        *addr = value;
        //PPUに関する処理
        if (index == 0x2006) {
            ppu_addr_write(nes);
        }
        else if (index == 0x2007) {
            ppu->ppu_mem[ppu->vram_addr] = *addr;
            mirroring(nes, addr);
            ppu_addr_inc(nes);
        }
        else if (index == 0x2003) {
            ppu->sprite_addr = cpu->cpu_mem[0x2003];
        }
        else if (index == 0x2004) {
            ppu->sprite[ppu->sprite_addr] = *addr;
            ppu->sprite_addr += 1;
        }
        //OAMに関する処理
        else if (index == 0x4014) {
            uint16_t sprite_index = (uint16_t)*addr << 8;
            memcpy(ppu->sprite, cpu->cpu_mem + sprite_index, 256);
        }
        //コントローラーに関する処理
        else if (index == 0x4016) {
            Controller_Emulator* con = nes->Con;
            if (!(con->signal) && ((cpu->cpu_mem[0x4016] & 0b00000001) == 1)) {
                con->trigger = true;
            }
            if ((con->trigger) && ((cpu->cpu_mem[0x4016] & 0b00000001) == 0)) {
                con->signal = true;
            }
        }
    }
    else{
        //マッパー処理
        memcpy(ppu->ppu_mem, ppu->bank + value * 8192, 8192);
    }
}

uint8_t read_data(NES_Emulator* nes, uint8_t* addr) {
    uint8_t send = *addr;
    CPU_Emulator* cpu = nes->Cpu;
    uint16_t index = addr - cpu->cpu_mem;
    //PPUに関する処理
    if (index == 0x2007) {
        send = (nes->Ppu)->buffer;
        (nes->Ppu)->buffer = (nes->Ppu)->ppu_mem[(nes->Ppu)->vram_addr];
        ppu_addr_inc(nes);
        return send;
    }
    else if (index == 0x2002) {
        *addr &= 0b01111111;
    }
    //OAMに関する処理
    else if (index == 0x4016) {
        Controller_Emulator* con = nes->Con;
        if (con->signal) {
            send = (con->index & con->reg) ? 1 : 0;
            con->index <<= 1;
            if (con->index == 0) {
                con->index = 1;
                con->trigger = false;
                con->signal = false;
            }
            
        }
    }

    return send;
}