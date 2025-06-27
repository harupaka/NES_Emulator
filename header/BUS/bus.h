#pragma once
#include "nes_manager.h"

void write_data(NES_Emulator*, uint8_t*, uint8_t);
uint8_t read_data(NES_Emulator*, uint8_t*);