//
// Created by Squanch on 2024/6/7.
//

#include <stdbool.h>
#include "class.h"


Class *new_class(ClassFile *cf) {
    Class *cl = (Class *) malloc(sizeof(Class));
    cl->access_flags = cf->access_flags;
    cl->name = get_utf8_string(cf->constant_pool, cf->this_class);
    cl->super_name = get_utf8_string(cf->constant_pool, cf->super_class);
    cl->interface_names = get_interface_names(cf->constant_pool, cf->interfaces);
    cl->constant_pool = new_rt_constant_pool(cl, cf->constant_pool);
    cl->fields_count = cf->fields_count;
    cl->methods_count = cf->methods_count;
    cl->fields = new_rt_fields(cl, cf->fields, cf->fields_count);
    cl->methods = new_rt_methods(cl, cf->methods, cf->methods_count);
    return cl;
}

RtMethods **new_rt_methods(Class *pClass, MemberInfo **methods, int count) {
    RtMethods **pRtMethods = (RtMethods **) malloc(count * sizeof(RtMethods *));
    for (int i = 0; i < count; i++) {
        pRtMethods[i] = (RtMethods *) malloc(sizeof(RtMethods));
        pRtMethods[i]->base = (RtMember *) malloc(sizeof(RtMember));
        pRtMethods[i]->base->class = pClass;
        copy_member_info(pRtMethods[i]->base, methods[i]);
        copy_attribute_info(pRtMethods[i], methods[i]);
        calculate_args(pRtMethods[i]);
    }
    return pRtMethods;
}

int is_static_member(RtMember *member) {
    return (member->access_flags & ACC_STATIC) != 0;
}

int is_protected_member(RtMember *member) {
    return (member->access_flags & ACC_PROTECTED) != 0;
}

int is_abstract_member(RtMember *member) {
    return (member->access_flags & ACC_ABSTRACT) != 0;
}

int is_public_member(RtMember *member) {
    return (member->access_flags & ACC_PUBLIC) != 0;
}

int is_private_member(RtMember *member) {
    return (member->access_flags & ACC_PRIVATE) != 0;
}

int is_implements(Class *self, Class *target) {
    for (Class *c = self; c; c = c->super_class) {
        int count = c->interfaces_count;
        for (int i = 0; i < count; i++) {
            if (c->interfaces[i] == target || is_sub_interface_of(c->interfaces[i], target)) {
                return true;
            }
        }
    }
    return false;
}

void calculate_args(RtMethods *method) {
    MethodDescriptor *descriptor = parse_method_descriptor(method->base->descriptor);
    if (descriptor == NULL) {
        fprintf(stderr, "Failed to parse method descriptor\n");
        exit(EXIT_FAILURE);
    }

    method->arg_slots_count = 0;
    int count = descriptor->parameter_count;
    for (int i = 0; i < count; i++) {
        method->arg_slots_count++;
        if (strcmp(descriptor->parameter_type[i], "J") == 0 || strcmp(descriptor->parameter_type[i], "D") == 0) {
            method->arg_slots_count++;
        }
    }
    if (!is_static_member(method->base)) {
        method->arg_slots_count++;
    }

    for (int i = 0; i < descriptor->parameter_count; i++) {
        free(descriptor->parameter_type[i]);
    }
    free(descriptor->parameter_type);
    free(descriptor->return_type);
    free(descriptor);
}


RtFields **new_rt_fields(Class *pClass, MemberInfo **fields, int count) {
    RtFields **pRtFields = (RtFields **) malloc(count * sizeof(RtFields *));
    for (int i = 0; i < count; i++) {
        pRtFields[i] = (RtFields *) malloc(sizeof(RtFields));
        pRtFields[i]->base = (RtMember *) malloc(sizeof(RtMember));
        pRtFields[i]->base->class = pClass;
        copy_member_info(pRtFields[i]->base, fields[i]);
        copy_field_attribute_info(pRtFields[i], fields[i]);
    }
    return pRtFields;
}

