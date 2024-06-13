//
// Created by Squanch on 2024/6/12.
//

#include "invoke.h"

void init_INVOKE_SPECIAL(INVOKE_SPECIAL *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_INVOKE_SPECIAL;
}


void execute_INVOKE_SPECIAL(void *self, Frame *frame) {
    // 类型转换
    INVOKE_SPECIAL *self_ = (INVOKE_SPECIAL *) self;

    // 获取当前类和常量池
    Class *current_class = frame->method->base->class;
    RtConstantPool *pool = current_class->constant_pool;

    // 解析方法引用
    MethodRef *method = get_constant_info(pool, self_->base.index)->value.methodRef;
    Class *resolved_class = resolve_classes(&method->base);
    RtMethods *resolved_method = resolve_methods(method);

    // 检查初始化方法
    if (strcmp(resolved_method->base->name, "<init>") == 0 && resolved_class != resolved_method->base->class) {
        printf("java.lang.NoSuchMethodError\n");
        exit(1);
    }

    // 检查静态方法
    if (is_static_member(resolved_method->base)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }

    // 获取引用对象
    Object *ref = get_ref_from_top(frame->operand_stack, resolved_method->arg_slots_count - 1);
    if (ref == NULL) {
        printf("java.lang.NullPointerException\n");
        exit(1);
    }

    // 检查 protected 方法的访问权限
    if (is_protected_member(resolved_method->base) &&
        is_super_class_of(resolved_method->base->class, current_class) &&
        strcmp(get_package_name(resolved_method->base->class), get_package_name(current_class)) != 0 &&
        ref->class != current_class &&
        !is_sub_class_of(ref->class, current_class)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }

    // 确定要调用的方法
    RtMethods *method_to_be_invoked = resolved_method;
    if (is_super(current_class) &&
        is_super_class_of(resolved_class, current_class) &&
        strcmp(resolved_method->base->name, "<init>") != 0) {
        method_to_be_invoked = find_method_in_class(current_class->super_class, method->name,
                                                    method->descriptor);
    }

    // 检查方法是否为抽象方法
    if (method_to_be_invoked == NULL || is_abstract_member(method_to_be_invoked->base)) {
        printf("java.lang.AbstractMethodError\n");
        exit(1);
    }

    // 调用方法
    invoke_method(frame, method_to_be_invoked);
}


void init_INVOKE_VIRTUAL(INVOKE_VIRTUAL *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_INVOKE_VIRTUAL;
}
void println(OperandStack *stack, const char* descriptor);

void execute_INVOKE_VIRTUAL(void *self, Frame *frame) {
    // 类型转换
    INVOKE_VIRTUAL *self_ = (INVOKE_VIRTUAL *) self;

    // 获取当前类和常量池
    Class *current_class = frame->method->base->class;
    RtConstantPool *pool = current_class->constant_pool;

    // 解析方法引用
    MethodRef *method_ref = get_constant_info(pool, self_->base.index)->value.methodRef;
    RtMethods *resolved_method = resolve_methods(method_ref);

    // 检查静态方法
    if (is_static_member(resolved_method->base)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }

    // 获取引用对象
    Object *ref = get_ref_from_top(frame->operand_stack, resolved_method->arg_slots_count - 1);
    if (ref == NULL) {
        // hack!
        if (strcmp(method_ref->name, "println") == 0) {
            println(frame->operand_stack, method_ref->descriptor);
            return;
        }

        printf("java.lang.NullPointerException\n");
        exit(1);
    }

    // 检查 protected 方法的访问权限
    if (is_protected_member(resolved_method->base) &&
        is_super_class_of(resolved_method->base->class, current_class) &&
        strcmp(get_package_name(resolved_method->base->class), get_package_name(current_class)) != 0 &&
        ref->class != current_class &&
        !is_sub_class_of(ref->class, current_class)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }

    // 确定要调用的方法
    RtMethods *method_to_be_invoked = find_method_in_class(ref->class, method_ref->name, method_ref->descriptor);
    if (method_to_be_invoked == NULL || is_abstract_member(method_to_be_invoked->base)) {
        printf("java.lang.AbstractMethodError\n");
        exit(1);
    }

    // 调用方法
    invoke_method(frame, method_to_be_invoked);
}

