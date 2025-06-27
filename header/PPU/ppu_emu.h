#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"

PPU_Emulator* create_ppu();
void PPU(NES_Emulator*, Screen*, uint8_t*, unsigned int);
void ppu_addr_write(NES_Emulator*);
void ppu_addr_inc(NES_Emulator*);
void mirroring(NES_Emulator*, uint8_t*);