RtConstantPool *new_rt_constant_pool(Class *pClass, ConstantPool *pPool) {
    RtConstantPool *pRtPool = (RtConstantPool *) malloc(sizeof(RtConstantPool));
    pRtPool->class = pClass;
    pRtPool->constants_count = pPool->count;
    RtConstantInfo **pRtInfo = (RtConstantInfo **) malloc(pPool->count * sizeof(RtConstantInfo *));
    pRtPool->constants = pRtInfo;
    for (int i = 1; i < pPool->count; i++) {
        ConstantInfo *con = pPool->constants[i];
        switch (con->tag) {
            case CONSTANT_Integer:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_Integer;
                pRtInfo[i]->value.intValue = ((ConstantIntegerInfo *) (pPool->constants[i]))->value;
                break;
            case CONSTANT_Float:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_Float;
                pRtInfo[i]->value.floatValue = ((ConstantFloatInfo *) (pPool->constants[i]))->value;
                break;
            case CONSTANT_Long:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_Long;
                pRtInfo[i]->value.longValue = ((ConstantLongInfo *) (pPool->constants[i]))->value;
                i++;
                break;
            case CONSTANT_Double:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_Double;
                pRtInfo[i]->value.doubleValue = ((ConstantDoubleInfo *) (pPool->constants[i]))->value;
                i++;
                break;
            case CONSTANT_String:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_String;
                int index = ((ConstantStringInfo *) (pPool->constants[i]))->string_index;
                pRtInfo[i]->value.stringValue = get_utf8_string(pPool, index);
                break;
            case CONSTANT_Fieldref:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_Fieldref;
                pRtInfo[i]->value.fieldRef = new_field_ref(pRtPool, (ConstantFieldRefInfo *) pPool->constants[i]);
                break;
            case CONSTANT_Methodref:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_Methodref;
                pRtInfo[i]->value.methodRef = new_method_ref(pRtPool, (ConstantMethodRefInfo *) pPool->constants[i]);
                break;
            case CONSTANT_InterfaceMethodref:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_InterfaceMethodref;
                pRtInfo[i]->value.interfaceMethodRef = new_interface_method_ref(pRtPool,
                                                                                (ConstantInterfaceMethodRefInfo *) pPool->constants[i]);
                break;
            case CONSTANT_Class:
                pRtInfo[i] = (RtConstantInfo *) malloc(sizeof(RtConstantInfo));
                pRtInfo[i]->tag = CONSTANT_Class;
                pRtInfo[i]->value.classRef = new_class_ref(pRtPool, (ConstantClassInfo *) pPool->constants[i]);
                break;
            default:
                break;
        }
    }
    return pRtPool;
}

char **get_interface_names(ConstantPool *pPool, uint16_t *pInt) {
    return NULL;
}

void copy_member_info(RtMember *member, MemberInfo *info) {
    member->name = get_utf8_string(info->pool, info->name_index);
    member->descriptor = get_utf8_string(info->pool, info->descriptor_index);
    member->access_flags = info->access_flags;
}

void copy_attribute_info(RtMethods *methods, MemberInfo *info) {
    CodeAttribute *codeAttribute = get_code_attribute(info);
    if (codeAttribute != NULL) {
        methods->code = codeAttribute->code;
        methods->max_stack = codeAttribute->max_stack;
        methods->max_locals = codeAttribute->max_locals;
    }
}

void copy_field_attribute_info(RtFields *fields, MemberInfo *info) {
    ConstantValueAttribute *constant = get_constant_value_attribute(info);
    if (constant != NULL) {
        fields->constant_value_index = constant->constant_value_index;
    }
}

ClassRef *new_class_ref(RtConstantPool *pool, ConstantClassInfo *info) {
    ClassRef *ref = (ClassRef *) malloc(sizeof(ClassRef));
    ref->base.class = pool->class;
    ref->base.pool = pool;
    ref->base.class_name = get_utf8_string(info->pool, info->name_index);
    return ref;
}


