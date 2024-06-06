//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_ATTR_INFO_H
#define JVMC_ATTR_INFO_H
#include "class_reader.h"
#include "constant_pool.h"
#include <string.h>
#define STRCMP(s1, s2) (strcmp((s1), (s2)) == 0)
typedef struct{
    void (*read_info)(void* ,ClassReader *);
}AttributeInfo;
AttributeInfo * new_attribute_info(char*name,uint32_t len,ConstantPool * pool);
AttributeInfo * read_attribute(ClassReader * reader,ConstantPool*pool);
AttributeInfo ** read_attributes(ClassReader *reader, ConstantPool* pool);
typedef struct{
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
}ExceptionTableEntry;
ExceptionTableEntry ** read_exception_table(ClassReader *reader);

typedef struct{
    char* name;
    uint32_t len;
    uint8_t * info;
    AttributeInfo *base;
}UnparsedAttributeInfo;
void read_unparsed_attribute_info(void*self,ClassReader * reader);
void init_unparsed_attribute_info(UnparsedAttributeInfo *self,ClassReader * reader);

typedef struct{
    ConstantPool * pool;
    uint16_t max_stack;
    uint16_t max_locals;
    uint8_t * code;
    ExceptionTableEntry ** exception_table;
    AttributeInfo ** attributes;
    AttributeInfo *base;
}CodeAttribute;
void read_code_attribute(void *self,ClassReader * reader);
void init_code_attribute(CodeAttribute *self,ClassReader * reader);


#endif //JVMC_ATTR_INFO_H
