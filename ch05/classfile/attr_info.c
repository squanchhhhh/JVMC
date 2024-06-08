//
// Created by Squanch on 2024/6/5.
//

#include "attr_info.h"
#include "common_classfile_struct.h"
/*
 * 方便后面识别code属性
 */
#define CODE 1
#define CONSTANT_VALUE 2

void read_constant_value_attribute(void* self, ClassReader *reader){
    ConstantValueAttribute *attr = (ConstantValueAttribute *) self;
    attr->constant_value_index = read_uint16_class(reader);
}

void init_constant_value_attribute(ConstantValueAttribute *self, ClassReader *reader){
    self->base.read_info = read_constant_value_attribute;
    self->base.type = CONSTANT_VALUE;
}
AttributeInfo *read_attribute(ClassReader *reader, ConstantPool *pool) {
    uint16_t attr_name_index = read_uint16_class(reader);
    char *attr_name = (char *) get_utf8_string(pool, attr_name_index);
    printf("开始加载属性:%s\n",attr_name);
    uint32_t attr_length = read_uint32_class(reader);
    AttributeInfo *info = new_attribute_info(attr_name, attr_length, pool,reader);
    info->read_info(info, reader);
    return info;
}

AttributeInfo *new_attribute_info(char *name, uint32_t len, ConstantPool *pool,ClassReader*reader) {
    switch (name[0]) {
        case 'B':
            if (STRCMP(name, "BootstrapMethods")) {
                //BootstrapMethodsAttribute *attr = (BootstrapMethodsAttribute *)malloc(sizeof(BootstrapMethodsAttribute));
                // Initialize BootstrapMethodsAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("BootstrapMethodsAttribute\n");
            }
            break;
        case 'C':
            if (STRCMP(name, "Code")) {
                CodeAttribute *attr = (CodeAttribute *) malloc(sizeof(CodeAttribute));
                attr->pool = pool;
                init_code_attribute(attr, NULL);
                return (AttributeInfo *) attr;
            } else if (STRCMP(name, "ConstantValue")) {
                ConstantValueAttribute *attr = (ConstantValueAttribute *)malloc(sizeof(ConstantValueAttribute));
                init_constant_value_attribute(attr, reader);
                return (AttributeInfo *)attr;
            }
            break;
        case 'D':
            if (STRCMP(name, "Deprecated")) {
                DeprecatedAttribute *attr = (DeprecatedAttribute *)malloc(sizeof(DeprecatedAttribute));
                init_deprecated_attribute(attr, reader);
                return (AttributeInfo *)attr;
            }
            break;
        case 'E':
            if (STRCMP(name, "EnclosingMethod")) {
                // EnclosingMethodAttribute *attr = (EnclosingMethodAttribute *)malloc(sizeof(EnclosingMethodAttribute));
                // Initialize EnclosingMethodAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("EnclosingMethodAttribute\n");
            } else if (STRCMP(name, "Exceptions")) {
                ExceptionAttribute *attr = (ExceptionAttribute *)malloc(sizeof(ExceptionAttribute));
                init_exception_attribute(attr,reader,len);
                return (AttributeInfo *)attr;
            }
            break;
//        case 'I':
//            if (STRCMP(name, "InnerClasses")) {
//                //InnerClassesAttribute *attr = (InnerClassesAttribute *)malloc(sizeof(InnerClassesAttribute));
//                // Initialize InnerClassesAttribute if necessary
//                //return (AttributeInfo *)attr;
//                printf("InnerClassesAttribute\n");
//            }
//            break;
        case 'L':
            if (STRCMP(name, "LineNumberTable")) {
                LineNumberTableAttribute *attr = (LineNumberTableAttribute *) malloc(sizeof(LineNumberTableAttribute));
                init_line_number_attribute(attr, NULL);
                return (AttributeInfo *) attr;
            }
//            } else if (STRCMP(name, "LocalVariableTable")) {
//                //LocalVariableTableAttribute *attr = (LocalVariableTableAttribute *)malloc(sizeof(LocalVariableTableAttribute));
//                // Initialize LocalVariableTableAttribute if necessary
//                //return (AttributeInfo *)attr;
//                printf("LocalVariableTableAttribute\n");
//            } else if (STRCMP(name, "LocalVariableTypeTable")) {
//                //LocalVariableTypeTableAttribute *attr = (LocalVariableTypeTableAttribute *)malloc(sizeof(LocalVariableTypeTableAttribute));
//                // Initialize LocalVariableTypeTableAttribute if necessary
//                //return (AttributeInfo *)attr;
//                printf("LocalVariableTypeTableAttribute\n");
//            }
            break;
        case 'S':
            if (STRCMP(name, "Signature")) {
                SignatureAttributeInfo *attr = (SignatureAttributeInfo *)malloc(sizeof(SignatureAttributeInfo));
                init_signature_attribute(attr,reader,len);
                return (AttributeInfo *)attr;
            } else if (STRCMP(name, "SourceFile")) {
                SourceFileAttribute *attr = (SourceFileAttribute *)malloc(sizeof(SourceFileAttribute));
                attr->pool = pool;
                init_source_file_attribute(attr,NULL);
                return (AttributeInfo *)attr;
            } else if (STRCMP(name, "Synthetic")) {
                static AttributeInfo synthetic_attr = {NULL};
                return &synthetic_attr;
            } else if (STRCMP(name, "StackMapTable")){
                StackMapTableAttributeInfo *attr = (StackMapTableAttributeInfo *)malloc(sizeof(StackMapTableAttributeInfo));
                init_stack_map_table_attribute(attr,reader,len);
                return (AttributeInfo *)attr;
            }
            break;
        default: {
            UnparsedAttributeInfo *info = (UnparsedAttributeInfo *) malloc(sizeof(UnparsedAttributeInfo));
            init_unparsed_attribute_info(info,reader,len);
            return (AttributeInfo*)info;
        }
    }
}