InterfaceMethodRef *new_interface_method_ref(RtConstantPool *pool, ConstantInterfaceMethodRefInfo *info) {
    InterfaceMethodRef *ref = (InterfaceMethodRef *) malloc(sizeof(InterfaceMethodRef));
    ref->base.pool = pool;
    ref->base.class_name = get_utf8_string(info->pool, info->class_index);
    ConstantNameAndTypeInfo *c = (ConstantNameAndTypeInfo *) info->pool->constants[info->name_and_type_index];
    ref->name = get_utf8_string(info->pool, c->name_index);
    ref->descriptor = get_utf8_string(info->pool, c->descriptor_index);
    return ref;
}

MethodRef *new_method_ref(RtConstantPool *pool, ConstantMethodRefInfo *info) {
    MethodRef *ref = (MethodRef *) malloc(sizeof(MethodRef));
    ref->base.pool = pool;
    ref->base.class_name = get_utf8_string(info->pool, info->class_index);
    ConstantNameAndTypeInfo *c = (ConstantNameAndTypeInfo *) info->pool->constants[info->name_and_type_index];
    ref->name = get_utf8_string(info->pool, c->name_index);
    ref->descriptor = get_utf8_string(info->pool, c->descriptor_index);
    return ref;
}

FieldRef *new_field_ref(RtConstantPool *pool, ConstantFieldRefInfo *info) {
    FieldRef *ref = (FieldRef *) malloc(sizeof(FieldRef));
    ref->base.pool = pool;
    ref->base.class_name = get_utf8_string(info->pool, info->class_index);
    ConstantNameAndTypeInfo *c = (ConstantNameAndTypeInfo *) info->pool->constants[info->name_and_type_index];
    ref->name = get_utf8_string(info->pool, c->name_index);
    ref->descriptor = get_utf8_string(info->pool, c->descriptor_index);
    return ref;
}


ClassLoader *new_class_loader() {
    ClassLoader *loader = (ClassLoader *) malloc(sizeof(ClassLoader));
    loader->size = 0;
    loader->classes = (Class **) malloc(sizeof(Class *));
    loader->names = (char **) malloc(sizeof(char *));
    return loader;
}

RtMethods *get_main_method_rt(Class *cls) {
    return get_static_method_rt(cls, "main", "([Ljava/lang/String;)V");
}

RtMethods *get_static_method_rt(Class *cls, char *name, char *description) {
    RtMethods *method = NULL;
    for (int i = 0; i < cls->methods_count; i++) {
        if (strcmp(cls->methods[i]->base->name, name) == 0 &&
            strcmp(cls->methods[i]->base->descriptor, description) == 0) {
            method = cls->methods[i];
            break;
        }
    }
    return method;
}

RtMethods *get_clinit_method(Class *cls) {
    return get_static_method_rt(cls, "<clinit>", "()V");
}

RtFields *get_field_rt(Class *cls, char *name, char *descriptor, int is_static) {
    for (int i = 0; i < cls->fields_count; i++) {
        if (strcmp(cls->fields[i]->base->name, name) == 0 &&
            strcmp(cls->fields[i]->base->descriptor, descriptor) == 0 && is_static_field(cls->fields[i]) == is_static) {
            return cls->fields[i];
        }
    }
    return NULL;
}

unsigned int hash(const char *str, int size) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % size;
}

RtConstantInfo *get_constant_info(RtConstantPool *pool, uint16_t index) {
    return pool->constants[index];
}


typedef struct {
    const char *name;
    const char *descriptor;
} PrimitiveType;

PrimitiveType primitiveTypes[] = {
        {"void",    "V"},
        {"boolean", "Z"},
        {"byte",    "B"},
        {"short",   "S"},
        {"int",     "I"},
        {"long",    "J"},
        {"char",    "C"},
        {"float",   "F"},
        {"double",  "D"}
};

const int primitiveTypesCount = sizeof(primitiveTypes) / sizeof(PrimitiveType);

const char *getPrimitiveDescriptor(const char *typeName) {
    for (int i = 0; i < primitiveTypesCount; i++) {
        if (strcmp(primitiveTypes[i].name, typeName) == 0) {
            return primitiveTypes[i].descriptor;
        }
    }
    return NULL; // 如果未找到匹配的类型，返回 NULL
}

