//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_BYTECODE_READER_H
#define JVMC_BYTECODE_READER_H
#include <stdint.h>
typedef struct BytecodeReader{
    uint8_t* code;
    int pc;
} BytecodeReader;
void reset(BytecodeReader* reader, unsigned char * code, int pc);
uint8_t read_uint8(BytecodeReader* reader);
uint16_t read_uint16(BytecodeReader* reader);
int8_t read_int8(BytecodeReader* reader);
int16_t read_int16(BytecodeReader* reader);
int32_t read_int32(BytecodeReader* reader);
void skip_padding(BytecodeReader* reader);


#endif //JVMC_BYTECODE_READER_H