AttributeInfo **read_attributes(ClassReader *reader, ConstantPool *pool, MemberInfo *member) {
    uint16_t attr_count = read_uint16_class(reader);
    if (member!=NULL) member->count = attr_count;
    AttributeInfo **info = (AttributeInfo **) malloc(sizeof(AttributeInfo *) * attr_count);
    for (int i = 0; i < attr_count; ++i) {
        info[i] = read_attribute(reader, pool);
    }
    return info;
}

//todo unparse
void read_unparsed_attribute_info(void *self, ClassReader *reader) {
    UnparsedAttributeInfo *info = (UnparsedAttributeInfo *) self;
    info->info = read_bytes_class(reader, info->len);
}

void init_unparsed_attribute_info(UnparsedAttributeInfo *self, ClassReader *reader,int len) {
    self->len = len;
    self->base.read_info = read_unparsed_attribute_info;
}

void read_code_attribute(void *self, ClassReader *reader) {
    CodeAttribute *info = (CodeAttribute *) self;
    info->max_stack = read_uint16_class(reader);
    info->max_locals = read_uint16_class(reader);
    uint32_t code_length = read_uint32_class(reader);
    info->code = read_bytes_class(reader, code_length);
    info->exception_table = read_exception_table(reader);
    info->attributes = read_attributes(reader, info->pool, NULL);
}

void init_code_attribute(CodeAttribute *self, ClassReader *reader) {
    self->base.type = CODE;
    self->base.read_info = read_code_attribute;
}

ExceptionTableEntry **read_exception_table(ClassReader *reader) {
    uint16_t exception_table_length = read_uint16_class(reader);
    ExceptionTableEntry **exception_table = (ExceptionTableEntry **) malloc(
            exception_table_length * sizeof(ExceptionTableEntry *));
    for (int i = 0; i < exception_table_length; ++i) {
        exception_table[i] = (ExceptionTableEntry *) malloc(sizeof(ExceptionTableEntry));
        exception_table[i]->start_pc = read_uint16_class(reader);
        exception_table[i]->end_pc = read_uint16_class(reader);
        exception_table[i]->handler_pc = read_uint16_class(reader);
        exception_table[i]->catch_type = read_uint16_class(reader);
    }
    return exception_table;
}

void read_line_number_attribute(void *self,ClassReader * reader){
    uint16_t len = read_uint16_class(reader);
    LineNumberTableAttribute *info = (LineNumberTableAttribute *) self;
    info->lines = (LineNumberTable**)malloc(len*sizeof(LineNumberTable*));
    for (int i = 0; i < len; ++i) {
        info->lines[i] = (LineNumberTable*)malloc(sizeof(LineNumberTable));
        info->lines[i]->start_pc = read_uint16_class(reader);
        info->lines[i]->line_number = read_uint16_class(reader);
    }
}
void init_line_number_attribute(LineNumberTableAttribute *self,ClassReader * reader){
    self->base.read_info = read_line_number_attribute;
}


void read_source_file_attribute(void *self,ClassReader * reader){
    SourceFileAttribute *info = (SourceFileAttribute *) self;
    info->source_file_index = read_uint16_class(reader);
}
void init_source_file_attribute(SourceFileAttribute *self,ClassReader * reader){
    self->base.read_info = read_source_file_attribute;
}

void read_signature_attribute(void *self,ClassReader * reader){
    // do nothing
}
void init_signature_attribute(SignatureAttributeInfo *self,ClassReader * reader,int len){
    self->temp_store = read_bytes_class(reader,len);
    self->base.read_info = read_signature_attribute;
}

void read_exception_attribute(void *self, ClassReader *reader){
    // do nothing
}

void init_exception_attribute(ExceptionAttribute *self, ClassReader *reader,int len){
    self->temp_store = read_bytes_class(reader,len);
    self->base.read_info = read_exception_attribute;
}
void read_stack_map_table_entrys(StackMapTableAttributeInfo * info ,ClassReader *reader){
    for (int i = 0; i < info->number_of_entries;i++){
        info->entries[i] = read_stack_map_table_entry(reader);
    }
}

StackMapTableEntry *read_stack_map_table_entry(ClassReader *reader){
    StackMapTableEntry * entry = (StackMapTableEntry *)malloc(sizeof(StackMapTableEntry));
    entry->frame_type = read_uint8_class(reader);
    entry->offset = read_uint16_class(reader);
}

void read_stack_map_table_attribute(void *self,ClassReader * reader){
    //do nothing
//    StackMapTableAttributeInfo *info = (StackMapTableAttributeInfo *) self;
//    info->number_of_entries = read_uint16_class(reader);
//    info->entries = (StackMapTableEntry**) malloc(info->number_of_entries*sizeof(StackMapTableEntry*));
//    read_stack_map_table_entrys(info,reader);
}
void init_stack_map_table_attribute(StackMapTableAttributeInfo *self,ClassReader * reader,int len){
    self->contents = read_bytes_class(reader,len);
    self->base.read_info = read_stack_map_table_attribute;
}

void init_deprecated_attribute(DeprecatedAttribute * self, ClassReader * reader){
    self->base.read_info = read_deprecated_attribute;
}

void read_deprecated_attribute(void *self, ClassReader *reader){
    //do nothing
}