char *to_descriptor(const char *className) {
    // 如果类名以 '[' 开头，直接返回类名
    if (className[0] == '[') {
        return strdup(className);
    }

    // 查找是否是基本类型
    const char *primitiveDescriptor = getPrimitiveDescriptor(className);
    if (primitiveDescriptor != NULL) {
        return strdup(primitiveDescriptor);
    }

    // 否则，构造普通类名的描述符
    size_t len = strlen(className) + 3; // "L" + className + ";"
    char *descriptor = (char *) malloc(len);
    snprintf(descriptor, len, "L%s;", className);

    return descriptor;
}

char *get_arr_name(const char *className) {
    char *descriptor = to_descriptor(className);
    size_t len = strlen(descriptor) + 2; // '[' + descriptor + '\0'
    char *arrName = (char *) malloc(len);

    snprintf(arrName, len, "[%s", descriptor);
    free(descriptor);

    return arrName;
}

char *to_class_name(const char *descriptor) {
    if (descriptor[0] == '[') {
        return strdup(descriptor);
    }
    if (descriptor[0] == 'L') {
        size_t len = strlen(descriptor) - 2;
        char *className = (char *) malloc(len + 1);
        strncpy(className, descriptor + 1, len);
        className[len] = '\0';
        return className;
    }
    for (int i = 0; i < primitiveTypesCount; i++) {
        if (strcmp(primitiveTypes[i].descriptor, descriptor) == 0) {
            return strdup(primitiveTypes[i].name);
        }
    }
    fprintf(stderr, "Invalid descriptor: %s\n", descriptor);
    exit(EXIT_FAILURE);
}

char *get_component_class_name(const char *className) {
    if (className[0] == '[') {
        return to_class_name(className + 1);
    }
    fprintf(stderr, "Not array: %s\n", className);
    exit(EXIT_FAILURE);
}


Class *find_class_by_name(ClassLoader *loader, char *name) {
    if (loader->size == 0) return NULL;
    for (int i = 0; i < loader->size; i++) {
        if (strcmp(loader->names[i], name) == 0) {
            return loader->classes[i];
        }
    }
    return NULL;
}

Class *load_class(ClassLoader *loader, char *name) {
    Class *cl = find_class_by_name(loader, name);
    if (cl != NULL) {
        return cl;
    }
    if (name[0] == '[') {
        return load_array_class(loader, name);
    }
    return load_non_array_class(loader, name);
}


Class *load_non_array_class(ClassLoader *loader, char *name) {
    Class *cl = define_class(loader, name);
    printf("loading non-array class: %s\n", name);
    loader->names[loader->size] = name;
    loader->classes[loader->size] = cl;
    loader->size++;
    link_(cl);
    return cl;
}

Class *load_array_class(ClassLoader *loader, char *name) {
    Class *cl = (Class *) malloc(sizeof(Class));
    printf("load array class : %s\n", name);
    cl->access_flags = ACC_PUBLIC;
    cl->name = name;
    cl->loader = loader;
    cl->initialized = 1;
    cl->super_class = load_class(loader, "java/lang/Object");
    cl->interfaces = (Class **) malloc(sizeof(Class *) * 2);
    cl->interfaces[0] = load_class(loader, "java/lang/Cloneable");
    cl->interfaces[1] = load_class(loader, "java/io/Serializable");
    cl->interfaces_count = 2;
    loader->names[loader->size] = name;
    loader->classes[loader->size] = cl;
    loader->size++;
    return cl;
}


Class *define_class(ClassLoader *loader, char *name) {
    ClassFile *file = loadClassFile(name);
    Class *pClass = new_class(file);
    pClass->loader = loader;
    resolve_super_class(pClass);
    resolve_interfaces(pClass);
    return pClass;
}

int isArrayClass(Class *class) {
    return class->name[0] == '[';
}

