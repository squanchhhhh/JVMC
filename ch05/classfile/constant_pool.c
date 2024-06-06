//
// Created by Squanch on 2024/6/5.
//

#include <printf.h>
#include "constant_pool.h"

void read_integer(void *self, ClassReader *reader) {
    ConstantIntegerInfo *info = (ConstantIntegerInfo *)self;
    info->value = (int32_t) read_uint32_class(reader);
}
void init_read_integer(ConstantIntegerInfo *self, ClassReader *reader) {
    self->base.tag = CONSTANT_Integer;
    self->base.read_info = read_integer;
}

ConstantInfo *read_constant_info(ClassReader *reader, ConstantPool *pool) {
    uint8_t tag = read_uint8_class(reader);
    ConstantInfo *const_info = new_constant_info(tag, pool, reader);
    const_info->read_info((void*)const_info,reader);
    pool->constants[pool->index] =const_info;
    pool->index ++;
    return const_info;
}

/**
 * 对于class类型，读取到的是index，所以需要再做一次转换
 * @param pool
 * @param index
 * @return
 */
char* get_utf8_string(ConstantPool *pool,uint16_t index){
    ConstantUtf8Info *info = (ConstantUtf8Info *)pool->constants[index];
    if (info->base.tag == CONSTANT_Class){
        ConstantClassInfo *info = (ConstantClassInfo *)pool->constants[index];
        return get_utf8_string(pool,info->name_index);
    }
    return info->str;
}
ConstantPool *read_constant_pool(ClassReader *reader) {
    int count = read_uint16_class(reader);
    // 为 ConstantInfo* 指针数组分配内存
    ConstantInfo **constants = malloc(sizeof(ConstantInfo *) * count);
    if (!constants) {
        perror("Failed to allocate memory for constants");
        exit(EXIT_FAILURE);
    }
    ConstantPool *pool = malloc(sizeof(ConstantPool));
    if (!pool) {
        perror("Failed to allocate memory for ConstantPool");
        free(constants);  // 确保释放已经分配的内存
        exit(EXIT_FAILURE);
    }
    pool->index = 1;
    pool->count = count;
    pool->constants = constants;
    // 初始化常量池条目
    for (int i = 1; i < count; i++) {
        pool->constants[i] = read_constant_info(reader, pool);
        // 处理 LONG 和 DOUBLE 占用两个索引的情况
        if (pool->constants[i]->tag == CONSTANT_Long || pool->constants[i]->tag == CONSTANT_Double) {
            i++;
        }
    }
    return pool;
}
//#define CONSTANT_Class              7
//#define CONSTANT_Fieldref           9
//#define CONSTANT_Methodref          10
//#define CONSTANT_InterfaceMethodref 11
//#define CONSTANT_String             8
//#define CONSTANT_Integer            3
//#define CONSTANT_Float              4
//#define CONSTANT_Long               5
//#define CONSTANT_Double             6
//#define CONSTANT_NameAndType        12
//#define CONSTANT_Utf8               1
//#define CONSTANT_MethodHandle       15
//#define CONSTANT_MethodType         16
//#define CONSTANT_InvokeDynamic      18
ConstantInfo *new_constant_info(uint8_t tag, ConstantPool *pool, ClassReader *reader) {
    switch (tag) {
        case CONSTANT_Integer: {
            ConstantIntegerInfo *info = malloc(sizeof(ConstantIntegerInfo));
            init_read_integer(info, reader);
            return (ConstantInfo *)info;
        }
        case CONSTANT_Float: {
            ConstantFloatInfo *info = malloc(sizeof(ConstantFloatInfo));
            init_read_float(info, reader);
            return (ConstantInfo *)info;
        }
        case CONSTANT_Long: {
            ConstantLongInfo *info = malloc(sizeof(ConstantLongInfo));
            init_read_long(info, reader);
            return (ConstantInfo *)info;
        }
        case CONSTANT_Class:{
            ConstantClassInfo *info = malloc(sizeof(ConstantClassInfo));
            init_read_class(info, reader);
            return (ConstantInfo *)info;
        }
        case CONSTANT_String:{
            ConstantStringInfo *info = malloc(sizeof(ConstantStringInfo));
            init_read_string(info, reader);
            return (ConstantInfo *)info;
        }
        case CONSTANT_Utf8:{
            ConstantUtf8Info *info = malloc(sizeof(ConstantUtf8Info));
            init_read_utf8(info, reader);
            return (ConstantInfo *)info;
        }
//        case CONSTANT_MethodHandle:{
//            ConstantMethodHandleInfo *info = malloc(sizeof(ConstantMethodHandleInfo));
//            init_read_method_handle(info, reader);
//            return (ConstantInfo *)info;
//        }
//        case CONSTANT_MethodType:{
//            ConstantMethodTypeInfo *info = malloc(sizeof(ConstantMethodTypeInfo));
//            init_read_method_type(info, reader);
//            return (ConstantInfo *)info;
//        }
//        case CONSTANT_InvokeDynamic:{
//            ConstantInvokeDynamicInfo *info = malloc(sizeof(ConstantInvokeDynamicInfo));
//            init_read_invoke_dynamic(info, reader);
//            return (ConstantInfo *)info;
//        }
        case CONSTANT_Fieldref:{
            ConstantFieldrefInfo *info = malloc(sizeof(ConstantFieldrefInfo));
            init_read_fieldref(info, reader,CONSTANT_Fieldref);
            return (ConstantInfo *)info;
        }
        case CONSTANT_Methodref:{
            ConstantMethodrefInfo *info = malloc(sizeof(ConstantMethodrefInfo));
            init_read_methodref(info, reader,CONSTANT_Methodref);
            return (ConstantInfo *)info;
        }
        case CONSTANT_InterfaceMethodref:{
            ConstantInterfaceMethodrefInfo *info = malloc(sizeof(ConstantInterfaceMethodrefInfo));
            init_read_interface_methodref(info, reader,CONSTANT_InterfaceMethodref);
            return (ConstantInfo *)info;
        }
        case CONSTANT_NameAndType:{
            ConstantNameAndTypeInfo *info = malloc(sizeof(ConstantNameAndTypeInfo));
            init_read_name(info, reader);
            return (ConstantInfo *)info;
        }
        default:
            fprintf(stderr, "Unknown constant pool tag: %d\n", tag);
            exit(1);
    }
}

