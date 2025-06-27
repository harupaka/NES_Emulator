#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "nes_manager.h"

void ADC(NES_Emulator*, uint8_t*);
void SBC(NES_Emulator*, uint8_t*);
void AND(NES_Emulator*, uint8_t*);
void ORA(NES_Emulator*, uint8_t*);
void EOR(NES_Emulator*, uint8_t*);
void ASL(NES_Emulator*, uint8_t*);
void LSR(NES_Emulator*, uint8_t*);
void ROL(NES_Emulator*, uint8_t*);
void ROR(NES_Emulator*, uint8_t*);
void BIT(NES_Emulator*, uint8_t*);
void JMP(NES_Emulator*, uint8_t*);
void CMP(NES_Emulator*, uint8_t*);
void CPX(NES_Emulator*, uint8_t*);
void CPY(NES_Emulator*, uint8_t*);
void INC(NES_Emulator*, uint8_t*);
void DEC(NES_Emulator*, uint8_t*);
void LDA(NES_Emulator*, uint8_t*);
void LDX(NES_Emulator*, uint8_t*);
void LDY(NES_Emulator*, uint8_t*);
void STA(NES_Emulator*, uint8_t*);
void STX(NES_Emulator*, uint8_t*);
void STY(NES_Emulator*, uint8_t*);

void LAX(NES_Emulator*, uint8_t*);
void SAX(NES_Emulator*, uint8_t*);
void DCP(NES_Emulator*, uint8_t*);
void ISC(NES_Emulator*, uint8_t*);
void SLO(NES_Emulator*, uint8_t*);
void RLA(NES_Emulator*, uint8_t*);
void SRE(NES_Emulator*, uint8_t*);
void RRA(NES_Emulator*, uint8_t*);