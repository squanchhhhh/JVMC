//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_CLASS_READER_H
#define JVMC_CLASS_READER_H
#include <stdint.h>
#include <stdlib.h>
#include "common_classfile_struct.h"


ClassReader* create_class_reader(const uint8_t *data, size_t size);
void destroy_class_reader(ClassReader *reader);

uint8_t read_uint8_class(ClassReader *reader);
uint16_t read_uint16_class(ClassReader *reader);
uint32_t read_uint32_class(ClassReader *reader);
uint64_t read_uint64_class(ClassReader *reader);
uint16_t* read_uint16s_class(ClassReader *reader);
uint8_t* read_bytes_class(ClassReader *reader, uint32_t length);

#endif //JVMC_CLASS_READER_H
