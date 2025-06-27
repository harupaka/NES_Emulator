#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"

void InterruptFunction(CPU_Emulator*, bool*, bool*);
void RESET(CPU_Emulator*);