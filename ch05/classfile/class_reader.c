//
// Created by Squanch on 2024/6/5.
//

#include <libc.h>
#include "class_reader.h"
// 创建 ClassReader 实例
ClassReader* create_class_reader(const uint8_t *data, size_t size) {
    ClassReader *reader = (ClassReader *)malloc(sizeof(ClassReader));
    reader->data = data;
    reader->size = size;
    reader->index = 0;
    return reader;
}

// 读取 uint8
uint8_t read_uint8_class(ClassReader *reader) {
    if (reader->index >= reader->size) {
        return 0; // 或者处理错误
    }
    return reader->data[reader->index++];
}

// 读取 uint16
uint16_t read_uint16_class(ClassReader *reader) {
    if (reader->index + 1 >= reader->size) {
        return 0; // 或者处理错误
    }
    uint16_t val = (reader->data[reader->index] << 8) | reader->data[reader->index + 1];
    reader->index += 2;
    return val;
}

// 读取 uint32
uint32_t read_uint32_class(ClassReader *reader) {
    if (reader->index + 3 >= reader->size) {
        return 0; // 或者处理错误
    }
    uint32_t val = (reader->data[reader->index] << 24) |
                   (reader->data[reader->index + 1] << 16) |
                   (reader->data[reader->index + 2] << 8) |
                   reader->data[reader->index + 3];
    reader->index += 4;
    return val;
}

// 读取 uint64
uint64_t read_uint64_class(ClassReader *reader) {
    if (reader->index + 7 >= reader->size) {
        return 0; // 或者处理错误
    }
    uint64_t val = ((uint64_t)reader->data[reader->index] << 56) |
                   ((uint64_t)reader->data[reader->index + 1] << 48) |
                   ((uint64_t)reader->data[reader->index + 2] << 40) |
                   ((uint64_t)reader->data[reader->index + 3] << 32) |
                   ((uint64_t)reader->data[reader->index + 4] << 24) |
                   ((uint64_t)reader->data[reader->index + 5] << 16) |
                   ((uint64_t)reader->data[reader->index + 6] << 8) |
                   (uint64_t)reader->data[reader->index + 7];
    reader->index += 8;
    return val;
}

// 读取 uint16 表
uint16_t* read_uint16s_class(ClassReader *reader) {
    uint16_t length = read_uint16_class(reader);
    uint16_t *array = (uint16_t *)malloc(length * sizeof(uint16_t));
    for (size_t i = 0; i < length; i++) {
        array[i] = read_uint16_class(reader);
    }
    return array;
}

// 读取指定长度的字节
uint8_t* read_bytes_class(ClassReader *reader, uint32_t length) {
    if (reader->index + length > reader->size) {
        return NULL; // 或者处理错误
    }
    uint8_t *bytes = (uint8_t *)malloc(length);
    memcpy(bytes, reader->data + reader->index, length);
    reader->index += length;
    return bytes;
};