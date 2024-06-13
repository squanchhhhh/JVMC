//
// Created by Squanch on 2024/6/13.
//

#ifndef JVMC_STRING_POOL_H
#define JVMC_STRING_POOL_H
#include "class.h"
#include "object.h"
typedef struct Object Object;
typedef struct StringPool StringPool;

extern StringPool *internedStrings;
Object* find_interned_string(const char *str);
uint16_t* utf8_to_utf16(const char *utf8_str);
Object* create_java_string(ClassLoader *loader ,const char *str);
char* to_c_string(Object*ref);
char* utf16_to_utf8(const uint16_t* utf16_str, size_t utf16_len);

#endif //JVMC_STRING_POOL_H
