//
// Created by Squanch on 2024/6/7.
//

#ifndef JVMC_CLASS_H
#define JVMC_CLASS_H

#include "../common_rtda_struct.h"
typedef struct Object Object;
Class *new_class(ClassFile *cf);

int is_accessible(Class *a, Class *b);

int is_protected(Class *pClass);

int is_private(Class *c);

int is_public(Class *class);

int is_interface(Class *pClass);

int is_abstract(Class *pClass);

int is_sub_class_of(Class *d, Class *c);

int is_accessible_field(FieldRef *self, Class *other);

char **get_interface_names(ConstantPool *pPool, uint16_t *pInt);

RtConstantPool *new_rt_constant_pool(Class *pClass, ConstantPool *pPool);

RtFields **new_rt_fields(Class *pClass, MemberInfo **fields, int count);

int is_double_or_long(RtFields *field);

int is_static_field(RtFields *field);

int is_final_field(RtFields *field);

int is_volatile_field(RtFields *field);

void copy_attribute_info(RtMethods *methods, MemberInfo *info);

void copy_member_info(RtMember *member, MemberInfo *info);

RtMethods **new_rt_methods(Class *pClass, MemberInfo **methods, int count);

ClassRef *new_class_ref(RtConstantPool *pool, ConstantClassInfo *info);

FieldRef *new_field_ref(RtConstantPool *pool, ConstantFieldRefInfo *info);

MethodRef *new_method_ref(RtConstantPool *pool, ConstantMethodRefInfo *info);

InterfaceMethodRef *new_interface_method_ref(RtConstantPool *pool, ConstantInterfaceMethodRefInfo *info);

RtConstantInfo *get_constant_info(RtConstantPool *pool, uint16_t index);

unsigned int hash(const char *str, int size);

ClassLoader *NewClassLoader(int size);

void resolve_super_class(Class *class);

void resolve_interfaces(Class *class);

Class *load_non_array_class(ClassLoader *loader, char *name);

Class *define_class(ClassLoader *loader, char *name);

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


Class *resolve_classes(SymRef *self);

void resolve_field_ref(FieldRef *self);

RtFields *resolve_fields(FieldRef *self);

RtFields *find_field(Class *pClass, char *name, char *descriptor);

Object *new_object_by_class(Class *pClass);

#endif //JVMC_CLASS_H
