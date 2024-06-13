//
// Created by Squanch on 2024/6/3.
//

#include "object.h"

Object *new_object(Class *pClass) {
    Object *pObject = malloc(sizeof(Object));
    pObject->class = pClass;
    pObject->slots = new_local_vars(pClass->instance_slot_count);
    return pObject;
}

void set_ref_var(Object *self, char *name, char *descriptor, Object *ref) {
    RtFields *field = get_field_rt(self->class, name, descriptor, 0);
    LocalVars *var = self->slots;
    set_ref(var, field->slot_id, ref);
}
Object *get_ref_var(Object *self, char *name, char *descriptor) {
    RtFields *field = get_field_rt(self->class, name, descriptor, 0);
    LocalVars *var = self->slots;
    return get_ref(var, field->slot_id);
}

size_t utf16_strlen(const uint16_t *str) {
    size_t len = 0;
    while (str[len] != 0) {
        len++;
    }
    return len;
}

Object *new_chars_object(Class *pClass, char *str) {
    Object *pObject = malloc(sizeof(Object));
    pObject->class = pClass;
    pObject->data_type = TYPE_CHAR_ARRAY;
    pObject->data = str;
    pObject->length = utf16_strlen(str);
    return pObject;
}

int is_instance_of(Object *ref, Class *pClass) {
    return ref->class == pClass;
}


int8_t *bytes(Object *obj) {
    if (obj->data_type != TYPE_INT8_ARRAY) {
        fprintf(stderr, "Not a int8 array!\n");
        exit(1);
    }
    return (int8_t *) obj->data;
}

int16_t *shorts(Object *obj) {
    if (obj->data_type != TYPE_INT16_ARRAY) {
        fprintf(stderr, "Not a int16 array!\n");
        exit(1);
    }
    return (int16_t *) obj->data;
}


int32_t *ints(Object *obj) {
    if (obj->data_type != TYPE_INT32_ARRAY) {
        fprintf(stderr, "Not a int32 array!\n");
        exit(1);
    }
    return (int32_t *) obj->data;
}

int64_t *longs(Object *obj) {
    if (obj->data_type != TYPE_INT64_ARRAY) {
        fprintf(stderr, "Not a int64 array!\n");
        exit(1);
    }
    return (int64_t *) obj->data;
}

int16_t *chars(Object *obj) {
    if (obj->data_type != TYPE_CHAR_ARRAY) {
        fprintf(stderr, "Not a char array!\n");
        exit(1);
    }
    return (int16_t *) obj->data;
}

float *floats(Object *obj) {
    if (obj->data_type != TYPE_FLOAT32_ARRAY) {
        fprintf(stderr, "Not a float32 array!\n");
        exit(1);
    }
    return (float *) obj->data;
}

double *doubles(Object *obj) {
    if (obj->data_type != TYPE_FLOAT64_ARRAY) {
        fprintf(stderr, "Not a float64 array!\n");
        exit(1);
    }
    return (double *) obj->data;
}

Object **refs(Object *obj) {
    if (obj->data_type != TYPE_OBJECT_ARRAY) {
        fprintf(stderr, "Not a ref array!\n");
        exit(1);
    }
    return (Object **) obj->data;
}

int32_t arrayLength(Object *obj) {
    return obj->length;
}

Object *new_array(Class *class, uint32_t count) {
    if (!isArrayClass(class)) {
        fprintf(stderr, "Not array class: %s\n", class->name);
        exit(1);
    }

    Object *obj = (Object *) malloc(sizeof(Object));
    obj->class = class;

    if (strcmp(class->name, "[Z") == 0 || strcmp(class->name, "[B") == 0) {
        obj->data = (int8_t *) malloc(sizeof(int8_t) * count);
        obj->data_type = TYPE_INT8_ARRAY;
    } else if (strcmp(class->name, "[C") == 0) {
        obj->data = (uint16_t *) malloc(sizeof(uint16_t) * count);
        obj->data_type = TYPE_CHAR_ARRAY;
    } else if (strcmp(class->name, "[S") == 0) {
        obj->data = (int16_t *) malloc(sizeof(int16_t) * count);
        obj->data_type = TYPE_INT16_ARRAY;

    } else if (strcmp(class->name, "[I") == 0) {
        obj->data = (int32_t *) malloc(sizeof(int32_t) * count);
        obj->data_type = TYPE_INT32_ARRAY;
    } else if (strcmp(class->name, "[J") == 0) {
        obj->data = (int64_t *) malloc(sizeof(int64_t) * count);
        obj->data_type = TYPE_INT64_ARRAY;
    } else if (strcmp(class->name, "[F") == 0) {
        obj->data = (float *) malloc(sizeof(float) * count);
        obj->data_type = TYPE_FLOAT32_ARRAY;
    } else if (strcmp(class->name, "[D") == 0) {
        obj->data = (double *) malloc(sizeof(double) * count);
        obj->data_type = TYPE_FLOAT64_ARRAY;
    } else {
        obj->data = (Object **) malloc(sizeof(Object *) * count);
        obj->data_type = TYPE_OBJECT_ARRAY;
    }
    obj->length = count;
    return obj;
}