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

void readAndCheckMagic(ClassFile *cf, ClassReader *reader);

void readAndCheckVersion(ClassFile *cf, ClassReader *reader);

ClassFile *parseClassFile(const uint8_t *classData, size_t size);

#endif //JVMC_CLASS_FILE_H