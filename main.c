#include <stdio.h>
#include "ch05/rtda/thread.h"
#include "ch05/cmd.h"
#include "ch05/all_class_headers.h"
#include "ch05/interpret.h"
ClassFile * loadClassFile(char*class_name);
int main(int argc,char * argv[]) {
    ClassFile * class_file = loadClassFile("/Users/squanch/CLionProjects/JVMC/MyFirstJvmTest.class");
    MemberInfo * main = get_main_method(class_file);
    interpret(main);
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


