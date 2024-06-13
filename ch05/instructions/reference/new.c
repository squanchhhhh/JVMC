//
// Created by Squanch on 2024/6/8.
//

#include "new.h"

void init_NEW(NEW *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_NEW;
}

void execute_NEW(void *self_, Frame *frame) {
    NEW *self = (NEW *) self_;
    RtConstantPool *pool = frame->method->base->class->constant_pool;
    ClassRef *class_ref = get_constant_info(pool, self->base.index)->value.classRef;
    Class *c = resolve_classes(&class_ref->base);
    //如果类没有被初始化
    if (!c->initialized){
        revert_next_pc(frame);
        init_class(frame->thread,c);
        return ;
    }
    if (is_abstract(c) || is_interface(c)) {
        printf("java.lang.InstantiationError\n");
        exit(1);
    }
    Object *ref = new_object_by_class(c);
    push_ref(frame->operand_stack, ref);
}

void init_PUT_STATIC(PUT_STATIC *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_PUT_STATIC;
}

void execute_PUT_STATIC(void *self_, Frame *frame) {
    PUT_STATIC *self = (PUT_STATIC *) self_;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base->class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base->class;
    if (!is_static_field(f)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    if (is_final_field(f)) {
        if (current_class != c && current_class->name[0] != '<') {//"<clinit>"
            printf("java.lang.IllegalAccessError\n");
            exit(1);
        }
    }
    char *d = f->base->descriptor;
    int slot_id = f->slot_id;
    LocalVars *l = c->static_vars;
    OperandStack *o = frame->operand_stack;
    switch (d[0]) {
        case 'Z':

        case 'B':

        case 'C':

        case 'S':

        case 'I':
            set_int(l, slot_id, pop_int(o));
            break;
        case 'F':
            set_float(l, slot_id, pop_float(o));
            break;
        case 'J':
            set_long(l, slot_id, pop_long(o));
            break;
        case 'D':
            set_double(l, slot_id, pop_double(o));
            break;
        case 'L':
        case '[':
            set_ref(l, slot_id, pop_ref(o));
            break;
        default:
            printf("java.lang.IncompatibleClassChangeError1\n");
            exit(1);
    }
}

void init_GET_STATIC(GET_STATIC *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_GET_STATIC;
}

void execute_GET_STATIC(void *self, Frame *frame) {
    GET_STATIC *self_ = (GET_STATIC *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base->class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self_->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base->class;
    if (!is_static_field(f)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    char *d = f->base->descriptor;
    int slot_id = f->slot_id;
    LocalVars *l = c->static_vars;
    OperandStack *o = frame->operand_stack;
    switch (d[0]) {
        case 'Z':

        case 'B':

        case 'C':

        case 'S':

        case 'I':
            push_int(o, get_int(l, slot_id));
            break;
        case 'F':
            push_float(o, get_float(l, slot_id));
            break;
        case 'J':
            push_long(o, get_long(l, slot_id));
            break;
        case 'D':
            push_double(o, get_double(l, slot_id));
            break;
        case 'L':
        case '[':
            push_ref(o, get_ref(l, slot_id));
            break;
        default:
            printf("java.lang.IncompatibleClassChangeError2\n");
            exit(1);
    }
}

void init_PUT_FIELD(PUT_FIELD *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_PUT_FIELD;
}

void execute_PUT_FIELD(void *self, Frame *frame) {
    PUT_FIELD *self_ = (PUT_FIELD *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base->class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self_->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base->class;
    if (is_static_field(f)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    if (is_final_field(f)) {
        if (current_class != c && current_class->name[0] != '<') {//"<clinit>"
            printf("java.lang.IllegalAccessError\n");
            exit(1);
        }
    }
    char *d = f->base->descriptor;
    int slot_id = f->slot_id;
    OperandStack *o = frame->operand_stack;
    switch (d[0]) {
        case 'Z':

        case 'B':

        case 'C':

        case 'S':

        case 'I': {
            int val = pop_int(o);
            Object *ref = pop_ref(o);
            if (ref == NULL) {
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_int(ref->slots, slot_id, val);
        }
            break;
        case 'F': {
            float val = pop_float(o);
            Object *ref = pop_ref(o);
            if (ref == NULL) {
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_float(ref->slots, slot_id, val);
        }
            break;
        case 'J': {
            long val = pop_long(o);
            Object *ref = pop_ref(o);
            if (ref == NULL) {
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_long(ref->slots, slot_id, val);
        }
        case 'D': {
            double val = pop_double(o);
            Object *ref = pop_ref(o);
            if (ref == NULL) {
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_double(ref->slots, slot_id, val);
        }
            break;
        case 'L':
        case '[': {
            Object *val = pop_ref(o);
            Object *ref = pop_ref(o);
            if (ref == NULL) {
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_ref(ref->slots, slot_id, val);
        }
            break;
        default:
            printf("java.lang.IncompatibleClassChangeError3\n");
            exit(1);
    }
}

void init_GET_FIELD(GET_FIELD *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_GET_FIELD;
}

void execute_GET_FIELD(void *self, Frame *frame) {
    GET_FIELD *self_ = (GET_FIELD *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base->class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self_->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base->class;
    if (is_static_field(f)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    char *d = f->base->descriptor;
    int slot_id = f->slot_id;
    LocalVars *l = c->static_vars;
    OperandStack *o = frame->operand_stack;
    switch (d[0]) {
        case 'Z':

        case 'B':

        case 'C':

        case 'S':

        case 'I':
            push_int(o, get_int(l, slot_id));
            break;
        case 'F':
            push_float(o, get_float(l, slot_id));
            break;
        case 'J':
            push_long(o, get_long(l, slot_id));
            break;
        case 'D':
            push_double(o, get_double(l, slot_id));
            break;
        case 'L':
        case '[':
            push_ref(o, get_ref(l, slot_id));
            break;
        default:
            printf("java.lang.IncompatibleClassChangeError4\n");
            exit(1);
    }
}

void init_INSTANCE_OF(INSTANCE_OF *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_INSTANCE_OF;
}

void execute_INSTANCE_OF(void *self, Frame *frame) {
    INSTANCE_OF *self_ = (INSTANCE_OF *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base->class;
    RtConstantPool *pool = current_class->constant_pool;
    ClassRef *classRef = get_constant_info(pool, self_->base.index)->value.classRef;
    Class *c = resolve_classes(&classRef->base);
    OperandStack *o = frame->operand_stack;
    Object *ref = pop_ref(o);
    if (ref == NULL) {
        push_int(o, 0);
        return;
    }
    push_int(o, is_instance_of(ref, c));
}

void init_CHECK_CAST(CHECK_CAST *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_CHECK_CAST;
}

void execute_CHECK_CAST(void *self, Frame *frame) {
    CHECK_CAST *self_ = (CHECK_CAST *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base->class;
    RtConstantPool *pool = current_class->constant_pool;
    ClassRef *classRef = get_constant_info(pool, self_->base.index)->value.classRef;
    Class *c = resolve_classes(&classRef->base);
    OperandStack *o = frame->operand_stack;
    Object *ref = pop_ref(o);
    if (ref == NULL) {
        printf("java.lang.NullPointerException\n");
        exit(1);
    }
    if (!is_instance_of(ref, c)) {
        printf("java.lang.ClassCastException\n");
        exit(1);
    }
}

void init_NEW_ARRAY(NEW_ARRAY *self){
    self->base.Execute = execute_NEW_ARRAY;
    self->base.FetchOperands = fetch_NEW_ARRAY;
}


Class * get_primitive_array_class(ClassLoader *loader,uint8_t atype){
    switch(atype){
        case AT_BOOLEAN:
            return load_class(loader,"[Z");
        case AT_CHAR:
            return load_class(loader,"[C");
        case AT_FLOAT:
            return load_class(loader,"[F");
        case AT_DOUBLE:
            return load_class(loader,"[D");
        case AT_BYTE:
            return load_class(loader,"[B");
        case AT_SHORT:
            return load_class(loader,"[S");
        case AT_INT:
            return load_class(loader,"[I");
        case AT_LONG:
            return load_class(loader,"[J");
        default:
            printf("java.lang.InternalError\n");
            exit(1);
    }
}
void execute_NEW_ARRAY(void *self, Frame *frame){
    NEW_ARRAY *self_ = (NEW_ARRAY *) self;
    OperandStack *stack = frame->operand_stack;
    int count = pop_int(stack);
    if (count < 0) {
        printf("java.lang.NegativeArraySizeException\n");
        exit(1);
    }
    ClassLoader * loader = frame->method->base->class->loader;
    Class * arr_class = get_primitive_array_class(loader,self_->atype);
    Object * arr = new_array(arr_class, count);
    push_ref(stack,arr);
}

void fetch_NEW_ARRAY(void *self,BytecodeReader*reader){
    NEW_ARRAY *self_ = (NEW_ARRAY *) self;
    self_->atype = read_uint8(reader);
}

void init_ANEW_ARRAY(ANEW_ARRAY *self){
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_ANEW_ARRAY;
}

void execute_ANEW_ARRAY(void *self, Frame *frame){
    RtConstantPool * pool = frame->method->base->class->constant_pool;
    ANEW_ARRAY *self_ = (ANEW_ARRAY *) self;
    ClassRef *classRef = get_constant_info(pool, self_->base.index)->value.classRef;
    Class * component_class = resolve_classes(&classRef->base);
    OperandStack *stack = frame->operand_stack;
    int count = pop_int(stack);
    if (count < 0) {
        printf("java.lang.NegativeArraySizeException\n");
        exit(1);
    }
    Class * array_class = arr_class(component_class);
    Object * arr = new_array(array_class, count);
    push_ref(stack,arr);
}


void init_ARRAY_LENGTH(ARRAY_LENGTH *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_ARRAY_LENGTH;
}

void execute_ARRAY_LENGTH(void *self, Frame *frame){
    ARRAY_LENGTH *self_ = (ARRAY_LENGTH *) self;
    OperandStack *stack = frame->operand_stack;
    Object * arr_ref = pop_ref(stack);
    if (arr_ref == NULL) {
        printf("java.lang.NullPointerException\n");
        exit(1);
    }
    int arr_len = arrayLength(arr_ref);
    push_int(stack,arr_len);
}

int32_t * pop_and_check_counts(OperandStack*stack,int dimensions){
    int32_t * counts= (int32_t*) malloc(sizeof(int32_t));
    for (int i = dimensions-1;i>=0;i--){
        counts[i] = pop_int(stack);
        if (counts[i]<0){
            printf("java.lang.NegativeArraySizeException\n");
            exit(1);
        }
    }
    return counts;
}

Object* new_multi_array(Class*self,int32_t * counts,int dimensions){
    int count = counts[0];
    Object * arr_class = new_array(self,count);
    if (dimensions>1){
        Object ** ref_ = refs(arr_class);
        int len = arr_class->length;
        for (int i=0;i<len;i++){
            ref_[i] = new_multi_array(ComponentClass(self),counts+1,dimensions-1);
        }
    }
    return arr_class;
}
void init_MULTI_ANEW_ARRAY(MULTI_ANEW_ARRAY *self){
    self->base.Execute = execute_MULTI_ANEW_ARRAY;
    self->base.FetchOperands = fetch_MULTI_ANEW_ARRAY;
}

void execute_MULTI_ANEW_ARRAY(void *self, Frame *frame){
    MULTI_ANEW_ARRAY *self_ = (MULTI_ANEW_ARRAY *) self;
    RtConstantPool * pool = frame->method->base->class->constant_pool;
    ClassRef *class_ref = get_constant_info(pool,self_->index)->value.classRef;
    Class * arr_class = resolve_classes(&class_ref->base);
    OperandStack * stack = frame->operand_stack;
    int32_t* counts = pop_and_check_counts(stack,self_->dimensions);
    Object *arr = new_multi_array(arr_class,counts,self_->dimensions);
    push_ref(stack,arr);
}

void fetch_MULTI_ANEW_ARRAY(void *self, BytecodeReader *reader){
    MULTI_ANEW_ARRAY *self_ = (MULTI_ANEW_ARRAY *) self;
    self_->index= read_uint16(reader);
    self_->dimensions = read_uint8(reader);
}