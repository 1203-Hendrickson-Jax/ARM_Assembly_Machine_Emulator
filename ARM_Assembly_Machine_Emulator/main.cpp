//Author: Jax hendrickson
//Date: 12/1/2023
//Purpose: To design a machine language model that can emulate an ARM assembly machine. 
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

struct MachineState { //To implement each of the registers.
    std::map<std::string, uint32_t> registers = {{"R0", 0}, {"R1", 0}, {"R2", 0}, {"R3", 0}, {"R4", 0}, {"R5", 0}, {"R6", 0}, {"R7", 0}, {"R8", 0}, {"R9", 0}, {"R10", 0}, {"R11", 0}, {"R12", 0}, {"SP", 0}, {"LR", 0}, {"PC", 0}};
    uint32_t flags = 0;
};

void parseRegister(const std::string& regStr, std::string& registerName, bool& hasComma) { //To go through the registers at the end of each operation.
    registerName = "";
    hasComma = false;
    size_t commaPos = regStr.find(',');
    if (commaPos != std::string::npos) {
        registerName = regStr.substr(0, commaPos);
        hasComma = true;
    } else {
        registerName = regStr;
        hasComma = false;
    }
}

void printState(const std::map<std::string, uint32_t>& registers, uint32_t flags) { //To print the state of the registers and flags at the end of each operation.
    for (int i = 0; i <= 7; ++i) {
        std::string regName = "R" + std::to_string(i);
        std::cout << regName << ": " << "0x" << std::hex << registers.at(regName) << " ";
    }
    std::cout << std::endl;
    std::cout << "N = " << ((flags >> 31) & 1) << " Z = " << ((flags >> 30) & 1) << " C = " << ((flags >> 29) & 1) << " V = " << ((flags >> 28) & 1) << std::endl;
}

void executeInstruction(MachineState& state, const std::string& opcode, const std::string& destRegister, const std::string& srcRegister1, const std::string& srcRegister2, uint32_t immediate, uint32_t shiftAmount) { //Carries the logic to preform each of the operations. 
    uint32_t operand1 = state.registers[srcRegister1];
    uint32_t operand2 = state.registers[srcRegister2];
    uint32_t result = 0;
    if (opcode == "MOV" || opcode == "MOVS") {
        result = immediate;
    } else if (opcode == "ADD" || opcode == "ADDS") {
        result = operand1 + operand2;
    } else if (opcode == "SUB" || opcode == "SUBS") {
        result = operand1 - operand2;
    } else if (opcode == "AND" || opcode == "ANDS") {
        result = operand1 & operand2;
    } else if (opcode == "ORR" || opcode == "ORRS") {
        result = operand1 | operand2;
    } else if (opcode == "XOR" || opcode == "XORS") {
        result = operand1 ^ operand2;
    } else if (opcode == "LSL" || opcode == "LSLS") {
        result = operand1 << shiftAmount;
    } else if (opcode == "LSR" || opcode == "LSRS") {
        result = operand1 >> shiftAmount;
    } else if (opcode == "NOT" || opcode == "NOTS") {
        result = ~operand1;
    }
    state.registers[destRegister] = result;
    state.flags &= ~(1 << 31); // Clear N flag
    state.flags &= ~(1 << 30); // Clear Z flag
    state.flags &= ~(1 << 29); // Clear C flag
    state.flags &= ~(1 << 28); // Clear V flag

    if (result & (1u << 31)) {
        state.flags |= (1 << 31); 
    }

    if (result == 0) {
        state.flags |= (1 << 30); 
    }

    if (opcode.back() == 'S') {
        if (opcode == "ADDS" || opcode == "LSLS") {
            if (operand2 > 0 && shiftAmount > 0) {
                state.flags |= (1 << 29); 
            }
        }
        if ((operand1 > INT32_MAX - operand2) || (operand1 + operand2 > INT32_MAX)) {
            state.flags |= (1 << 28); 
        }
    }
}

int main() { //The main function: reads the file into each register, and goes through the insert.txt file to handle each operation, then output it. 
    MachineState state;
    std::ifstream inputFile("insert.txt");
    if (!inputFile.is_open()) {
        std::cout << "Error opening the file." << std::endl;
        return 1;
    }
    std::string line, opcode, destRegister, srcRegister1, srcRegister2;
    uint32_t immediate, shiftAmount;
    bool hasComma;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        iss >> opcode;
        std::transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
        if (opcode == "MOV" || opcode == "MOVS") {
            iss >> destRegister >> std::hex >> immediate;
            executeInstruction(state, opcode, destRegister, "", "", immediate, 0);
        } else {
            parseRegister(destRegister, destRegister, hasComma);
            parseRegister(srcRegister1, srcRegister1, hasComma);
            parseRegister(srcRegister2, srcRegister2, hasComma);

            if (hasComma) {
                iss >> shiftAmount;
                executeInstruction(state, opcode, destRegister, srcRegister1, srcRegister2, 0, shiftAmount);
            } else {
                executeInstruction(state, opcode, destRegister, srcRegister1, srcRegister2, 0, 0);
            }
        }
        printState(state.registers, state.flags);
    }
    inputFile.close();
    return 0;
}