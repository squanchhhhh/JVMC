//
// Created by Squanch on 2024/6/3.
//

#include "object.h"
Object * new_object(Class *pClass){
    Object *pObject = malloc(sizeof(Object));
    pObject->class = pClass;
    pObject->slots = new_local_vars(pClass->instance_slot_count);
    return pObject;
}
int is_instance_of(Object*ref,Class *pClass){
    return ref->class == pClass;
}