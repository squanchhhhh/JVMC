//
// Created by Squanch on 2024/6/7.
//

#ifndef JVMC_CLASS_H
#define JVMC_CLASS_H

#include "../common_rtda_struct.h"

typedef struct Object Object;

Class *new_class(ClassFile *cf);

int is_accessible(Class *a, Class *b);

void calculate_args(RtMethods *methods);

int is_protected(Class *pClass);

int is_private(Class *c);

int is_public(Class *class);

int is_interface(Class *self);

int is_abstract(Class *pClass);

int is_sub_class_of(Class *d, Class *c);

int is_sub_interface_of(Class *target, Class *base);

int is_super_class_of(Class *d, Class *c);

int is_super(Class *target);

int is_accessible_s(SymRef *self, Class *other);

RtMethods *resolve_interface_method_ref(InterfaceMethodRef *self);

RtMethods *resolve_interface_method_refs(InterfaceMethodRef *self);

char **get_interface_names(ConstantPool *pPool, uint16_t *pInt);

RtMethods *find_method_in_class(Class *pClass, char *name, char *descriptor);

RtConstantPool *new_rt_constant_pool(Class *pClass, ConstantPool *pPool);

RtFields **new_rt_fields(Class *pClass, MemberInfo **fields, int count);

int is_double_or_long(RtFields *field);

int is_static_field(RtFields *field);

int is_final_field(RtFields *field);

int is_volatile_field(RtFields *field);

void copy_attribute_info(RtMethods *methods, MemberInfo *info);

void copy_member_info(RtMember *member, MemberInfo *info);

RtMethods **new_rt_methods(Class *pClass, MemberInfo **methods, int count);

int is_static_member(RtMember *member);

int is_protected_member(RtMember *member);

int is_abstract_member(RtMember *member);

int is_private_member(RtMember *member);

int is_public_member(RtMember *member);

int is_implements(Class *self, Class *target);

ClassRef *new_class_ref(RtConstantPool *pool, ConstantClassInfo *info);

FieldRef *new_field_ref(RtConstantPool *pool, ConstantFieldRefInfo *info);

MethodRef *new_method_ref(RtConstantPool *pool, ConstantMethodRefInfo *info);

InterfaceMethodRef *new_interface_method_ref(RtConstantPool *pool, ConstantInterfaceMethodRefInfo *info);

RtConstantInfo *get_constant_info(RtConstantPool *pool, uint16_t index);

Class *find_class_by_name(ClassLoader *loader, char *name);

unsigned int hash(const char *str, int size);

ClassLoader *new_class_loader();

RtMethods *get_main_method_rt(Class *cls);

RtMethods *get_static_method_rt(Class *cls, char *name, char *description);

RtMethods *get_clinit_method(Class *cls);

void resolve_super_class(Class *class);

void resolve_interfaces(Class *class);
Class * load_array_class(ClassLoader *loader, char *name);
Class *load_non_array_class(ClassLoader *loader, char *name);

Class *define_class(ClassLoader *loader, char *name);
int isArrayClass(Class *class);
void verify(Class *class);

void prepare(Class *class);

void link_(Class *class);

void prepare(Class *class);

void verify(Class *class);

//计算实例字段的个数，同时编号
void calc_instance_field_slot_ids(Class *class);

void calc_static_field_slot_ids(Class *class);


void alloc_static(Class *class);

char *get_package_name(Class *class);

void init_static_final_var(Class *class, RtFields *field);

void copy_field_attribute_info(RtFields *fields, MemberInfo *info);

void resolve_class_ref(SymRef *self);

void resolve_method_ref(MethodRef *self);

RtMethods *resolve_methods(MethodRef *self);

RtFields *find_field(Class *pClass, char *name, char *descriptor);

RtMethods *find_method(Class *pClass, char *name, char *descriptor);

Class *resolve_classes(SymRef *self);

void resolve_field_ref(FieldRef *self);

RtFields *resolve_fields(FieldRef *self);

RtFields *find_field(Class *pClass, char *name, char *descriptor);

Object *new_object_by_class(Class *pClass);


MethodDescriptor *parse_method_descriptor(const char *descriptor);

static void start_params(MethodDescriptorParser *self);

static void end_params(MethodDescriptorParser *self);

static void finish(MethodDescriptorParser *self);

static void cause_panic(const MethodDescriptorParser *self);

static char read_uint8_m(MethodDescriptorParser *self);

static void unread_uint8(MethodDescriptorParser *self);

static void parse_param_types(MethodDescriptorParser *self);

static void parse_return_type(MethodDescriptorParser *self);

static char *parse_field_type(MethodDescriptorParser *self);

static char *parse_object_type(MethodDescriptorParser *self);

static char *parse_array_type(MethodDescriptorParser *self);

static void add_parameter_type(MethodDescriptor *self, const char *t);

#endif //JVMC_CLASS_H
