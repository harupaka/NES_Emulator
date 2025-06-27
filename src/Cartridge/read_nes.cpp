/*
主に.nesファイルの読み込みとメインループ前の下処理
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdint.h>
#include <stdbool.h>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "nes_manager.h"

//スプライトの色情報を作成
static void make_sprite(uint8_t* mem, uint8_t* sprite, uint8_t index) {
    const uint8_t* chr = mem + index * 16;
    memset(sprite, 0, 64);

    for (int y = 0; y < 8; y++) {
        uint8_t low  = chr[y];
        uint8_t high = chr[y + 8];

        for (int x = 0; x < 8; x++) {
            int bit = 7 - x;
            uint8_t value = ((low >> bit) & 1) | (((high >> bit) & 1) << 1);
            sprite[y * 8 + x] = value;
        }
    }
}

void make_CHR(uint8_t* index_chr, uint8_t* mem) {
    uint8_t sprite[64];

    for (int i = 0; i < 512; i++) {
        make_sprite(mem, index_chr + i * 64, i);
    }
}

void Load(NES_Emulator* nes, uint8_t* index_chr, const std::string name) {
    CPU_Emulator* cpu = nes->Cpu;
    PPU_Emulator* ppu = nes->Ppu;
    NES_Manager* mgr = nes->Mgr;
    FILE* fp;

    std::string path = "./NES/" + name + ".nes";
    errno_t err = fopen_s(&fp, path.c_str(), "rb+");
    if (err != 0 || fp == nullptr) {
        printf(".nes file not open");
        mgr->error = true;
        return;
    }

    //ヘッダー読み込み
    uint8_t header[16];
    fread(header, sizeof(uint8_t), 16, fp);

    uint8_t size_PRG;
    uint8_t size_CHR;
    uint8_t mirroring;

    size_PRG = header[4];
    printf("size_PRG:%x\n", size_PRG);
    size_CHR = header[5];
    printf("size_CHR:%x\n", size_CHR);
    if (size_CHR >= 9) {
        printf("The CHR-ROM size is too large.");
        mgr->error = true;
        fclose(fp);
        return;
    }
    mirroring = header[6];

    //PRGを書き込み
    if (size_PRG == 1) {
        fread(cpu->cpu_mem + 0xC000, sizeof(uint8_t), 16384, fp);
        memcpy(cpu->cpu_mem + 0x8000, cpu->cpu_mem + 0xC000, 16384);
    }
    else if (size_PRG == 2) {
        fread(cpu->cpu_mem + 0x8000, sizeof(uint8_t), 16384, fp);
        fread(cpu->cpu_mem + 0xC000, sizeof(uint8_t), 16384, fp);
    }
    else {
        printf("The PRG-ROM size is too large.");
        mgr->error = true;
        fclose(fp);
        return;
    }

    //CHRを書き込み
    for (unsigned int j = 0; j < (unsigned int)size_CHR; j++) {
        fread(ppu->bank + (0x2000 * j), sizeof(uint8_t), 8192, fp);
        if (j == 0) {
            memcpy(ppu->ppu_mem, ppu->bank, 8192);
        }
    }

    make_CHR(index_chr, ppu->ppu_mem);

    //ネームテーブルのミラーリング方法の確認
    ppu->Nametable_arrangement = (bool)(mirroring & 0b00000001);
    if(ppu->Nametable_arrangement) printf("Vertical arrangement\n");
    else printf("Horizontal arrangement\n");

    //マッパーの確認
    ppu->mapper = ((mirroring & 0b11110000) >> 4) | (header[7] & 0b11110000);
    printf("Mapper %d ", ppu->mapper);
    if(ppu->mapper == 0) printf("NROM");
    else if(ppu->mapper == 1) printf("MMC1");
    else if(ppu->mapper == 2) printf("UNROM");
    else if(ppu->mapper == 3) printf("CNROM");
    else if(ppu->mapper == 4) printf("MMC3");
    printf("\n");

    fclose(fp);

}