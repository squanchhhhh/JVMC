//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_OBJECT_H
#define JVMC_OBJECT_H
#include "class.h"
typedef struct Class Class;
typedef struct Object Object;
typedef struct LocalVars LocalVars;

Object *get_ref_var(Object *self, char *name, char *descriptor);
void set_ref_var(Object *self, char *name, char *descriptor, Object *ref);
Object * new_object(Class *pClass);
Object * new_chars_object(Class *pClass,uint16_t * str);
//todo 有点复杂的判断方法
int is_instance_of(Object*ref,Class *pClass);

int8_t* bytes(Object *obj);
int16_t* shorts(Object *obj);
int32_t* ints(Object *obj);
int64_t* longs(Object *obj);
float* floats(Object *obj);
double* doubles(Object *obj);
uint16_t * chars(Object *obj);
Object**refs(Object *obj);
int32_t arrayLength(Object *obj);
Object* new_array(Class *class, uint32_t count);
#endif //JVMC_OBJECT_H
