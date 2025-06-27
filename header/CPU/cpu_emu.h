#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"

CPU_Emulator* create_cpu();
unsigned int CPU(NES_Emulator*);