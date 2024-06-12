//
// Created by Squanch on 2024/6/7.
//

#ifndef JVMC_COMMON_RTDA_STRUCT_H
#define JVMC_COMMON_RTDA_STRUCT_H

#include "../classfile/common_classfile_struct.h"
#include "../all_class_headers.h"

#include "thread.h"

typedef struct Class Class;
typedef struct ClassLoader ClassLoader;
typedef struct RtConstantPool RtConstantPool;
typedef struct RtFields RtFields;
typedef struct RtMember RtMember;
typedef struct RtMethods RtMethods;
typedef struct RtConstantInfo RtConstantInfo;
typedef struct SymRef SymRef;
typedef struct ClassRef ClassRef;
typedef struct MethodRef MethodRef;
typedef struct FieldRef FieldRef;
typedef struct InterfaceMethodRef InterfaceMethodRef;
typedef struct MethodDescriptor MethodDescriptor;
typedef struct MethodDescriptorParser MethodDescriptorParser;
//accessflags
#define ACC_PUBLIC 0x0001 // class field method
#define ACC_PRIVATE 0x0002 // field method
#define ACC_PROTECTED 0x0004 // field method
#define ACC_STATIC 0x0008 // field method
#define ACC_FINAL 0x0010 // class field method
#define ACC_SUPER 0x0020 // class
#define ACC_SYNCHRONIZED 0x0020 // method
#define ACC_VOLATILE 0x0040 // field
#define ACC_BRIDGE 0x0040 // method
#define ACC_TRANSIENT 0x0080 // field
#define ACC_VARARGS 0x0080 // method
#define ACC_NATIVE 0x0100 // method
#define ACC_INTERFACE 0x0200 // class
#define ACC_ABSTRACT 0x0400 // class method
#define ACC_STRICT 0x0800 // method
#define ACC_SYNTHETIC 0x1000 // class field method
#define ACC_ANNOTATION 0x2000 // class
#define ACC_ENUM 0x4000 // class field

typedef struct LocalVars LocalVars;
struct Class {
    uint16_t access_flags;
    char *name;
    char *super_name;
    char **interface_names;
    RtConstantPool *constant_pool;
    uint32_t fields_count;
    RtFields **fields;
    uint32_t methods_count;
    RtMethods **methods;
    ClassLoader *loader;
    Class *super_class;
    Class **interfaces;
    uint32_t interfaces_count;
    uint32_t instance_slot_count;
    uint32_t static_slot_count;
    LocalVars *static_vars;
};
struct RtConstantPool {
    Class *class;
    uint16_t constants_count;
    RtConstantInfo **constants;
};
struct RtMember {
    uint16_t access_flags;
    char *name;
    char *descriptor;
    Class *class;
};
typedef union {
    int intValue;
    float floatValue;
    long longValue;
    double doubleValue;
    char *stringValue;
    FieldRef *fieldRef;
    MethodRef *methodRef;
    ClassRef *classRef;
    InterfaceMethodRef *interfaceMethodRef;
} ConstantValue;

struct RtFields {
    RtMember *base;
    uint32_t slot_id;
    uint32_t constant_value_index;
};

struct RtMethods {
    RtMember *base;
    uint32_t max_stack;
    uint32_t max_locals;
    uint8_t *code;
    uint32_t arg_slots_count;
};

struct MethodDescriptor {
    char **parameter_type;
    int parameter_count;
    char *return_type;
};

struct MethodDescriptorParser {
    const char *raw;
    int offset;
    MethodDescriptor *parsed;
};

struct RtConstantInfo {
    int tag;
    ConstantValue value;
};

struct SymRef {
    char *class_name;
    Class *class;
    RtConstantPool *pool;
};

struct MethodRef {
    SymRef base;
    char *name;
    char *descriptor;
    RtMethods *methods;
};
struct FieldRef {
    SymRef base;
    char *name;
    char *descriptor;
    RtFields *fields;
};
struct InterfaceMethodRef {
    SymRef base;
    char *name;
    char *descriptor;
    RtMethods *methods;
};
struct ClassRef {
    SymRef base;
};


/*
 * 用两个数组存储类加载器的信息
 */
struct ClassLoader {
    char **names;
    Class **classes;
    int size;                // 大小
};

#endif //JVMC_COMMON_RTDA_STRUCT_H
