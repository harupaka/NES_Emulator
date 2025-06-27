/*
コントローラーに関する処理
*/
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "nes_manager.h"

Controller_Emulator* create_controller() {
    Controller_Emulator* controller = new Controller_Emulator;
    controller->signal = false;
    controller->trigger = false;
    controller->reg = 0;

    controller->index = 1;
    return controller;
}

void controller(NES_Emulator* nes) {
	CPU_Emulator* cpu = nes->Cpu;
	NES_Manager* mgr = nes->Mgr;
    Controller_Emulator* con = nes->Con;
	SDL_Event e;

    if (!con->signal) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                bool pressed = (e.type == SDL_KEYDOWN);

                switch (e.key.keysym.sym) {
                case SDLK_RETURN:
                    if (pressed)
                        con->reg |= 0b00000001;
                    else
                        con->reg &= ~0b00000001;
                    break;
                case SDLK_RSHIFT:
                    if (pressed)
                        con->reg |= 0b00000010;
                    else
                        con->reg &= ~0b00000010;
                    break;
                case SDLK_1:
                    if (pressed)
                        con->reg |= 0b00000100;
                    else
                        con->reg &= ~0b00000100;
                    break;
                case SDLK_2:
                    if (pressed)
                        con->reg |= 0b00001000;
                    else
                        con->reg &= ~0b00001000;
                    break;
                case SDLK_w:
                    if (pressed)
                        con->reg |= 0b00010000;
                    else
                        con->reg &= ~0b00010000;
                    break;
                case SDLK_s:
                    if (pressed)
                        con->reg |= 0b00100000;
                    else
                        con->reg &= ~0b00100000;
                    break;
                case SDLK_a:
                    if (pressed)
                        con->reg |= 0b01000000;
                    else
                        con->reg &= ~0b01000000;
                    break;
                case SDLK_d:
                    if (pressed)
                        con->reg |= 0b10000000;
                    else
                        con->reg &= ~0b10000000;
                    break;
                case SDLK_SPACE:
                    if (pressed)
                        mgr->Reset = true;
                    break;
                }
            }
        }
    }
}