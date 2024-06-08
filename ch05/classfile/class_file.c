//
// Created by Squanch on 2024/6/5.
//


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
    cf->fields = read_members(reader, cf->constant_pool, cf, 0);
    cf->methods = read_members(reader, cf->constant_pool, cf, 1);
    cf->attributes = read_attributes(reader, cf->constant_pool, NULL);
    return cf;
}

void readAndCheckMagic(ClassFile *cf, ClassReader *reader) {
    cf->magic = read_uint32_class(reader);
    if (cf->magic != 0xCAFEBABE) {
        fprintf(stderr, "java.lang.ClassFormatError: magic!\n");
        exit(EXIT_FAILURE);
    }
}

MemberInfo * get_main_method(ClassFile *cf){
    int count = cf->methods_count;
    for (int i = 0; i < count; ++i) {
        MemberInfo *method = cf->methods[i];
        if (memcmp(read_member_name(method,cf->constant_pool),"main",4)==0) {
            return method;
        }
    }
    return NULL;
}
ClassFile * loadClassFile(char*class_name){
    // 定义基础路径
    const char *base_path = "/Users/squanch/CLionProjects/JVMC/";
    // 计算拼接后的路径长度
    size_t path_len = strlen(base_path) + strlen(class_name) + strlen(".class") + 1;
    // 分配内存
    char *full_path = (char *)malloc(path_len);

    if (!full_path) {
        perror("malloc");
        return NULL;
    }
    // 拼接路径
    snprintf(full_path, path_len, "%s%s.class", base_path, class_name);
    printf("load class %s \n", full_path);
    int fd = open(full_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return NULL;
    }
    // 获取文件大小
    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        close(fd);
        return NULL;
    }
    size_t file_size = file_stat.st_size;
    // 分配缓冲区
    uint8_t *bytes = (uint8_t *)malloc(file_size);
    if (bytes == NULL) {
        perror("malloc");
        close(fd);
        return NULL;
    }
    // 读取文件内容到缓冲区
    ssize_t bytes_read = read(fd, bytes, file_size);
    if (bytes_read != file_size) {
        perror("read");
        free(bytes);
        close(fd);
        return NULL;
    }
    // 关闭文件
    close(fd);
    ClassFile * class_file = parseClassFile(bytes, file_size);
    return class_file;
}
