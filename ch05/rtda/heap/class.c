//
// Created by Squanch on 2024/6/7.
//

#include "class.h"

RtFields *find_field(Class *pClass, char *name, char *descriptor);

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
        pRtMethods[i]->base.class = pClass;
        copy_member_info(&pRtMethods[i]->base, methods[i]);
        copy_attribute_info(pRtMethods[i], methods[i]);
    }
    return pRtMethods;
}

RtFields **new_rt_fields(Class *pClass, MemberInfo **fields, int count) {
    RtFields **pRtFields = (RtFields **) malloc(count * sizeof(RtFields *));
    for (int i = 0; i < count; i++) {
        pRtFields[i] = (RtFields *) malloc(sizeof(RtFields));
        pRtFields[i]->base.class = pClass;
        copy_member_info(&pRtFields[i]->base, fields[i]);
        copy_field_attribute_info(pRtFields[i], fields[i]);
    }
    return pRtFields;
}

RtConstantPool *new_rt_constant_pool(Class *pClass, ConstantPool *pPool) {
    RtConstantPool *pRtPool = (RtConstantPool *) malloc(sizeof(RtConstantPool));
    pRtPool->class = pClass;
    RtConstantInfo **pRtInfo = (RtConstantInfo **) malloc(pPool->count * sizeof(RtConstantInfo *));
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
    return NULL;
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
    loader->classes = (Class**)malloc(sizeof(Class*));
    loader->names = (char**)malloc(sizeof(char*));
    return loader;
}

RtMethods * get_main_method_rt(Class*cls){
    return get_static_method_rt(cls,"main","([Ljava/lang/String;)V");
}
RtMethods * get_static_method_rt(Class * cls,char* name,char*description){
    RtMethods *method=NULL;
    for(int i=0;i<cls->methods_count;i++){
        if(strcmp(cls->methods[i]->base.name,name)==0&&strcmp(cls->methods[i]->base.descriptor,description)==0){
            method=cls->methods[i];
            break;
        }
    }
    return method;
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

Class * find_class_by_name(ClassLoader*loader,char*name) {
    if (loader->size == 0) return NULL;
    for (int i = 0; i < loader->size; i++) {
        if (strcmp(loader->names[i], name) == 0) {
            return loader->classes[i];
        }
    }
    return NULL;
}

Class *load_class(ClassLoader *loader, char *name) {
    Class * cl = find_class_by_name(loader,name);
    if (cl != NULL) {
        return cl;
    }
    return load_non_array_class(loader, name);
}


Class *load_non_array_class(ClassLoader *loader, char *name) {
    Class *cl = define_class(loader, name);
    link_(cl);
    printf("load class %s ", name);
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
        switch (field->base.descriptor[0]) {
            case 'Z':
            case 'B':
            case 'C':
            case 'S':
            case 'I': {
                int val = get_constant_info(pool, index)->value.intValue;
                set_int(var, slot_id, val);
            }
            case 'F': {
                float val = get_constant_info(pool, index)->value.floatValue;
                set_float(var, slot_id, val);
            }
            case 'D': {
                double val = get_constant_info(pool, index)->value.doubleValue;
                set_double(var, slot_id, val);
            }
            case 'J': {
                if (field->base.descriptor[1] == '\0') {
                    long val = get_constant_info(pool, index)->value.longValue;
                    set_long(var, slot_id, val);
                } else {
                    printf("String \n");
                    exit(1);
                }
            }


        }
    }

}

int is_static(RtFields *field) {
    return 0 != (field->base.access_flags & ACC_STATIC);
}

int is_instance(RtFields *field) {
    return !is_static(field);
}

int is_final(RtFields *field) {
    return 0 != (field->base.access_flags & ACC_FINAL);

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
    if (strcmp(field->base.descriptor, "D") == 0 || strcmp(field->base.descriptor, "J") == 0) {
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
char* get_package_name(Class *self) {
    char *lastSlash = strrchr(self->name, '/');
    if (lastSlash != NULL) {
        size_t packageNameLength = lastSlash - self->name;
        char *packageName = (char *)malloc(packageNameLength + 1);
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

RtFields * resolve_fields(FieldRef*self){
    if (self->fields==NULL){
        resolve_field_ref(self);
    }
    return self->fields;
}
void resolve_field_ref(FieldRef*self){
    Class *d = self->base.class;
    Class *c =  resolve_classes(&self->base);
    RtFields *field = find_field(c, self->name, self->descriptor);
    if (!is_accessible_field(self, d)) {
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
        if (strcmp(field->base.name, name) == 0 && strcmp(field->base.descriptor, descriptor) == 0) {
            return field;
        }
    }
    int icount = pClass->interfaces_count;
    for (int i = 0; i < icount; i++) {
        Class *interface = pClass->interfaces[i];
        RtFields *field = find_field(interface, name, descriptor);
        if (field!= NULL) {
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
    return 0!= (pClass->access_flags & ACC_PROTECTED);
}
int is_private(Class *c) {
    return 0 != (c->access_flags & ACC_PRIVATE);
}
int is_interface(Class *pClass){
    return 0 != (pClass->access_flags & ACC_INTERFACE);
}
int is_abstract(Class *pClass){
    return 0 != (pClass->access_flags & ACC_ABSTRACT);
}

int is_sub_class_of(Class *d, Class *c) {
    Class *current = d;
    while (current != NULL) {
        if (current == c) {
            return 1;
        }
        current = current->super_class;
    }
    return 0;
}
int is_accessible_field(FieldRef *self, Class *other) {
    Class *c = self->base.class;
    if (is_public(c)) {
        return 1;
    }
    if (is_protected(c)) {
        return other == c || is_sub_class_of(other, c) || strcmp(get_package_name(c), get_package_name(other)) == 0;
    }
    if (!is_private(c)) {
        return strcmp(get_package_name(c), get_package_name(other)) == 0;
    }
    return other == c;
}

Object *new_object_by_class(Class *pClass){
    return new_object(pClass);
}
int is_static_field(RtFields *field){
    return 0 != (field->base.access_flags & ACC_STATIC);
}
int is_final_field(RtFields *field){
    return 0 != (field->base.access_flags & ACC_FINAL);
}
int is_volatile_field(RtFields *field){
    return 0 != (field->base.access_flags & ACC_VOLATILE);
}