/*
ログ出力を行うためのファイル
*/
#include <fstream>
#include <iomanip>
#include <sstream>
#include <map>
#include <iostream>

#include "nes_manager.h"

std::ofstream logfile("log.txt");

struct Instruction {
    std::string mnemonic;
    std::string mode;
};

std::map<uint8_t, Instruction> opcode_map = {
    {0x00, {"BRK", "IMP"}}, {0x01, {"ORA", "IZX"}}, {0x05, {"ORA", "ZP0"}},
    {0x06, {"ASL", "ZP0"}}, {0x08, {"PHP", "IMP"}}, {0x09, {"ORA", "IMM"}},
    {0x0A, {"ASL", "ACC"}}, {0x0D, {"ORA", "ABS"}}, {0x0E, {"ASL", "ABS"}},

    {0x10, {"BPL", "REL"}}, {0x11, {"ORA", "IZY"}}, {0x15, {"ORA", "ZPX"}},
    {0x16, {"ASL", "ZPX"}}, {0x18, {"CLC", "IMP"}}, {0x19, {"ORA", "ABY"}},
    {0x1D, {"ORA", "ABX"}}, {0x1E, {"ASL", "ABX"}},

    {0x20, {"JSR", "ABS"}}, {0x21, {"AND", "IZX"}}, {0x24, {"BIT", "ZP0"}},
    {0x25, {"AND", "ZP0"}}, {0x26, {"ROL", "ZP0"}}, {0x28, {"PLP", "IMP"}},
    {0x29, {"AND", "IMM"}}, {0x2A, {"ROL", "ACC"}}, {0x2C, {"BIT", "ABS"}},
    {0x2D, {"AND", "ABS"}}, {0x2E, {"ROL", "ABS"}},

    {0x30, {"BMI", "REL"}}, {0x31, {"AND", "IZY"}}, {0x35, {"AND", "ZPX"}},
    {0x36, {"ROL", "ZPX"}}, {0x38, {"SEC", "IMP"}}, {0x39, {"AND", "ABY"}},
    {0x3D, {"AND", "ABX"}}, {0x3E, {"ROL", "ABX"}},

    {0x40, {"RTI", "IMP"}}, {0x41, {"EOR", "IZX"}}, {0x45, {"EOR", "ZP0"}},
    {0x46, {"LSR", "ZP0"}}, {0x48, {"PHA", "IMP"}}, {0x49, {"EOR", "IMM"}},
    {0x4A, {"LSR", "ACC"}}, {0x4C, {"JMP", "ABS"}}, {0x4D, {"EOR", "ABS"}},
    {0x4E, {"LSR", "ABS"}},

    {0x50, {"BVC", "REL"}}, {0x51, {"EOR", "IZY"}}, {0x55, {"EOR", "ZPX"}},
    {0x56, {"LSR", "ZPX"}}, {0x58, {"CLI", "IMP"}}, {0x59, {"EOR", "ABY"}},
    {0x5D, {"EOR", "ABX"}}, {0x5E, {"LSR", "ABX"}},

    {0x60, {"RTS", "IMP"}}, {0x61, {"ADC", "IZX"}}, {0x65, {"ADC", "ZP0"}},
    {0x66, {"ROR", "ZP0"}}, {0x68, {"PLA", "IMP"}}, {0x69, {"ADC", "IMM"}},
    {0x6A, {"ROR", "ACC"}}, {0x6C, {"JMP", "IND"}}, {0x6D, {"ADC", "ABS"}},
    {0x6E, {"ROR", "ABS"}},

    {0x70, {"BVS", "REL"}}, {0x71, {"ADC", "IZY"}}, {0x75, {"ADC", "ZPX"}},
    {0x76, {"ROR", "ZPX"}}, {0x78, {"SEI", "IMP"}}, {0x79, {"ADC", "ABY"}},
    {0x7D, {"ADC", "ABX"}}, {0x7E, {"ROR", "ABX"}},

    {0x81, {"STA", "IZX"}}, {0x84, {"STY", "ZP0"}}, {0x85, {"STA", "ZP0"}},
    {0x86, {"STX", "ZP0"}}, {0x88, {"DEY", "IMP"}}, {0x8A, {"TXA", "IMP"}},
    {0x8C, {"STY", "ABS"}}, {0x8D, {"STA", "ABS"}}, {0x8E, {"STX", "ABS"}},

    {0x90, {"BCC", "REL"}}, {0x91, {"STA", "IZY"}}, {0x94, {"STY", "ZPX"}},
    {0x95, {"STA", "ZPX"}}, {0x96, {"STX", "ZPY"}}, {0x98, {"TYA", "IMP"}},
    {0x99, {"STA", "ABY"}}, {0x9A, {"TXS", "IMP"}}, {0x9D, {"STA", "ABX"}},

    {0xA0, {"LDY", "IMM"}}, {0xA1, {"LDA", "IZX"}}, {0xA2, {"LDX", "IMM"}},
    {0xA4, {"LDY", "ZP0"}}, {0xA5, {"LDA", "ZP0"}}, {0xA6, {"LDX", "ZP0"}},
    {0xA8, {"TAY", "IMP"}}, {0xA9, {"LDA", "IMM"}}, {0xAA, {"TAX", "IMP"}},
    {0xAC, {"LDY", "ABS"}}, {0xAD, {"LDA", "ABS"}}, {0xAE, {"LDX", "ABS"}},

    {0xB0, {"BCS", "REL"}}, {0xB1, {"LDA", "IZY"}}, {0xB4, {"LDY", "ZPX"}},
    {0xB5, {"LDA", "ZPX"}}, {0xB6, {"LDX", "ZPY"}}, {0xB8, {"CLV", "IMP"}},
    {0xB9, {"LDA", "ABY"}}, {0xBA, {"TSX", "IMP"}}, {0xBD, {"LDA", "ABX"}},

    {0xC0, {"CPY", "IMM"}}, {0xC1, {"CMP", "IZX"}}, {0xC4, {"CPY", "ZP0"}},
    {0xC5, {"CMP", "ZP0"}}, {0xC6, {"DEC", "ZP0"}}, {0xC8, {"INY", "IMP"}},
    {0xC9, {"CMP", "IMM"}}, {0xCA, {"DEX", "IMP"}}, {0xCC, {"CPY", "ABS"}},
    {0xCD, {"CMP", "ABS"}}, {0xCE, {"DEC", "ABS"}},

    {0xD0, {"BNE", "REL"}}, {0xD1, {"CMP", "IZY"}}, {0xD5, {"CMP", "ZPX"}},
    {0xD6, {"DEC", "ZPX"}}, {0xD8, {"CLD", "IMP"}}, {0xD9, {"CMP", "ABY"}},
    {0xDD, {"CMP", "ABX"}}, {0xDE, {"DEC", "ABX"}},

    {0xE0, {"CPX", "IMM"}}, {0xE1, {"SBC", "IZX"}}, {0xE4, {"CPX", "ZP0"}},
    {0xE5, {"SBC", "ZP0"}}, {0xE6, {"INC", "ZP0"}}, {0xE8, {"INX", "IMP"}},
    {0xE9, {"SBC", "IMM"}}, {0xEA, {"NOP", "IMP"}}, {0xEC, {"CPX", "ABS"}},
    {0xED, {"SBC", "ABS"}}, {0xEE, {"INC", "ABS"}},

    {0xF0, {"BEQ", "REL"}}, {0xF1, {"SBC", "IZY"}}, {0xF5, {"SBC", "ZPX"}},
    {0xF6, {"INC", "ZPX"}}, {0xF8, {"SED", "IMP"}}, {0xF9, {"SBC", "ABY"}},
    {0xFD, {"SBC", "ABX"}}, {0xFE, {"INC", "ABX"}},
};

