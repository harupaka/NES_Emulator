#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdint.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include <SDL.h>

#include "nes_manager.h"
#include "cpu_emu.h"
#include "operation_set.h"
#include "ppu_emu.h"
#include "read_nes.h"
#include "coloring.h"
#include "interrupt.h"
#include "log.h"
#include "controller.h"

#define SDL_MAIN_HANDLED

const std::string CARTRIDGE = "nestest";

static NES_Manager* create_mgr() {
    NES_Manager* mgr = new NES_Manager;
    mgr->Reset = false;
    mgr->error = false;
    mgr->NMIpin = true;
    mgr->IRQpin = true;

    mgr->cycle = -1;

    return mgr;
}

static NES_Emulator* create_nes(CPU_Emulator* cpu, PPU_Emulator* ppu, NES_Manager* mgr, Controller_Emulator* controller) {
    NES_Emulator* nes = new NES_Emulator;
    nes->Cpu = cpu;
    nes->Ppu = ppu;
    nes->Mgr = mgr;
    nes->Con = controller;

    return nes;
}

//確保したメモリの解放
static void destroy_nes(CPU_Emulator* cpu, PPU_Emulator* ppu, Controller_Emulator* con, NES_Manager* mgr, NES_Emulator* nes, Screen* canvas) {
    delete[] cpu->cpu_mem;
    delete cpu;
    delete[] ppu->ppu_mem;
    delete[] ppu->sprite;
    delete[] ppu->OAM_buffer;
    delete[] ppu->bank;
    delete ppu;
    delete con;
    delete mgr;
    delete nes;
    delete[] canvas->screen;
    delete canvas;
}

int main(int, char*[]) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    //各メモリの確保
    NES_Manager* mgr = create_mgr();
    CPU_Emulator* cpu = create_cpu();
    PPU_Emulator* ppu = create_ppu();
    Controller_Emulator* con = create_controller();
    NES_Emulator* nes = create_nes(cpu, ppu, mgr, con);
    Screen* canvas = create_screen();

    uint8_t* index_chr = new uint8_t[512 * 64]();

    make_display();

    init_operations();

    //.nesファイルの読み込み
    Load(nes, index_chr, CARTRIDGE);
    
    Uint32 last_draw = SDL_GetTicks();
    unsigned int clock;

    RESET(nes->Cpu);

    //メインループ
    while (1) {
        if (mgr->Reset) {
            RESET(nes->Cpu);
            break;
        }

        //ログ出力
        //log_cpu_state(cpu, mgr);

        clock = CPU(nes);

        PPU(nes, canvas, index_chr, clock);

        controller(nes);

        if ((canvas->complete) && (canvas->drawing)) {
            Uint32 now = SDL_GetTicks();
            if (now - last_draw >= 16) {
                coloring(canvas);
                canvas->drawing = false;
                last_draw = now;
            }
        }
        
        if (mgr->error == true) {
            printf("error\n");
            break;
        }
    }

    destroy_nes(nes->Cpu, nes->Ppu, nes->Con, nes->Mgr, nes, canvas);
    delete_display();
    delete[] index_chr;

    SDL_Quit();

    return 0;

}