// hack!
void println(OperandStack *stack, const char* descriptor) {
    if (strcmp(descriptor, "(Z)V") == 0) {
        printf("%d\n", pop_int(stack) != 0);
    } else if (strcmp(descriptor, "(C)V") == 0) {
        printf("%c\n", (char)pop_int(stack));
    } else if (strcmp(descriptor, "(I)V") == 0 || strcmp(descriptor, "(B)V") == 0 || strcmp(descriptor, "(S)V") == 0) {
        printf("%d\n", pop_int(stack));
    } else if (strcmp(descriptor, "(F)V") == 0) {
        printf("%f\n", pop_float(stack));
    } else if (strcmp(descriptor, "(J)V") == 0) {
        printf("%ld\n", pop_long(stack));
    } else if (strcmp(descriptor, "(D)V") == 0) {
        printf("%lf\n", pop_double(stack));
    } else if (strcmp(descriptor, "(Ljava/lang/String;)V") == 0){
        Object * ref = pop_ref(stack);
        char * c = to_c_string(ref);
        printf("%s\n", c);
    }
    else {
        printf("println: %s\n", descriptor);
        exit(1);
    }
    pop_ref(stack);
}


void init_INVOKE_STATIC(INVOKE_STATIC *self) {
    Index16_instruction_init(&self->base);
    self->base.base.Execute = execute_INVOKE_STATIC;
}

void execute_INVOKE_STATIC(void *self, Frame *frame) {
    INVOKE_STATIC *self_ = (INVOKE_STATIC *) self;
    RtMethods *current_method = frame->method;
    Class *current_class = current_method->base->class;
    RtConstantPool *pool = current_class->constant_pool;
    MethodRef *methodRef = get_constant_info(pool, self_->base.index)->value.methodRef;
    RtMethods *m = resolve_methods(methodRef);
    if (!is_static_member(m->base)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    invoke_method(frame, m);
}


void init_INVOKE_INTERFACE(INVOKE_INTERFACE *self){
    self->base.Execute = execute_INVOKE_INTERFACE;
    self->base.FetchOperands = fetch_INVOKE_INTERFACE;
}
void fetch_INVOKE_INTERFACE(void * self,BytecodeReader*reader) {
    INVOKE_INTERFACE *self_ = (INVOKE_INTERFACE *) self;
    self_->index = read_uint16(reader);
    //self_->count = read_uint8(reader);
    read_uint8(reader);
    read_uint8(reader);
}
void execute_INVOKE_INTERFACE(void *self, Frame *frame) {
    // 类型转换
    INVOKE_INTERFACE *self_ = (INVOKE_INTERFACE *) self;

    // 获取当前类和常量池
    Class *current_class = frame->method->base->class;
    RtConstantPool *pool = current_class->constant_pool;

    // 解析接口方法引用
    InterfaceMethodRef *method_ref = get_constant_info(pool, self_->index)->value.interfaceMethodRef;
    RtMethods *resolved_method = resolve_interface_method_refs(method_ref);

    // 检查静态或私有方法
    if (is_static_member(resolved_method->base) || is_private_member(resolved_method->base)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }

    // 获取引用对象
    Object *ref = get_ref_from_top(frame->operand_stack, resolved_method->arg_slots_count - 1);
    if (ref == NULL) {
        printf("java.lang.NullPointerException\n");
        exit(1);
    }

    // 检查引用对象是否实现了接口
    if (!is_implements(ref->class, resolve_classes(&method_ref->base))) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }

    // 查找要调用的方法
    RtMethods *method_to_be_invoked = find_method_in_class(ref->class, method_ref->name, method_ref->descriptor);
    if (method_to_be_invoked == NULL || is_abstract_member(method_to_be_invoked->base)) {
        printf("java.lang.AbstractMethodError\n");
        exit(1);
    }

    // 检查方法是否为 public
    if (!is_public_member(method_to_be_invoked->base)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }

    // 调用方法
    invoke_method(frame, method_to_be_invoked);
}