std::string decode(uint8_t opcode, uint8_t op1, uint8_t op2) {
    std::ostringstream oss;
    if (opcode_map.find(opcode) == opcode_map.end()) {
        oss << "???";
        return oss.str();
    }

    Instruction inst = opcode_map[opcode];
    oss << inst.mnemonic << " ";

    std::ostringstream operand;
    operand << std::uppercase << std::hex << std::setfill('0');

    if (inst.mode == "IMM") {
        operand << "#$" << std::setw(2) << (int)op1;
    }
    else if (inst.mode == "ZP0") {
        operand << "$" << std::setw(2) << (int)op1;
    }
    else if (inst.mode == "ABS") {
        uint16_t addr = op1 + ((uint16_t)op2 << 8);
        operand << "$" << std::setw(4) << addr;
    }
    else if (inst.mode == "IMP") {
        operand.str("");
    }
    else {
        operand << "??";
    }

    oss << operand.str();
    return oss.str();
}

void log_cpu_state(CPU_Emulator* cpu, NES_Manager* mgr) {
    uint16_t pc_before = cpu->PC;
    uint8_t opcode = cpu->cpu_mem[pc_before];
    uint8_t op1 = cpu->cpu_mem[pc_before + 1];
    uint8_t op2 = cpu->cpu_mem[pc_before + 2];
    std::string asm_str = decode(opcode, op1, op2);
    std::ostringstream line;

    line << std::hex << std::uppercase << std::setfill('0');
    line << "$" << std::setw(4) << pc_before << "  ";

    line << std::setw(2) << (int)opcode << " ";
    line << std::setw(2) << (int)op1 << " ";
    line << std::setw(2) << (int)op2 << "   ";

    line << std::left << std::setw(30) << asm_str;

    line << "A:" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(cpu->A & 0xFF);
    line << "X:" << std::setw(2) << (cpu->X & 0xFF) << " ";
    line << "Y:" << std::setw(2) << (cpu->Y & 0xFF) << " ";

    uint8_t P = (cpu->N << 7) | (cpu->V << 6) | (1 << 5) | (cpu->B << 4) | (cpu->D << 3) | (cpu->I << 2) | (cpu->Z << 1) | (cpu->C);
    line << "P:" << std::setw(2) << (P & 0xFF) << " ";

    line << "SP:" << std::setw(2) << (cpu->SP & 0xFF) << " ";

    line << "CYC:" << std::dec << mgr->cycle;

    logfile << line.str() << "\n";
}
