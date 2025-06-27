#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"

uint8_t* fetch(CPU_Emulator*, uint16_t);
void push(CPU_Emulator*, uint8_t);
uint8_t pop(CPU_Emulator*);
void Interrupt_Stuck(CPU_Emulator*);