void resolve_super_class(Class *class) {
    if (strcmp(class->name, "java/lang/Object") != 0) {
        class->super_class = load_class(class->loader, class->super_name);
        if (class->super_class == NULL) {
            fprintf(stderr, "Failed to load super class: %s\n", class->super_name);
            exit(EXIT_FAILURE);
        }
    }
}

void resolve_interfaces(Class *class) {
    uint count = class->interfaces_count;
    class->interfaces = (Class **) malloc(count * sizeof(Class *));
    for (int i = 0; i < count; i++) {
        class->interfaces[i] = load_class(class->loader, class->interface_names[i]);
    }
}


void link_(Class *class) {
    verify(class);
    prepare(class);
}


void init_static_final_var(Class *class, RtFields *field) {
    LocalVars *var = class->static_vars;
    RtConstantPool *pool = class->constant_pool;
    uint32_t index = field->constant_value_index;
    uint32_t slot_id = field->slot_id;
    if (index > 0) {
        switch (field->base->descriptor[0]) {
            case 'Z':
            case 'B':
            case 'C':
            case 'S':
            case 'I': {
                int val = get_constant_info(pool, index)->value.intValue;
                set_int(var, slot_id, val);
                break;
            }
            case 'F': {
                float val = get_constant_info(pool, index)->value.floatValue;
                set_float(var, slot_id, val);
                break;
            }
            case 'D': {
                double val = get_constant_info(pool, index)->value.doubleValue;
                set_double(var, slot_id, val);
                break;
            }
            case 'J': {
                long val = get_constant_info(pool, index)->value.longValue;
                set_long(var, slot_id, val);
                break;
            }
            case 'L': {
                char *str = get_constant_info(pool, index)->value.stringValue;
                Object *java_string = create_java_string(class->loader, str);
                set_ref(var, slot_id, java_string);
                break;
            }
        }
    }

}

int is_static(RtFields *field) {
    return 0 != (field->base->access_flags & ACC_STATIC);
}

int is_instance(RtFields *field) {
    return !is_static(field);
}

int is_final(RtFields *field) {
    return 0 != (field->base->access_flags & ACC_FINAL);

}

void alloc_static(Class *class) {
    class->static_vars = new_local_vars(class->static_slot_count);
    for (int i = 0; i < class->fields_count; i++) {
        if (is_static(class->fields[i]) && is_final(class->fields[i])) {
            init_static_final_var(class, class->fields[i]);
        }
    }
}

