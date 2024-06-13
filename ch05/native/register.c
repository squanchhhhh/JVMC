//
// Created by Squanch on 2024/6/13.
//

#include "register.h"
void empty_native_method(Frame *frame) {
    // Do nothing
}
NativeMethodEntry *registry = NULL;
void register_(const char *className, const char *methodName, const char *methodDescriptor, NativeMethod method) {
    NativeMethodEntry *entry = malloc(sizeof(NativeMethodEntry));
    if (entry == NULL) {
        perror("Failed to allocate memory for NativeMethodEntry");
        exit(EXIT_FAILURE);
    }

    entry->class_name = strdup(className);
    entry->method_name = strdup(methodName);
    entry->method_descriptor = strdup(methodDescriptor);
    entry->method = method;
    entry->next = registry;  // 将新节点插入到链表头部
    registry = entry;
}

NativeMethod find_native_method(const char *className, const char *methodName, const char *methodDescriptor) {
    NativeMethodEntry *current = registry;
    while (current != NULL) {
        if (strcmp(current->class_name, className) == 0 &&
            strcmp(current->method_name, methodName) == 0 &&
            strcmp(current->method_descriptor, methodDescriptor) == 0) {
            return current->method;
        }
        current = current->next;
    }

    // 特殊处理 registerNatives 方法
    if (strcmp(methodDescriptor, "()V") == 0 && strcmp(methodName, "registerNatives") == 0) {
        return empty_native_method;
    }

    return NULL;
}