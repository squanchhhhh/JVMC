//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_ATTR_INFO_H
#define JVMC_ATTR_INFO_H
#include "class_reader.h"
#include "constant_pool.h"
#include "common.h"
#include <string.h>
#define STRCMP(s1, s2) (strcmp((s1), (s2)) == 0)

AttributeInfo *new_attribute_info(char*name,uint32_t len,ConstantPool * pool);
AttributeInfo * read_attribute(ClassReader * reader,ConstantPool*pool);
AttributeInfo **read_attributes(ClassReader *reader, ConstantPool *pool, MemberInfo *member);


ExceptionTableEntry ** read_exception_table(ClassReader *reader);


void read_unparsed_attribute_info(void*self,ClassReader * reader);
void init_unparsed_attribute_info(UnparsedAttributeInfo *self,ClassReader * reader);


void read_code_attribute(void *self,ClassReader * reader);
void init_code_attribute(CodeAttribute *self,ClassReader * reader);


void read_line_number_attribute(void *self,ClassReader * reader);
void init_line_number_attribute(LineNumberTableAttribute *self,ClassReader * reader);

void read_source_file_attribute(void *self,ClassReader * reader);
void init_source_file_attribute(SourceFileAttribute *self,ClassReader * reader);
#endif //JVMC_ATTR_INFO_H
