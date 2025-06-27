/*
PPUの処理を行うファイル
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nes_manager.h"
#include "interrupt.h"
#include "read_nes.h"

PPU_Emulator* create_ppu() {
    PPU_Emulator* ppu = new PPU_Emulator;
    ppu->ppu_mem = new uint8_t[4*16*256];
    ppu->sprite = new uint8_t[256];
    ppu->OAM_buffer = new uint8_t[8 * 4];
    ppu->bank = new uint8_t[8192 * 8];
    memset(ppu->ppu_mem, 0, 4 * 16 * 256);
    memset(ppu->sprite, 0, 256);
    memset(ppu->OAM_buffer, 0, 8 * 4);
    memset(ppu->bank, 0, 8192 * 8);

    ppu->buffer = 0;
    ppu->mapper = 0;

    ppu->l_addr = false;
    ppu->vram_addr = 0;
    ppu->sprite_addr = 0;
    ppu->OAM_num = 0;

    ppu->Vblank_trigger = false;
    ppu->Nametable_arrangement = false;
    ppu->sprite0_hit_flag = false;

    return ppu;
}

static uint8_t make_palette_index(uint8_t* mem, uint16_t nametable, uint8_t index) {
    int row = index / 32;
    int palette_row = row / 4;
    int column = index % 32;
    int palette_column = column / 4;

    uint8_t palette_index = mem[nametable + 0x3C0 + (palette_row * 8) + palette_column];
    if ((row % 4 == 0) || (row % 4 == 1)) {
        if ((column % 4 == 0) || (column % 4 == 1)) {
            return (uint8_t)((palette_index & 0b00000011));
        }
        else {
            return (uint8_t)((palette_index & 0b00001100) >> 2);
        }
    }
    else {
        if ((column % 4 == 0) || (column % 4 == 1)) {
            return (uint8_t)((palette_index & 0b00110000) >> 4);
        }
        else {
            return (uint8_t)((palette_index & 0b11000000) >> 6);
        }
    }
}

//0ヒット処理
void sprite_0hit(CPU_Emulator* cpu, PPU_Emulator* ppu, Screen* canvas, uint8_t* index_chr) {
    ppu->sprite0_hit_flag = false;
    cpu->cpu_mem[0x2002] &= ~(1 << 6);

    uint8_t y0 = ppu->sprite[0];
    uint8_t index0 = ppu->sprite[1];
    uint8_t attr0 = ppu->sprite[2];
    uint8_t x0 = ppu->sprite[3];
    bool flipH0 = attr0 & 0x40;
    bool flipV0 = attr0 & 0x80;
    uint8_t pal0 = attr0 & 0b11;

    if (!(ppu->sprite0_hit_flag) && (canvas->line >= y0) && (canvas->line < y0 + 8) && (cpu->cpu_mem[0x2001] & 0x18) == 0x18) {

        int row = flipV0 ? (7 - (canvas->line - y0)) : (canvas->line - y0);

        for (int col = 0; col < 8; col++) {
            int src_col = flipH0 ? (7 - col) : col;
            uint8_t spr_color = index_chr[index0 * 64 + row * 8 + src_col];
            if (spr_color == 0) continue;

            int x = x0 + col;
            if (x < 0 || x >= 256) continue;
            if (x < 8 && ((cpu->cpu_mem[0x2001] & 0b00000010) == 0)) continue;

            uint8_t bg_pixel = canvas->screen[canvas->line * 256 + x] & 0x3F;
            if ((bg_pixel % 4) == 0) continue;

            cpu->cpu_mem[0x2002] |= (1 << 6);
            ppu->sprite0_hit_flag = true;
            break;
        }
    }
}

void PPU(NES_Emulator* nes, Screen* canvas, uint8_t* index_chr, unsigned int clk) {
    CPU_Emulator* cpu = nes->Cpu;
    PPU_Emulator* ppu = nes->Ppu;
    NES_Manager* mgr = nes->Mgr;
    uint8_t sprite_index, palette_index;

    uint8_t sprite[64];

    for(int i = 0; i < clk * 3; i++){
        mgr->cycle++;
        //一列完了
        if(mgr->cycle == 341){
            canvas->line++;
            mgr->cycle -= 341;
        }
        //全行完了
        if ((canvas->line == 259) && (mgr->cycle == 340)) {
            canvas->line = 0;
            canvas->complete = false;
            cpu->cpu_mem[0x2002] &= 0b01111111;
            make_CHR(index_chr, ppu->ppu_mem);
            return;
        }
        //画面の行外範囲
        else if ((canvas->line == 240) && (mgr->cycle == 0)) {
            cpu->cpu_mem[0x2002] |= 0b10000000;
            if (((cpu->cpu_mem[0x2000] & 0b10000000) == 0b10000000) && (ppu->Vblank_trigger)) {
                mgr->NMIpin = false;
                ppu->Vblank_trigger = false;
            }
        }
        //画面内最終行
        else if ((canvas->line == 239) && (mgr->cycle == 340)) {
            canvas->complete = true;
            ppu->Vblank_trigger = true;
            canvas->drawing = true;
            return;
        }
        
        if (!(canvas->complete)) {
            uint8_t pixel_x, pixel_y;
            uint16_t nametable;
            uint8_t row;
            uint8_t tile;
            uint8_t sprite_pixel_x, sprite_pixel_y;
            //ネームテーブルの決定
            if ((cpu->cpu_mem[0x2000] & 0b00000011) == 0b00000000) {
                nametable = 0x2000;
            }
            else if ((cpu->cpu_mem[0x2000] & 0b00000011) == 0b00000001) {
                nametable = 0x2400;
            }
            else if ((cpu->cpu_mem[0x2000] & 0b00000011) == 0b00000010) {
                nametable = 0x2800;
            }
            else {
                nametable = 0x2C00;
            }
            //画面描画範囲
            if(mgr->cycle < 256){
                pixel_x = mgr->cycle;
                pixel_y = canvas->line;
                row = pixel_y / 8;
                tile = pixel_x / 8;
                sprite_index = ppu->ppu_mem[nametable + (row * 32) + tile];
                palette_index = make_palette_index(ppu->ppu_mem, nametable, row * 32 + tile);
                sprite_pixel_x = pixel_x % 8;
                sprite_pixel_y = pixel_y % 8;
                canvas->screen[256 * pixel_y + pixel_x] = ppu->ppu_mem[0x3F00 + palette_index * 4 + index_chr[sprite_index * 64 + 8 * sprite_pixel_y + sprite_pixel_x]];
                
                if(pixel_y != 0){
                    int8_t sprite_MAX = (ppu->OAM_num > 8) ? 7 : ppu->OAM_num-1;
                    //OAM_bufferに保存されているスプライトの処理
                    for(int j = sprite_MAX; j > -1; j--){
                        uint8_t y = ppu->OAM_buffer[j * 4];
                        uint8_t tile_index = ppu->OAM_buffer[j * 4 + 1];
                        uint8_t attr = ppu->OAM_buffer[j * 4 + 2];
                        uint8_t x = ppu->OAM_buffer[j * 4 + 3];

                        uint8_t palette = attr & 0b11;
                        bool back_background = attr & 0x20;
                        if (back_background) continue;
                        bool flipH = attr & 0x40;
                        bool flipV = attr & 0x80;

                        uint8_t sprite_row = pixel_y - y;
                        int16_t sprite_col = pixel_x - x;
                        if((sprite_col < 0) || (sprite_col >= 8)) continue;
                        uint8_t src_col = flipH ? (7 - sprite_col) : sprite_col;
                        uint8_t src_row = flipV ? (7 - sprite_row) : sprite_row;
                        uint8_t color_index = index_chr[tile_index * 64 + src_row * 8 + src_col];
                        if(color_index == 0) continue;
                        canvas->screen[pixel_y * 256 + pixel_x] = ppu->ppu_mem[0x3F10 + palette * 4 + color_index];
                    }
                }
            }
            //画面外の列範囲
            else if(mgr->cycle < 319){
                //OAM_bufferの更新
                if(mgr->cycle == 256){
                    ppu->OAM_num = 0;
                    cpu->cpu_mem[0x2002] &= ~(1 << 5);
                    memset(ppu->OAM_buffer, 0, 8 * 4);
                }

                uint8_t OAM_index = mgr->cycle - 256;
                uint8_t evaluation_y = ppu->sprite[4 * OAM_index];
                
                int16_t tmp = canvas->line + 1 - evaluation_y;
                if((tmp >= 0) && (tmp < 8)){
                    ppu->OAM_num++;
                    if(ppu->OAM_num < 9) memcpy(ppu->OAM_buffer + (ppu->OAM_num - 1) * 4, ppu->sprite + 4 * OAM_index, 4);
                    else cpu->cpu_mem[0x2002] |= (1 << 5);
                }
            }
            sprite_0hit(cpu, ppu, canvas, index_chr);
        }
    }
}

void ppu_addr_write(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    PPU_Emulator* ppu = nes->Ppu;
    if (!(ppu->l_addr)) {
        ppu->vram_addr = 0;
        ppu->vram_addr += (uint16_t)cpu->cpu_mem[0x2006] << 8;
        ppu->l_addr = true;
    }
    else {
        ppu->vram_addr += (uint16_t)cpu->cpu_mem[0x2006];
        ppu->l_addr = false;
    }
}

void ppu_addr_inc(NES_Emulator* nes) {
    CPU_Emulator* cpu = nes->Cpu;
    PPU_Emulator* ppu = nes->Ppu;
    if ((cpu->cpu_mem[0x2000] & 0b00000100) == 0b00000100) {
        ppu->vram_addr += 32;
    }
    else {
        ppu->vram_addr += 1;
    }
}

void mirroring(NES_Emulator* nes, uint8_t* addr) {
    CPU_Emulator* cpu = nes->Cpu;
    PPU_Emulator* ppu = nes->Ppu;
    if ((ppu->vram_addr >= 0x2000) && (ppu->vram_addr < 0x3000)) {
        if (ppu->Nametable_arrangement) {
            if ((ppu->vram_addr >= 0x2000) && (ppu->vram_addr < 0x2400)) ppu->ppu_mem[ppu->vram_addr + 0x800] = *addr;
            else if ((ppu->vram_addr >= 0x2400) && (ppu->vram_addr < 0x2800)) ppu->ppu_mem[ppu->vram_addr + 0x800] = *addr;
            else if ((ppu->vram_addr >= 0x2800) && (ppu->vram_addr < 0x2C00)) ppu->ppu_mem[ppu->vram_addr - 0x800] = *addr;
            else ppu->ppu_mem[ppu->vram_addr - 0x800] = *addr;
        }
        else {
            if ((ppu->vram_addr >= 0x2000) && (ppu->vram_addr < 0x2400)) ppu->ppu_mem[ppu->vram_addr + 0x400] = *addr;
            else if ((ppu->vram_addr >= 0x2400) && (ppu->vram_addr < 0x2800)) ppu->ppu_mem[ppu->vram_addr - 0x400] = *addr;
            else if ((ppu->vram_addr >= 0x2800) && (ppu->vram_addr < 0x2C00)) ppu->ppu_mem[ppu->vram_addr + 0x400] = *addr;
            else ppu->ppu_mem[ppu->vram_addr - 0x400] = *addr;
        }
    }
}