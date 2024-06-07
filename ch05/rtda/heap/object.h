//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_OBJECT_H
#define JVMC_OBJECT_H
#include "class.h"

typedef struct{
    Class *class;
    LocalVars slots;
}Object;

#endif //JVMC_OBJECT_H
