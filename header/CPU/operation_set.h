#pragma once

#include <stdbool.h>

#include "nes_manager.h"

void init_operations(void);

typedef unsigned int operation_func_t(NES_Emulator*);

extern operation_func_t* operations[256];