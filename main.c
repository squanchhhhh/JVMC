#include <stdio.h>
#include "ch05/rtda/thread.h"
#include "ch05/cmd.h"
#include "ch05/all_class_headers.h"
ClassFile * loadClassFile(char*class_name);
int main(int argc,char * argv[]) {
    ClassFile * class_file = loadClassFile("/Users/squanch/CLionProjects/JVMC/MyFirstJvmTest.class");
    printf("version: %d,%d\n",class_file->major_version,class_file->minor_version);
    printf("constants count: %d\n", class_file->constant_pool->count);
    printf("access_flags: %d\n", class_file->access_flags);
    printf("this_class: %s\n", get_utf8_string(class_file->constant_pool,class_file->this_class));
    printf("super_class: %s\n", get_utf8_string(class_file->constant_pool,class_file->super_class));
    printf("interfaces count: %d\n", class_file->interfaces_count);
    printf("fields count: %d\n", class_file->fields_count);
    for (int i = 0; i < class_file->fields_count; i++){
        printf("    %s\n", read_member_name(class_file->fields[i],class_file->constant_pool));
    }
    printf("methods count: %d\n", class_file->methods_count);
    for (int i = 0; i < class_file->methods_count; i++){
        printf("    %s\n",read_member_name(class_file->methods[i],class_file->constant_pool));
    }
    return 0;
}

ClassFile * loadClassFile(char*class_name){
    // 打开文件
    int fd = open(class_name, O_RDONLY);
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