void read_float(void *self, ClassReader *reader){
    ConstantFloatInfo *info = (ConstantFloatInfo *)self;
    uint32_t val = read_uint32_class(reader);
    info->value = *(float *)&val;
}

void init_read_float(ConstantFloatInfo *self, ClassReader *reader){
    self->base.tag = CONSTANT_Float;
    self->base.read_info = read_float;
}

void read_long(void *self, ClassReader *reader){
    ConstantLongInfo *info = (ConstantLongInfo *)self;
    uint64_t val = read_uint64_class(reader);
    info->value = *(long *)&val;
}
void init_read_long(ConstantLongInfo *self, ClassReader *reader){
    self->base.tag = CONSTANT_Long;
    self->base.read_info = read_long;
}
void read_double(void *self, ClassReader *reader){
    ConstantDoubleInfo *info = (ConstantDoubleInfo *)self;
    uint64_t val = read_uint64_class(reader);
    info->value = *(double *)&val;
}
void init_read_double(ConstantDoubleInfo *self, ClassReader *reader){
    self->base.tag = CONSTANT_Double;
    self->base.read_info = read_double;
}


char *decode_mutf8(const uint8_t *bytearr, size_t length) {
    size_t utflen = length;
    char *chararr = (char *)malloc(utflen + 1); // +1 for null terminator

    size_t count = 0;
    size_t chararr_count = 0;

    while (count < utflen) {
        uint8_t c = bytearr[count];
        if (c > 127) break;
        count++;
        chararr[chararr_count++] = c;
    }

    while (count < utflen) {
        uint8_t c = bytearr[count];
        switch (c >> 4) {
            case 0 ... 7:
                count++;
                chararr[chararr_count++] = c;
                break;
            case 12:
            case 13: {
                count += 2;
                if (count > utflen) {
                    // handle error
                    free(chararr);
                    return NULL;
                }
                uint8_t char2 = bytearr[count - 1];
                if ((char2 & 0xC0) != 0x80) {
                    // handle error
                    free(chararr);
                    return NULL;
                }
                chararr[chararr_count++] = (c & 0x1F) << 6 | (char2 & 0x3F);
                break;
            }
            case 14: {
                count += 3;
                if (count > utflen) {
                    // handle error
                    free(chararr);
                    return NULL;
                }
                uint8_t char2 = bytearr[count - 2];
                uint8_t char3 = bytearr[count - 1];
                if ((char2 & 0xC0) != 0x80 || (char3 & 0xC0) != 0x80) {
                    // handle error
                    free(chararr);
                    return NULL;
                }
                chararr[chararr_count++] = (c & 0x0F) << 12 | (char2 & 0x3F) << 6 | (char3 & 0x3F);
                break;
            }
            default:
                // handle error
                free(chararr);
                return NULL;
        }
    }
    chararr[chararr_count] = '\0'; // Null-terminate the string
    return chararr;
}

