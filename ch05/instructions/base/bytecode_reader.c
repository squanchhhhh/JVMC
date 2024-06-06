//
// Created by Squanch on 2024/6/3.
//

#include "bytecode_reader.h"
void reset(BytecodeReader* reader,unsigned char * code, int pc) {
    reader->code = code;
    reader->pc = pc;
}

uint8_t read_uint8(BytecodeReader* reader) {
    uint8_t i = reader->code[reader->pc];
    reader->pc++;
    return i;
}

int8_t read_int8(BytecodeReader* reader) {
    return (int8_t)read_uint8(reader);
}

uint16_t read_uint16(BytecodeReader* reader) {
    uint16_t byte1 = (uint16_t)read_uint8(reader);
    uint16_t byte2 = (uint16_t)read_uint8(reader);
    return (byte1 << 8) | byte2;
}

int16_t read_int16(BytecodeReader* reader) {
    return (int16_t)read_uint16(reader);
}

int32_t read_int32(BytecodeReader* reader) {
    int32_t byte1 = (int32_t)read_uint8(reader);
    int32_t byte2 = (int32_t)read_uint8(reader);
    int32_t byte3 = (int32_t)read_uint8(reader);
    int32_t byte4 = (int32_t)read_uint8(reader);
    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

//跳过某些指令后面的padding
void skip_padding(BytecodeReader* reader){
    for (;reader->pc % 4 != 0;){
        read_int8(reader);
    }
}