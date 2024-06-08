//
// Created by Squanch on 2024/6/8.
//

#include "new.h"

void init_NEW(NEW *self) {
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_NEW;
}

void execute_NEW(void *self_, Frame *frame) {
    NEW *self = (NEW *) self_;
    RtConstantPool *pool = frame->method->base.class->constant_pool;
    ClassRef *class_ref = get_constant_info(pool, self->base.index)->value.classRef;
    Class *c = resolve_classes(&class_ref->base);
    if (is_abstract(c) || is_interface(c)) {
        printf("java.lang.InstantiationError\n");
        exit(1);
    }
    Object *ref = new_object_by_class(c);
    push_ref(frame->operand_stack, ref);
}

void init_PUT_STATIC(PUT_STATIC *self) {
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_PUT_STATIC;
}

void execute_PUT_STATIC(void *self_, Frame *frame) {
    PUT_STATIC *self = (PUT_STATIC *) self_;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base.class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base.class;
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
    char *d = f->base.descriptor;
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
void init_GET_STATIC(GET_STATIC *self){
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_GET_STATIC;
}

void execute_GET_STATIC(void *self, Frame *frame){
    GET_STATIC *self_ = (GET_STATIC *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base.class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self_->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base.class;
    if (!is_static_field(f)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    char *d = f->base.descriptor;
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
void init_PUT_FIELD(PUT_FIELD *self){
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_PUT_FIELD;
}

void execute_PUT_FIELD(void *self, Frame *frame){
    PUT_FIELD *self_ = (PUT_FIELD *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base.class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self_->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base.class;
    if (!is_static_field(f)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    char *d = f->base.descriptor;
    int slot_id = f->slot_id;
    LocalVars *l = c->static_vars;
    OperandStack *o = frame->operand_stack;
    switch (d[0]){
        case 'Z':

        case 'B':

        case 'C':

        case 'S':

        case 'I':
        {
            int val = pop_int(o);
            Object * ref = pop_ref(o);
            if (ref == NULL){
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_int(ref->slots,slot_id,val);
        }
        case 'F':
        {
            float val = pop_float(o);
            Object * ref = pop_ref(o);
            if (ref == NULL){
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_float(ref->slots,slot_id,val);
        }
        case 'J':
        {
            long val = pop_long(o);
            Object * ref = pop_ref(o);
            if (ref == NULL){
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_long(ref->slots,slot_id,val);
        }
        case 'D':
        {
            double val = pop_double(o);
            Object * ref = pop_ref(o);
            if (ref == NULL){
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_double(ref->slots,slot_id,val);
        }
        case 'L':
        case '[':
        {
            Object * val = pop_ref(o);
            Object * ref = pop_ref(o);
            if (ref == NULL){
                printf("java.lang.NullPointerException\n");
                exit(1);
            }
            set_ref(ref->slots,slot_id,val);
        }
        default:
            printf("java.lang.IncompatibleClassChangeError3\n");
            exit(1);
    }
}

void init_GET_FIELD(GET_FIELD *self){
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_GET_FIELD;
}

void execute_GET_FIELD(void *self, Frame *frame){
    GET_FIELD *self_ = (GET_FIELD *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base.class;
    RtConstantPool *pool = current_class->constant_pool;
    FieldRef *field = get_constant_info(pool, self_->base.index)->value.fieldRef;
    RtFields *f = resolve_fields(field);
    Class *c = f->base.class;
    if (!is_static_field(f)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    char *d = f->base.descriptor;
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
void init_INSTANCE_OF(INSTANCE_OF *self){
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_INSTANCE_OF;
}

void execute_INSTANCE_OF(void *self, Frame *frame){
    INSTANCE_OF *self_ = (INSTANCE_OF *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base.class;
    RtConstantPool *pool = current_class->constant_pool;
    ClassRef *classRef = get_constant_info(pool, self_->base.index)->value.classRef;
    Class *c = resolve_classes(&classRef->base);
    OperandStack *o = frame->operand_stack;
    Object *ref = pop_ref(o);
    if (ref == NULL){
        push_int(o, 0);
        return;
    }
    push_int(o, is_instance_of(ref, c));
}

void init_CHECK_CAST(CHECK_CAST *self){
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_CHECK_CAST;
}

void execute_CHECK_CAST(void *self, Frame *frame){
    CHECK_CAST *self_ = (CHECK_CAST *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base.class;
    RtConstantPool *pool = current_class->constant_pool;
    ClassRef *classRef = get_constant_info(pool, self_->base.index)->value.classRef;
    Class *c = resolve_classes(&classRef->base);
    OperandStack *o = frame->operand_stack;
    Object *ref = pop_ref(o);
    if (ref == NULL){
        printf("java.lang.NullPointerException\n");
        exit(1);
    }
    if (!is_instance_of(ref, c)){
        printf("java.lang.ClassCastException\n");
        exit(1);
    }
}


void init_INVOKE_SPECIAL(INVOKE_SPECIAL *self){
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_INVOKE_SPECIAL;
}

//todo invoke_special
void execute_INVOKE_SPECIAL(void *self, Frame *frame){
    pop_ref(frame->operand_stack);
}


void init_INVOKE_VIRTUAL(INVOKE_VIRTUAL *self){
    Index16_instruction_init(self->base);
    self->base.base.Execute = execute_INVOKE_VIRTUAL;
}

void execute_INVOKE_VIRTUAL(void *self, Frame *frame){
    INVOKE_VIRTUAL *self_ = (INVOKE_VIRTUAL *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base.class;
    RtConstantPool *pool = current_class->constant_pool;
    MethodRef *methodRef = get_constant_info(pool, self_->base.index)->value.methodRef;
    if (strcmp(methodRef->name,"println")==0){
        OperandStack *stack = frame->operand_stack;
        //switch methodRef.Descriptor() {
        //case "(Z)V": fmt.Printf("%v\n", stack.PopInt() != 0)
        //case "(C)V": fmt.Printf("%c\n", stack.PopInt())
        //case "(B)V": fmt.Printf("%v\n", stack.PopInt())
        //case "(S)V": fmt.Printf("%v\n", stack.PopInt())
        //case "(I)V": fmt.Printf("%v\n", stack.PopInt())
        //case "(J)V": fmt.Printf("%v\n", stack.PopLong())
        //case "(F)V": fmt.Printf("%v\n", stack.PopFloat())
        //case "(D)V": fmt.Printf("%v\n", stack.PopDouble())
        //default: panic("println: " + methodRef.Descriptor())
        //}
        //stack.PopRef()
        switch (methodRef->descriptor[1]) {
            case  'Z'   :
                printf("%d\n",pop_int(stack));
                break;
            case 'C':
                printf("%c\n",pop_int(stack));
                break;
            case 'B':
                printf("%d\n",pop_int(stack));
                break;
            case 'S':
                printf("%d\n",pop_int(stack));
                break;
            case 'I':
                printf("%d\n",pop_int(stack));
                break;
            case 'J':
                printf("%ld\n",pop_long(stack));
                break;
            case 'F':
                printf("%f\n",pop_float(stack));
                break;
            case 'D':
                printf("%f\n",pop_double(stack));
                break;
            default:
                printf("java.lang.IncompatibleClassChangeError\n");
                exit(1);
        }
    }

//    RtMethods *m = resolve_methods(&methodRef->base);
//    if (m == NULL){
//        printf("java.lang.NoSuchMethodError\n");
//        exit(1);
//    }
//    OperandStack *o = frame->operand_stack;
//    Object *ref = pop_ref(o);
//    if (ref == NULL){
//        printf("java.lang.NullPointerException\n");
//        exit(1);
//    }
}