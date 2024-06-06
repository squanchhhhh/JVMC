//
// Created by Squanch on 2024/6/5.
//

#include "attr_info.h"
AttributeInfo * read_attribute(ClassReader * reader,ConstantPool* pool){
    uint16_t attr_name_index = read_uint16_class(reader);
    char* attr_name = (char*)get_utf8_string(pool,attr_name_index);
    uint32_t attr_length = read_uint32_class(reader);
    AttributeInfo * info = new_attribute_info(attr_name,attr_length,pool);
    info->read_info(info,reader);
    return info;
}

AttributeInfo* new_attribute_info(char *name, uint32_t len, ConstantPool *pool) {
    switch (name[0]) {
        case 'B':
            if (STRCMP(name, "BootstrapMethods")) {
                //BootstrapMethodsAttribute *attr = (BootstrapMethodsAttribute *)malloc(sizeof(BootstrapMethodsAttribute));
                // Initialize BootstrapMethodsAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("BootstrapMethodsAttribute");
            }
            break;
        case 'C':
            if (STRCMP(name, "Code")) {
                CodeAttribute *attr = (CodeAttribute *)malloc(sizeof(CodeAttribute));
                attr->pool = pool;
                init_code_attribute(attr,NULL);
                return (AttributeInfo *)attr;
            } else if (STRCMP(name, "ConstantValue")) {
                //ConstantValueAttribute *attr = (ConstantValueAttribute *)malloc(sizeof(ConstantValueAttribute));
                // Initialize ConstantValueAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("ConstantValueAttribute");
            }
            break;
        case 'D':
            if (STRCMP(name, "Deprecated")) {
                static AttributeInfo deprecated_attr = { NULL };
                return &deprecated_attr;
            }
            break;
        case 'E':
            if (STRCMP(name, "EnclosingMethod")) {
               // EnclosingMethodAttribute *attr = (EnclosingMethodAttribute *)malloc(sizeof(EnclosingMethodAttribute));
                // Initialize EnclosingMethodAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("EnclosingMethodAttribute");
            } else if (STRCMP(name, "Exceptions")) {
                //ExceptionsAttribute *attr = (ExceptionsAttribute *)malloc(sizeof(ExceptionsAttribute));
                // Initialize ExceptionsAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("ExceptionsAttribute");
            }
            break;
        case 'I':
            if (STRCMP(name, "InnerClasses")) {
                //InnerClassesAttribute *attr = (InnerClassesAttribute *)malloc(sizeof(InnerClassesAttribute));
                // Initialize InnerClassesAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("InnerClassesAttribute");
            }
            break;
        case 'L':
            if (STRCMP(name, "LineNumberTable")) {
                //LineNumberTableAttribute *attr = (LineNumberTableAttribute *)malloc(sizeof(LineNumberTableAttribute));
                // Initialize LineNumberTableAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("LineNumberTableAttribute");
            } else if (STRCMP(name, "LocalVariableTable")) {
                //LocalVariableTableAttribute *attr = (LocalVariableTableAttribute *)malloc(sizeof(LocalVariableTableAttribute));
                // Initialize LocalVariableTableAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("LocalVariableTableAttribute");
            } else if (STRCMP(name, "LocalVariableTypeTable")) {
                //LocalVariableTypeTableAttribute *attr = (LocalVariableTypeTableAttribute *)malloc(sizeof(LocalVariableTypeTableAttribute));
                // Initialize LocalVariableTypeTableAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("LocalVariableTypeTableAttribute");
            }
            break;
        case 'S':
            if (STRCMP(name, "Signature")) {
               // SignatureAttribute *attr = (SignatureAttribute *)malloc(sizeof(SignatureAttribute));
                // Initialize SignatureAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("SignatureAttribute");
            } else if (STRCMP(name, "SourceFile")) {
                //SourceFileAttribute *attr = (SourceFileAttribute *)malloc(sizeof(SourceFileAttribute));
                //attr->cp = pool;
                // Initialize SourceFileAttribute if necessary
                //return (AttributeInfo *)attr;
                printf("SourceFileAttribute");
            } else if (STRCMP(name, "Synthetic")) {
                static AttributeInfo synthetic_attr = { NULL };
                return &synthetic_attr;
            }
            break;
        default:
            break;
    }
}

AttributeInfo **read_attributes(ClassReader *reader, ConstantPool *pool) {
    uint16_t attr_count = read_uint16_class(reader);
    AttributeInfo **info = (AttributeInfo **)malloc(sizeof(AttributeInfo*)*attr_count);
    for (int i = 0; i < attr_count; ++i) {
        info[i] = read_attribute(reader,pool);
    }
    return info;
}

//todo unparse
void read_unparsed_attribute_info(void*self,ClassReader * reader){
    UnparsedAttributeInfo * info = (UnparsedAttributeInfo* )self;
    info->info = read_bytes_class(reader, info->len);
}
void init_unparsed_attribute_info(UnparsedAttributeInfo *self,ClassReader * reader){
    self->base.read_info = read_unparsed_attribute_info;
}

void read_code_attribute(void *self,ClassReader * reader){
    CodeAttribute * info = (CodeAttribute *)self;
    info->max_stack = read_uint16_class(reader);
    info->max_locals = read_uint16_class(reader);
    uint32_t code_length = read_uint32_class(reader);
    info->code = read_bytes_class(reader, code_length);
    info->exception_table = read_exception_table(reader);
    info->attributes = read_attributes(reader, info->pool);
}
void init_code_attribute(CodeAttribute *self,ClassReader * reader){
    self->base.read_info = read_code_attribute;
}

ExceptionTableEntry **read_exception_table(ClassReader *reader) {
    uint16_t exception_table_length = read_uint16_class(reader);
    ExceptionTableEntry ** exception_table = (ExceptionTableEntry **)malloc(exception_table_length*sizeof(ExceptionTableEntry*));
    for (int i = 0; i < exception_table_length; ++i) {
        exception_table[i] = (ExceptionTableEntry *)malloc(sizeof(ExceptionTableEntry));
        exception_table[i]->start_pc = read_uint16_class(reader);
        exception_table[i]->end_pc = read_uint16_class(reader);
        exception_table[i]->handler_pc = read_uint16_class(reader);
        exception_table[i]->catch_type = read_uint16_class(reader);
    }
    return exception_table;
}
