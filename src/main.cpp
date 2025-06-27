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

const std::string CARTRIDGE = "2048";

static NES_Manager* create_mgr() {
    NES_Manager* mgr = new NES_Manager;
    mgr->Reset = false;
    mgr->error = false;
    mgr->NMIpin = true;
    mgr->IRQpin = true;

    mgr->cycle = 0;

    return mgr;
}

//CPU�쐬
static CPU_Emulator* create_cpu() {
    CPU_Emulator* cpu = new CPU_Emulator;
    cpu->cpu_mem = new uint8_t[256*256];
    memset(cpu->cpu_mem, 0, 256 * 256);

    //������
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

//PPU�쐬
static PPU_Emulator* create_ppu() {
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

//�R���g���[���[�쐬
static Controller_Emulator* create_controller() {
    Controller_Emulator* controller = new Controller_Emulator;
    controller->signal = false;
    controller->trigger = false;
    controller->reg = 0;

    controller->index = 1;
    return controller;
}

static NES_Emulator* create_nes(CPU_Emulator* cpu, PPU_Emulator* ppu, NES_Manager* mgr, Controller_Emulator* controller) {
    NES_Emulator* nes = new NES_Emulator;
    nes->Cpu = cpu;
    nes->Ppu = ppu;
    nes->Mgr = mgr;
    nes->Con = controller;

    return nes;
}

static Screen* create_screen() {
    Screen* canvas = new Screen;
    canvas->screen = new uint8_t[256*240];
    memset(canvas->screen, 0, 256 * 240);
    canvas->line = 0;

    canvas->complete = false;
    canvas->drawing = false;
    return canvas;
}

//確保したメモリの解放
static void destroy_nes(CPU_Emulator* cpu, PPU_Emulator* ppu, NES_Manager* mgr, NES_Emulator* nes, Screen* canvas) {
    delete[] cpu->cpu_mem;
    delete cpu;
    delete[] ppu->ppu_mem;
    delete[] ppu->sprite;
    delete[] ppu->OAM_buffer;
    delete[] ppu->bank;
    delete ppu;
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

    destroy_nes(nes->Cpu, nes->Ppu, nes->Mgr, nes, canvas);
    delete_display();
    delete[] index_chr;

    SDL_Quit();

    return 0;

}

