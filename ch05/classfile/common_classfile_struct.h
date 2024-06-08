//
// Created by Squanch on 2024/6/6.
//

#ifndef JVMC_COMMON_CLASSFILE_STRUCT_H
#define JVMC_COMMON_CLASSFILE_STRUCT_H
#define CODE 1
#define CONSTANT_VALUE 2
#include "class_reader.h"
#include "constant_pool.h"
#include <string.h>
#include "class_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <libc.h>
#include "class_reader.h"
#include "attr_info.h"
/**
 * 存放结构体,防止冲突
 */
typedef struct ClassFile ClassFile;
typedef struct ClassReader ClassReader;
typedef struct FieldInfo FieldInfo;
//constant
typedef struct ConstantPool ConstantPool;
typedef struct ConstantInfo ConstantInfo;
typedef struct ConstantFloatInfo ConstantFloatInfo;
typedef struct ConstantIntegerInfo ConstantIntegerInfo;
typedef struct ConstantLongInfo ConstantLongInfo;
typedef struct ConstantDoubleInfo ConstantDoubleInfo;
typedef struct ConstantUtf8Info ConstantUtf8Info;
typedef struct ConstantNameAndTypeInfo ConstantNameAndTypeInfo;
typedef struct ConstantMethodHandleInfo ConstantMethodHandleInfo;
typedef struct ConstantMethodTypeInfo ConstantMethodTypeInfo;
typedef struct ConstantStringInfo ConstantStringInfo;
typedef struct ConstantMethodRefInfo ConstantMethodRefInfo;
typedef struct ConstantFieldRefInfo ConstantFieldRefInfo;
typedef struct ConstantInterfaceMethodRefInfo ConstantInterfaceMethodRefInfo;
typedef struct ConstantInvokeDynamicInfo ConstantInvokeDynamicInfo;
typedef struct ConstantClassInfo ConstantClassInfo;
//attributes
typedef struct AttributeInfo AttributeInfo;
typedef struct UnparsedAttributeInfo UnparsedAttributeInfo;
typedef struct CodeAttributeInfo CodeAttributeInfo;
typedef struct LineNumberTable LineNumberTable;
typedef struct LineNumberTableAttribute LineNumberTableAttribute;
typedef struct SourceFileAttribute SourceFileAttribute;
typedef struct StackMapTableAttributeInfo StackMapTableAttributeInfo;
typedef struct StackMapTableEntry StackMapTableEntry;
typedef struct ConstantValueAttribute ConstantValueAttribute;
typedef struct ExceptionTableEntry ExceptionTableEntry;
typedef struct LocalVariableTableEntry LocalVariableTableEntry;
typedef struct SignatureAttributeInfo SignatureAttributeInfo;
typedef struct ExceptionAttribute ExceptionAttribute;

typedef struct MemberInfo MemberInfo;


struct ClassReader{
    const uint8_t *data;
    size_t size;
    size_t index;
};
struct ConstantInfo {
    uint8_t tag;
    void (*read_info)(void *self, ClassReader *reader);
};

struct ConstantPool {
    ConstantInfo **constants;
    int index;
    int count;
};
struct ConstantFloatInfo{
    ConstantInfo base;
    float value;
};
struct ConstantIntegerInfo{
    ConstantInfo base;
    int32_t value;
};
struct ConstantLongInfo{
    ConstantInfo base;
    int64_t value;
};
struct ConstantDoubleInfo{
    ConstantInfo base;
    double value;
};
struct ConstantUtf8Info{
    ConstantInfo base;
    char * str;
};
struct ConstantStringInfo{
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t string_index;
};
struct ConstantClassInfo{
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t name_index;
};
struct ConstantNameAndTypeInfo{
    ConstantInfo base;
    uint16_t name_index;
    uint16_t descriptor_index;
};
struct ConstantInterfaceMethodRefInfo{
    ConstantInfo base;
    ConstantPool *pool;
    uint16_t class_index;
    uint16_t name_and_type_index;
} ;


/**
 * 为了保证实现多态的效果，这里的ConstantInfo不能使用指针
 * 如果使用指针会导致类型强转时无法读取到base的信息
 */
struct ConstantMethodRefInfo{
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t class_index;
    uint16_t name_and_type_index;
};
struct ConstantFieldRefInfo{
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t class_index;
    uint16_t name_and_type_index;
};
struct AttributeInfo{
    void (*read_info)(void* ,ClassReader *);
    int type;
};
//Signature_attribute {
//    u2 attribute_name_index;
//    u4 attribute_length;
//    u2 signature_index;
//}
struct SignatureAttributeInfo{
    AttributeInfo base;
    uint16_t signature_index;
    //todo 临时保存属性信息
    uint8_t* temp_store;
    uint16_t attribute_name_index;
};
struct ExceptionAttribute{
    AttributeInfo base;
    uint8_t * temp_store;
};
struct ExceptionTableEntry{
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
};

struct StackMapTableEntry{
    uint8_t frame_type;
    uint16_t offset;
    uint8_t * locals;
};
struct StackMapTableAttributeInfo{
    AttributeInfo base;
    uint16_t number_of_entries;
    //临时保存frame
    uint8_t * contents;
    StackMapTableEntry ** entries;
};

struct UnparsedAttributeInfo{
    AttributeInfo base;
    char* name;
    uint32_t len;
    uint8_t * info;
};
struct CodeAttribute{
    AttributeInfo base;
    ConstantPool * pool;
    uint16_t max_stack;
    uint16_t max_locals;
    uint8_t * code;
    ExceptionTableEntry ** exception_table;
    AttributeInfo ** attributes;
};
struct LineNumberTable{
    uint16_t start_pc;
    uint16_t line_number;
};

struct LineNumberTableAttribute{
    AttributeInfo base;
    LineNumberTable ** lines;
};
struct SourceFileAttribute{
    AttributeInfo base;
    ConstantPool *pool;
    uint16_t source_file_index;
};
struct ConstantValueAttribute{
    AttributeInfo base;
    uint16_t constant_value_index;
};
struct MemberInfo{
    ConstantPool * pool;
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    AttributeInfo ** attributes;
    int count;
};

struct ClassFile {
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
};

#endif //JVMC_COMMON_CLASSFILE_STRUCT_H
