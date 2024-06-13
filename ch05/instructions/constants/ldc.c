//
// Created by Squanch on 2024/6/8.
//

#include "ldc.h"

void _ldc(Frame *frame, uint32_t index) {
    OperandStack *stack = frame->operand_stack;
    Class *class = frame->method->base->class;
    RtConstantPool *pool = class->constant_pool;
    RtConstantInfo *info = get_constant_info(pool, index);
    switch (info->tag) {
        case CONSTANT_Integer:
            push_int(stack, info->value.intValue);
            break;
        case CONSTANT_Float:
            push_float(stack, info->value.floatValue);
            break;
        case CONSTANT_Long:
            push_long(stack, info->value.longValue);
            break;
        case CONSTANT_Double:
            push_double(stack, info->value.doubleValue);
            break;
        case CONSTANT_String: {
            Object *ref = create_java_string(class->loader, info->value.stringValue);
            push_ref(stack, ref);
            break;
        }
        case CONSTANT_Class:
            printf("push class\n");
            break;
        default:
            printf("push other\n");
            exit(1);
    }
}

void init_LDC(LDC *self) {
    Index8_instruction_init(&self->base);
    self->base.base.Execute = execute_LDC;
}

void execute_LDC(void *self, Frame *frame) {
    LDC *ldc = (LDC *) self;
    _ldc(frame, ldc->base.index);
}

void init_LDC_W(LDC_W *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_LDC_W;
}

void execute_LDC_W(void *self, Frame *frame) {
    LDC_W *ldc = (LDC_W *) self;
    _ldc(frame, ldc->base.index);
}

void init_LDC2_W(LDC2_W *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_LDC2_W;
}

void execute_LDC2_W(void *self, Frame *frame) {
    LDC2_W *ldc = (LDC2_W *) self;
    OperandStack *stack = frame->operand_stack;
    RtConstantPool *pool = frame->method->base->class->constant_pool;
    RtConstantInfo *info = get_constant_info(pool, ldc->base.index);
    switch (info->tag) {
        case CONSTANT_Long:
            push_long(stack, info->value.longValue);
            break;
        case CONSTANT_Double:
            push_double(stack, info->value.doubleValue);
            break;
        default:
            printf("ldc2_w\n");
            exit(1);
    }
}