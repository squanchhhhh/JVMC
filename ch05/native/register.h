//
// Created by Squanch on 2024/6/13.
//

#ifndef JVMC_REGISTER_H
#define JVMC_REGISTER_H

#include "../instructions/base/instruction.h"

typedef void (*NativeMethod)(Frame *frame);

// 链表节点结构体
typedef struct NativeMethodEntry {
    char *class_name;
    char *method_name;
    char *method_descriptor;
    NativeMethod method;
    struct NativeMethodEntry *next;
} NativeMethodEntry;
// 定义本地方法类型

void empty_native_method(Frame *frame);

void register_(const char *className, const char *methodName, const char *methodDescriptor, NativeMethod method);
NativeMethod find_native_method(const char *className, const char *methodName, const char *methodDescriptor);


// 链表头指针
extern NativeMethodEntry *registry;
#endif //JVMC_REGISTER_H
