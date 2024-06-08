//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_OBJECT_H
#define JVMC_OBJECT_H
#include "class.h"

typedef struct{
    Class *class;
    LocalVars *slots;
}Object;

Object * new_object(Class *pClass);
//todo 有点复杂的判断方法
int is_instance_of(Object*ref,Class *pClass);

#endif //JVMC_OBJECT_H
