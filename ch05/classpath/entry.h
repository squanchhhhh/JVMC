//
// Created by Squanch on 2024/6/4.
//

#ifndef JVMC_ENTRY_H
#define JVMC_ENTRY_H
#include <stddef.h>
#include <libc.h>
//路径分隔符默认使用linux/mac
#define PATH_SEPARATOR :
// 定义 Entry 结构体
typedef struct Entry Entry;

struct Entry {
    void (*readClass)(void* self, const char* className, unsigned char** data, size_t* length, int* err);
    char* (*toString)(void* self);
};
int contains(const char* str,char c);
int has_suffix(const char* str,const char* suffix);

typedef struct {
    Entry * base;
    char* abs_path;
}DirEntry;
void dir_entry_read_class(void* self, const char* className, unsigned char** data, size_t* length, int* err);

// todo other entry
typedef struct {
    Entry * base;
    char* abs_path;
}ZipEntry;

//匹配多路径    xxx/xxx:xxx/xxx
typedef struct {
    Entry * base;
}CompositeEntry;

//匹配通配符    xxx/*
typedef struct {
    Entry * base;
}WildCardEntry;

#endif //JVMC_ENTRY_H
