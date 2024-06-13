//
// Created by Squanch on 2024/6/13.
//

#include "system.h"

void arraycopy(Frame *frame) {
    LocalVars *localVars = frame->local_vars;
    Object *src = get_ref(localVars, 0);
    int src_pos = get_int(localVars, 1);
    Object *dest = get_ref(localVars, 2);
    int dest_pos = get_int(localVars, 3);
    int length = get_int(localVars, 4);
    if (src == NULL || dest == NULL) {
        printf("java.lang.NullPointerException");
        exit(1);
    }
    if (src_pos < 0 || dest_pos < 0 || length < 0 ||
        src_pos + length > src->length || dest_pos + length > dest->length) {
        printf("java.lang.ArrayIndexOutOfBoundsException\n");
        exit(1);
    }

    //todo 判断是否能够拷贝
    //typedef enum {
    //    TYPE_INT8_ARRAY,
    //    TYPE_INT16_ARRAY,
    //    TYPE_INT32_ARRAY,
    //    TYPE_INT64_ARRAY,
    //    TYPE_CHAR_ARRAY,
    //    TYPE_FLOAT32_ARRAY,
    //    TYPE_FLOAT64_ARRAY,
    //    TYPE_OBJECT_ARRAY
    //} DataType;
    switch (src->data_type) {
        case TYPE_INT8_ARRAY: {
            int8_t *src_array = (int8_t *) src->data;
            int8_t *dest_array = (int8_t *) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }
        case TYPE_INT16_ARRAY: {
            int16_t *src_array = (int16_t *) src->data;
            int16_t *dest_array = (int16_t *) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }
        case TYPE_INT32_ARRAY: {
            int32_t *src_array = (int32_t *) src->data;
            int32_t *dest_array = (int32_t *) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }
        case TYPE_INT64_ARRAY: {
            int64_t *src_array = (int64_t *) src->data;
            int64_t *dest_array = (int64_t *) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }
        case TYPE_CHAR_ARRAY: {
            int16_t *src_array = (int16_t *) src->data;
            int16_t *dest_array = (int16_t *) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }
        case TYPE_FLOAT32_ARRAY: {
            float *src_array = (float *) src->data;
            float *dest_array = (float *) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }
        case TYPE_FLOAT64_ARRAY: {
            double *src_array = (double *) src->data;
            double *dest_array = (double *) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }
        case TYPE_OBJECT_ARRAY: {
            Object **src_array = (Object **) src->data;
            Object **dest_array = (Object **) dest->data;
            for (int i = 0; i < length; ++i) {
                dest_array[dest_pos + i] = src_array[src_pos + i];
            }
            break;
        }


    }
}

int float_to_raw_int_bits(float value) {
    int bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

void floatToRawIntBits(Frame *frame) {
    float value = get_float(frame->local_vars, 0);
    int bits = float_to_raw_int_bits(value);
    push_int(frame->operand_stack, bits);
}

long long double_to_raw_long_bits(double value) {
    long long bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

void doubleToRawLongBits(Frame *frame) {
    double value = get_double(frame->local_vars, 0);
    long long bits = double_to_raw_long_bits(value);
    push_long(frame->operand_stack, bits);
}

void intern(Frame *frame) {
    Object *ref = get_ref(frame->local_vars, 0);
    Object *r = intern_string(ref);
    push_ref(frame->operand_stack, r);
}


void init() {
    register_("java/lang/System", "arraycopy",
              "(Ljava/lang/Object;ILjava/lang/Object;II)V", arraycopy);
    register_("java/lang/Float",
              "floatToRawIntBits", "(F)I", floatToRawIntBits);
    register_("java/lang/Double",
              "doubleToRawLongBits", "(D)J", doubleToRawLongBits);
    register_("java/lang/String",
              "intern", "()Ljava/lang/String;", intern);
}