void read_utf8(void *info_, ClassReader *reader) {
    ConstantUtf8Info *info = (ConstantUtf8Info *)info_;
    uint16_t length = read_uint16_class(reader);
    uint8_t *bytes = read_bytes_class(reader, length);
    if (bytes == NULL) {
        // handle error
        return;
    }
    info->str = decode_mutf8(bytes, length);
    free(bytes);
}
void init_read_utf8(ConstantUtf8Info *info, ClassReader *reader){
    info->base.tag = CONSTANT_Utf8;
    info->base.read_info = read_utf8;
}
void read_string(void *info, ClassReader *reader){
    ConstantStringInfo *info_ = (ConstantStringInfo *)info;
    info_->string_index = read_uint16_class(reader);
}
void init_read_string(ConstantStringInfo *info, ClassReader *reader){
    info->base.tag = CONSTANT_String;
    info->base.read_info = read_string;
}

void read_class(void *info, ClassReader *reader){
    ConstantClassInfo *info_ = (ConstantClassInfo *)info;
    info_->name_index = read_uint16_class(reader);
}
void init_read_class(ConstantClassInfo *info, ClassReader *reader){
    info->base.tag = CONSTANT_Class;
    info->base.read_info = read_class;
}

void read_name(void *info, ClassReader *reader){
    ConstantNameAndTypeInfo *info_ = (ConstantNameAndTypeInfo *)info;
    info_->name_index = read_uint16_class(reader);
    info_->descriptor_index = read_uint16_class(reader);
}
void init_read_name(ConstantNameAndTypeInfo *info, ClassReader *reader){
    info->base.tag = CONSTANT_NameAndType;
    info->base.read_info = read_name;
}

void read_methodref(void *info, ClassReader *reader){
    ConstantMethodrefInfo *info_ = (ConstantMethodrefInfo *)info;
    info_->class_index = read_uint16_class(reader);
    info_->name_and_type_index = read_uint16_class(reader);
}
void init_read_methodref(ConstantMethodrefInfo *info, ClassReader *reader,uint8_t tag){
    info->base.tag = tag;
    info->base.read_info = read_methodref;
}

void read_fieldref(void *info, ClassReader *reader){
    ConstantFieldrefInfo *info_ = (ConstantFieldrefInfo *)info;
    info_->class_index = read_uint16_class(reader);
    info_->name_and_type_index = read_uint16_class(reader);
}
void init_read_fieldref(ConstantFieldrefInfo *info, ClassReader *reader,uint8_t tag){
    info->base.tag = tag;
    info->base.read_info = read_fieldref;
}

void read_interface_methodref(void *info, ClassReader *reader){
    ConstantInterfaceMethodrefInfo *info_ = (ConstantInterfaceMethodrefInfo *)info;
    info_->class_index = read_uint16_class(reader);
    info_->name_and_type_index = read_uint16_class(reader);
}
void init_read_interface_methodref(ConstantInterfaceMethodrefInfo *info, ClassReader *reader,uint8_t tag){
    info->base.tag = tag;
    info->base.read_info = read_interface_methodref;
}



