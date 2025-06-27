#pragma once

#include "nes_manager.h"
#include <string>

void Load(NES_Emulator*, uint8_t*, const std::string);
void make_CHR(uint8_t*, uint8_t*);