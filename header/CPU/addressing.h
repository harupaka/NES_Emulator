#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"

uint8_t* Immidiate(CPU_Emulator*);
uint8_t* Absolute(CPU_Emulator*);
uint8_t* ZeroPage(CPU_Emulator*);
uint8_t* IndexZeroPage(CPU_Emulator*, uint8_t);
uint8_t* IndexAbsolute(CPU_Emulator*, uint8_t);
uint8_t* Relative(CPU_Emulator*);
uint8_t* XIndirect(CPU_Emulator*);
uint8_t* YIndirect(CPU_Emulator*);
uint8_t* AbsoluteIndirect(CPU_Emulator*);