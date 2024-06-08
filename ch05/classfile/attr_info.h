//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_ATTR_INFO_H
#define JVMC_ATTR_INFO_H


#include "common_classfile_struct.h"
typedef struct UnparsedAttributeInfo UnparsedAttributeInfo;
typedef struct CodeAttribute CodeAttribute;
typedef struct ExceptionTableEntry ExceptionTableEntry;
typedef struct AttributeInfo AttributeInfo;
typedef struct LineNumberTable LineNumberTable;
typedef struct LineNumberTableAttribute LineNumberTableAttribute;
typedef struct SourceFileAttribute SourceFileAttribute;
typedef struct StackMapTableAttributeInfo StackMapTableAttributeInfo;
typedef struct StackMapTableAttributeInfo StackMapTableAttributeInfo;
typedef struct StackMapTableEntry StackMapTableEntry;
typedef struct ConstantValueAttribute ConstantValueAttribute;
typedef struct SignatureAttributeInfo SignatureAttributeInfo;
typedef struct ExceptionAttribute ExceptionAttribute;
typedef struct DeprecatedAttribute DeprecatedAttribute;
typedef struct MemberInfo MemberInfo;
#define STRCMP(s1, s2) (strcmp((s1), (s2)) == 0)

AttributeInfo *new_attribute_info(char *name, uint32_t len, ConstantPool *pool,ClassReader*reader);

AttributeInfo *read_attribute(ClassReader *reader, ConstantPool *pool);

AttributeInfo **read_attributes(ClassReader *reader, ConstantPool *pool, MemberInfo *member);


ExceptionTableEntry **read_exception_table(ClassReader *reader);


void read_unparsed_attribute_info(void *self, ClassReader *reader);

void init_unparsed_attribute_info(UnparsedAttributeInfo *self, ClassReader *reader,int len);


void read_code_attribute(void *self, ClassReader *reader);

void init_code_attribute(CodeAttribute *self, ClassReader *reader);


void read_line_number_attribute(void *self, ClassReader *reader);

void init_line_number_attribute(LineNumberTableAttribute *self, ClassReader *reader);

void read_source_file_attribute(void *self, ClassReader *reader);

void init_source_file_attribute(SourceFileAttribute *self, ClassReader *reader);

void init_signature_attribute(SignatureAttributeInfo *self,ClassReader * reader,int len);
void read_signature_attribute(void *self,ClassReader * reader);

void read_exception_attribute(void *self, ClassReader *reader);

void init_exception_attribute(ExceptionAttribute *self, ClassReader *reader,int len);

void read_stack_map_table_entrys(StackMapTableAttributeInfo * info ,ClassReader *reader);

StackMapTableEntry *read_stack_map_table_entry(ClassReader *reader);
void read_constant_value_attribute(void* self, ClassReader *reader);

void init_constant_value_attribute(ConstantValueAttribute *self, ClassReader *reader);

void read_stack_map_table_attribute(void *self,ClassReader * reader);

void init_stack_map_table_attribute(StackMapTableAttributeInfo *self,ClassReader * reader,int len);

void init_deprecated_attribute(DeprecatedAttribute * self, ClassReader * reader);

void read_deprecated_attribute(void *self, ClassReader *reader);
#endif //JVMC_ATTR_INFO_H
