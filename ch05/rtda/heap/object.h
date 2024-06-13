//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_OBJECT_H
#define JVMC_OBJECT_H
#include "class.h"
typedef struct Class Class;
typedef struct Object Object;
typedef struct LocalVars LocalVars;

typedef enum {
    TYPE_SLOTS,
    TYPE_INT8_ARRAY,
    TYPE_INT16_ARRAY,
    TYPE_INT32_ARRAY,
    TYPE_INT64_ARRAY,
    TYPE_CHAR_ARRAY,
    TYPE_FLOAT32_ARRAY,
    TYPE_FLOAT64_ARRAY,
    TYPE_OBJECT_ARRAY
} DataType;

struct Object{
    Class *class;
    LocalVars *slots;

    //为数组类准备的额外字段
    void *data;
    DataType data_type;
};

Object * new_object(Class *pClass);
//todo 有点复杂的判断方法
int is_instance_of(Object*ref,Class *pClass);

int8_t* bytes(Object *obj);
int16_t* shorts(Object *obj);
int32_t* ints(Object *obj);
int64_t* longs(Object *obj);
float* floats(Object *obj);
double* doubles(Object *obj);
char* chars(Object *obj);
Object* refs(Object *obj);
int32_t arrayLength(Object *obj);
Object* newArray(Class *class, uint32_t count);
#endif //JVMC_OBJECT_H