int is_double_or_long(RtFields *field) {
    if (strcmp(field->base->descriptor, "D") == 0 || strcmp(field->base->descriptor, "J") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_public(Class *class) {
    return 0 != (class->access_flags & ACC_PUBLIC);
}

void calc_static_field_slot_ids(Class *class) {
    uint32_t slot_id = 0;
    for (int i = 0; i < class->fields_count; i++) {
        if (is_static(class->fields[i])) {
            class->fields[i]->slot_id = slot_id;
            slot_id++;
            if (is_double_or_long(class->fields[i])) {
                slot_id++;
            }
        }
    }
    class->static_slot_count = slot_id;
}

void calc_instance_field_slot_ids(Class *class) {
    uint32_t slot_id = 0;
    if (class->super_class != NULL) {
        slot_id = class->super_class->instance_slot_count;
    }
    for (int i = 0; i < class->fields_count; i++) {
        if (is_instance(class->fields[i])) {
            class->fields[i]->slot_id = slot_id;
            slot_id++;
            if (is_double_or_long(class->fields[i])) {
                slot_id++;
            }
        }
    }
    class->instance_slot_count = slot_id;
}

void verify(Class *class) {

}

void prepare(Class *class) {
    calc_instance_field_slot_ids(class);
    calc_static_field_slot_ids(class);
    alloc_static(class);
}


Class *resolve_classes(SymRef *self) {
    if (self->class == NULL) {
        resolve_class_ref(self);
    }
    return self->class;
}

char *get_package_name(Class *self) {
    char *lastSlash = strrchr(self->name, '/');
    if (lastSlash != NULL) {
        size_t packageNameLength = lastSlash - self->name;
        char *packageName = (char *) malloc(packageNameLength + 1);
        if (packageName == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        strncpy(packageName, self->name, packageNameLength);
        packageName[packageNameLength] = '\0';
        return packageName;
    }
    return strdup("");
}

int is_accessible(Class *a, Class *b) {
    if (is_public(a)) {
        return 1;
    }
    char *packageNameA = get_package_name(a);
    char *packageNameB = get_package_name(b);
    int result = strcmp(packageNameA, packageNameB) == 0;
    free(packageNameA);
    free(packageNameB);
    return result;
}

void resolve_class_ref(SymRef *self) {
    Class *d = self->pool->class;
    Class *c = load_class(d->loader, self->class_name);
    if (!is_accessible(c, d)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }
    self->class = c;
}


//解析方法引用
RtMethods *resolve_methods(MethodRef *self) {
    if (self->methods == NULL) {
        resolve_method_ref(self);
    }
    return self->methods;
}

void resolve_method_ref(MethodRef *self) {
    Class *d = self->base.class;
    Class *c = resolve_classes(&self->base);
    if (is_interface(c)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    RtMethods *method = find_method(c, self->name, self->descriptor);
    if (!is_accessible_s(&self->base, d)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }
    if (method == NULL) {
        printf("java.lang.NoSuchMethodError\n");
        exit(1);
    }
    self->methods = method;
}

RtMethods *resolve_interface_method_refs(InterfaceMethodRef *self) {
    if (self->methods == NULL) {
        resolve_interface_method_ref(self);
    }
    return self->methods;
}

void resolve_interface_method_ref(InterfaceMethodRef *self) {
    Class *d = self->base.class;
    Class *c = resolve_classes(&self->base);
    if (is_interface(c)) {
        printf("java.lang.IncompatibleClassChangeError\n");
        exit(1);
    }
    RtMethods *method = find_method(c, self->name, self->descriptor);
    if (!is_accessible_s(&self->base, d)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }
    if (method == NULL) {
        printf("java.lang.NoSuchMethodError\n");
        exit(1);
    }
    self->methods = method;
}


int is_accessible_s(SymRef *self, Class *d) {
    Class *c = self->class;
    if (is_public(c)) {
        return 1;
    }
    if (is_protected(c)) {
        return d == c || is_sub_class_of(d, c) || strcmp(get_package_name(c), get_package_name(d)) == 0;
    }
    if (!is_private(c)) {
        return strcmp(get_package_name(c), get_package_name(d)) == 0;
    }
    return d == c;
}

RtMethods *find_method_in_class(Class *pClass, char *name, char *descriptor) {
    //递归父类寻找
    for (Class *c = pClass; c != NULL; c = c->super_class) {
        int count = c->methods_count;
        for (int i = 0; i < count; i++) {
            RtMethods *method = pClass->methods[i];
            if (strcmp(method->base->name, name) == 0 && strcmp(method->base->descriptor, descriptor) == 0) {
                return method;
            }
        }
    }
    return NULL;
}

RtMethods *find_method_in_interface(Class **pClass, char *name, char *descriptor, int count) {
    for (int i = 0; i < count; i++) {
        //在接口的方法中寻找
        uint mcount = pClass[i]->methods_count;
        for (int j = 0; j < mcount; j++) {
            RtMethods *method = pClass[i]->methods[j];
            if (strcmp(method->base->name, name) == 0 && strcmp(method->base->descriptor, descriptor) == 0) {
                return method;
            }
        }
        //在接口的接口中寻找
        uint icount = pClass[i]->interfaces_count;
        for (int j = 0; j < icount; j++) {
            Class *c = pClass[i]->interfaces[j];
            RtMethods *method = find_method_in_class(c, name, descriptor);
            if (method != NULL) {
                return method;
            }
        }
    }
    return NULL;
}


RtMethods *find_method(Class *pClass, char *name, char *descriptor) {
    RtMethods *method = find_method_in_class(pClass, name, descriptor);
    if (method == NULL) {
        method = find_method_in_interface(pClass->interfaces, name, descriptor, pClass->interfaces_count);
    }
    return method;
}

RtFields *resolve_fields(FieldRef *self) {
    if (self->fields == NULL) {
        resolve_field_ref(self);
    }
    return self->fields;
}

void resolve_field_ref(FieldRef *self) {
    Class *d = self->base.class;
    Class *c = resolve_classes(&self->base);
    RtFields *field = find_field(c, self->name, self->descriptor);
    if (!is_accessible_s(&self->base, d)) {
        printf("java.lang.IllegalAccessError\n");
        exit(1);
    }
    if (field == NULL) {
        printf("java.lang.NoSuchFieldError\n");
        exit(1);
    }
    self->fields = field;
}

RtFields *find_field(Class *pClass, char *name, char *descriptor) {
    int count = pClass->fields_count;
    for (int i = 0; i < count; i++) {
        RtFields *field = pClass->fields[i];
        if (strcmp(field->base->name, name) == 0 && strcmp(field->base->descriptor, descriptor) == 0) {
            return field;
        }
    }
    int icount = pClass->interfaces_count;
    for (int i = 0; i < icount; i++) {
        Class *interface = pClass->interfaces[i];
        RtFields *field = find_field(interface, name, descriptor);
        if (field != NULL) {
            return field;
        }
    }
    if (pClass->super_class != NULL) {
        return find_field(pClass->super_class, name, descriptor);
    } else {
        return NULL;
    }
}

int is_protected(Class *pClass) {
    return 0 != (pClass->access_flags & ACC_PROTECTED);
}

int is_private(Class *c) {
    return 0 != (c->access_flags & ACC_PRIVATE);
}

int is_interface(Class *pClass) {
    return 0 != (pClass->access_flags & ACC_INTERFACE);
}

int is_abstract(Class *pClass) {
    return 0 != (pClass->access_flags & ACC_ABSTRACT);
}

/**
 * 判断类 target 是否是类 base 的子类（包括间接子类）。
 *
 * @param target 指向被检查的目标类的指针。
 * @param base 指向可能是父类的类的指针。
 * @return 如果 target 是 base 的子类，则返回 1；否则返回 0。
 */
int is_sub_class_of(Class *target, Class *base) {
    Class *current = target;
    // 遍历 target 类的所有父类
    while (current != NULL) {
        // 如果当前类等于 base 类，则 target 是 base 的子类
        if (current == base) {
            return 1;
        }
        // 移动到当前类的父类
        current = current->super_class;
    }
    // 遍历结束，如果没有匹配到，则 target 不是 base 的子类
    return 0;
}

int is_sub_interface_of(Class *target, Class *base) {
    int count = target->interfaces_count;
    for (int i = 0; i < count; i++) {
        if (target->interfaces[i] == base || is_sub_interface_of(target->interfaces[i], base)) {
            return 1;
        }
    }
    return 0;
}

/**
 * 判断类 base 是否是类 target 的父类（包括间接父类）。
 *
 * @param base 指向被检查的可能是父类的类的指针。
 * @param target 指向被检查的目标类的指针。
 * @return 如果 base 是 target 的父类，则返回 1；否则返回 0。
 */
int is_super_class_of(Class *base, Class *target) {
    Class *current = target;
    // 遍历 target 类的所有父类
    while (current != NULL) {
        // 如果当前类等于 base 类，则 base 是 target 的父类
        if (current == base) {
            return 1;
        }
        // 移动到当前类的父类
        current = current->super_class;
    }
    // 遍历结束，如果没有匹配到，则 base 不是 target 的父类
    return 0;
}

int is_super(Class *target) {
    return 0 != (target->access_flags & ACC_SUPER);
}

Object *new_object_by_class(Class *pClass) {
    return new_object(pClass);
}

int is_static_field(RtFields *field) {
    return 0 != (field->base->access_flags & ACC_STATIC);
}

int is_final_field(RtFields *field) {
    return 0 != (field->base->access_flags & ACC_FINAL);
}

int is_volatile_field(RtFields *field) {
    return 0 != (field->base->access_flags & ACC_VOLATILE);
}


MethodDescriptor *parse_method_descriptor(const char *descriptor) {
    MethodDescriptorParser parser;
    parser.raw = descriptor;
    parser.offset = 0;
    parser.parsed = (MethodDescriptor *) malloc(sizeof(MethodDescriptor));
    parser.parsed->parameter_type = NULL;
    parser.parsed->parameter_count = 0;
    parser.parsed->return_type = NULL;

    start_params(&parser);
    parse_param_types(&parser);
    end_params(&parser);
    parse_return_type(&parser);
    finish(&parser);

    return parser.parsed;
}

static void start_params(MethodDescriptorParser *self) {
    if (read_uint8_m(self) != '(') {
        cause_panic(self);
    }
}

static void end_params(MethodDescriptorParser *self) {
    if (read_uint8_m(self) != ')') {
        cause_panic(self);
    }
}

static void finish(MethodDescriptorParser *self) {
    if (self->offset != strlen(self->raw)) {
        cause_panic(self);
    }
}

static void cause_panic(const MethodDescriptorParser *self) {
    fprintf(stderr, "BAD descriptor: %s\n", self->raw);
    exit(EXIT_FAILURE);
}

static char read_uint8_m(MethodDescriptorParser *self) {
    return self->raw[self->offset++];
}

static void unread_uint8(MethodDescriptorParser *self) {
    self->offset--;
}

static void parse_param_types(MethodDescriptorParser *self) {
    while (1) {
        char *t = parse_field_type(self);
        if (t != NULL) {
            add_parameter_type(self->parsed, t);
            free(t);
        } else {
            break;
        }
    }
}

static void parse_return_type(MethodDescriptorParser *self) {
    if (read_uint8_m(self) == 'V') {
        self->parsed->return_type = strdup("V");
        return;
    }

    unread_uint8(self);
    char *t = parse_field_type(self);
    if (t != NULL) {
        self->parsed->return_type = t;
        return;
    }

    cause_panic(self);
}

static char *parse_field_type(MethodDescriptorParser *self) {
    switch (read_uint8_m(self)) {
        case 'B':
            return strdup("B");
        case 'C':
            return strdup("C");
        case 'D':
            return strdup("D");
        case 'F':
            return strdup("F");
        case 'I':
            return strdup("I");
        case 'J':
            return strdup("J");
        case 'S':
            return strdup("S");
        case 'Z':
            return strdup("Z");
        case 'L':
            return parse_object_type(self);
        case '[':
            return parse_array_type(self);
        default:
            unread_uint8(self);
            return NULL;
    }
}

static char *parse_object_type(MethodDescriptorParser *self) {
    const char *unread = self->raw + self->offset;
    const char *semicolon = strchr(unread, ';');
    if (!semicolon) {
        cause_panic(self);
        return NULL;
    }

    int length = semicolon - (self->raw + self->offset - 1) + 1;
    char *descriptor = (char *) malloc(length + 1);
    strncpy(descriptor, self->raw + self->offset - 1, length);
    descriptor[length] = '\0';
    self->offset += length - 1;
    return descriptor;
}

static char *parse_array_type(MethodDescriptorParser *self) {
    int arr_start = self->offset - 1;
    parse_field_type(self);
    int arr_end = self->offset;
    int length = arr_end - arr_start;
    char *descriptor = (char *) malloc(length + 1);
    strncpy(descriptor, self->raw + arr_start, length);
    descriptor[length] = '\0';
    return descriptor;
}

static void add_parameter_type(MethodDescriptor *self, const char *t) {
    if (self->parameter_count == 0) {
        self->parameter_type = (char **) malloc(sizeof(char *));
    } else {
        self->parameter_type = (char **) realloc(self->parameter_type, (self->parameter_count + 1) * sizeof(char *));
    }

    if (self->parameter_type == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    self->parameter_type[self->parameter_count] = strdup(t);
    self->parameter_count++;
}