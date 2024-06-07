//
// Created by Squanch on 2024/6/6.
//

#ifndef JVMC_COMMON_H
#define JVMC_COMMON_H
#define CODE 1
/**
 * 存放结构体,防止冲突
 */
typedef struct ConstantPool ConstantPool;
typedef struct ConstantInfo ConstantInfo;
typedef struct {
    const uint8_t *data;
    size_t size;
    size_t index;
} ClassReader;
struct ConstantInfo {
    uint8_t tag;
    void (*read_info)(void *self, ClassReader *reader);
};

struct ConstantPool {
    ConstantInfo **constants;
    int index;
    int count;
};
typedef struct {
    ConstantInfo base;
    float value;
}ConstantFloatInfo;
typedef struct {
    ConstantInfo base;
    int32_t value;
} ConstantIntegerInfo;
typedef struct{
    void (*read_info)(void* ,ClassReader *);
    int type;
}AttributeInfo;
typedef struct{
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
}ExceptionTableEntry;

typedef struct{
    uint8_t frame_type;
    uint16_t offset;
    uint8_t * locals;
}StackMapTableEntry;
typedef struct{
    AttributeInfo base;
    uint16_t number_of_entries;
    //临时保存frame
    uint8_t * contents;
    StackMapTableEntry ** entries;
}StackMapTableAttributeInfo;

typedef struct{
    AttributeInfo base;
    char* name;
    uint32_t len;
    uint8_t * info;
}UnparsedAttributeInfo;
typedef struct{
    AttributeInfo base;
    ConstantPool * pool;
    uint16_t max_stack;
    uint16_t max_locals;
    uint8_t * code;
    ExceptionTableEntry ** exception_table;
    AttributeInfo ** attributes;
}CodeAttribute;
typedef struct{
    uint16_t start_pc;
    uint16_t line_number;
}lineNumberTable;

typedef struct{
    AttributeInfo base;
    lineNumberTable ** lines;
}LineNumberTableAttribute;
typedef struct{
    AttributeInfo base;
    ConstantPool *pool;
    uint16_t source_file_index;
}SourceFileAttribute;

typedef struct{
    ConstantPool * pool;
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    AttributeInfo ** attributes;
    int count;
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
