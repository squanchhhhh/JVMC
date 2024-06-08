//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_CLASS_FILE_H
#define JVMC_CLASS_FILE_H
#include "common_classfile_struct.h"
#include "member_info.h"
typedef struct ClassFile ClassFile;
typedef struct MemberInfo MemberInfo;
MemberInfo * get_main_method(ClassFile*class_file);
void readAndCheckMagic(ClassFile *cf, ClassReader *reader);

void readAndCheckVersion(ClassFile *cf, ClassReader *reader);

ClassFile *parseClassFile(const uint8_t *classData, size_t size);
ClassFile * loadClassFile(char*class_name);
#endif //JVMC_CLASS_FILE_H