//
// Created by Squanch on 2024/6/6.
//

#ifndef JVMC_COMMON_H
#define JVMC_COMMON_H
/**
 * 存放结构体,防止冲突
 */
typedef struct{
    ConstantPool * pool;
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    AttributeInfo ** attributes;
}MemberInfo;

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
#endif //JVMC_COMMON_H
