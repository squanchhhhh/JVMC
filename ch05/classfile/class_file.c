//
// Created by Squanch on 2024/6/5.
//

#include "class_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "class_reader.h"
#include "class_file.h"

void readAndCheckVersion(ClassFile *cf, ClassReader *reader) {
    cf->minor_version = read_uint16_class(reader);
    cf->major_version = read_uint16_class(reader);
    switch (cf->major_version) {
        case 45:
            return;
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
            if (cf->minor_version == 0) {
                return;
            }
    }
    fprintf(stderr, "java.lang.UnsupportedClassVersionError!\n");
    exit(EXIT_FAILURE);
}

ClassFile *parseClassFile(const uint8_t *classData, size_t size) {
    ClassReader *reader = create_class_reader(classData, size);
    ClassFile *cf = (ClassFile *) malloc(sizeof(ClassFile));

    readAndCheckMagic(cf, reader);
    readAndCheckVersion(cf, reader);
    cf->constant_pool = read_constant_pool(reader);
    cf->access_flags = read_uint16_class(reader);
    cf->this_class = read_uint16_class(reader);
    cf->super_class = read_uint16_class(reader);
    cf->interfaces = read_uint16s_class(reader);
    cf->fields = read_members(reader, cf->constant_pool);
    cf->methods = read_members(reader, cf->constant_pool);
    cf->attributes = read_attributes(reader, cf->constant_pool);

    return cf;
}

void readAndCheckMagic(ClassFile *cf, ClassReader *reader) {
    cf->magic = read_uint32_class(reader);
    if (cf->magic != 0xCAFEBABE) {
        fprintf(stderr, "java.lang.ClassFormatError: magic!\n");
        exit(EXIT_FAILURE);
    }
}
