//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_CLASS_FILE_H
#define JVMC_CLASS_FILE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "class_reader.h"
#include "constant_pool.h"
#include "attr_info.h"
#include "member_info.h"


typedef struct {
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    ConstantPool *constant_pool;
    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;
    uint16_t interfaces_count;
    uint16_t *interfaces;
    uint16_t fields_count;
    MemberInfo **fields;
    uint16_t methods_count;
    MemberInfo **methods;
    uint16_t attributes_count;
    AttributeInfo **attributes;
} ClassFile;

void readAndCheckMagic(ClassFile *cf, ClassReader *reader);

void readAndCheckVersion(ClassFile *cf, ClassReader *reader);

ClassFile *parseClassFile(const uint8_t *classData, size_t size);

#endif //JVMC_CLASS_FILE_H