//
// Created by Squanch on 2024/6/13.
//

#include "string_pool.h"
StringPool *internedStrings  =NULL;
// UTF-8 转换为 UTF-16
uint16_t* utf8_to_utf16(const char *utf8_str) {
    size_t len = strlen(utf8_str);
    // 预估 UTF-16 字符串的最大长度
    uint16_t *utf16_str = (uint16_t *)malloc((len + 1) * sizeof(uint16_t));
    if (!utf16_str) return NULL;

    size_t i = 0, j = 0;
    while (i < len) {
        uint8_t c = utf8_str[i];
        if (c < 0x80) {
            // 1 字节 UTF-8 (ASCII)
            utf16_str[j++] = c;
            i++;
        } else if ((c & 0xE0) == 0xC0) {
            // 2 字节 UTF-8
            if (i + 1 >= len) break; // 确保不会越界
            utf16_str[j++] = ((c & 0x1F) << 6) | (utf8_str[i + 1] & 0x3F);
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3 字节 UTF-8
            if (i + 2 >= len) break; // 确保不会越界
            utf16_str[j++] = ((c & 0x0F) << 12) | ((utf8_str[i + 1] & 0x3F) << 6) | (utf8_str[i + 2] & 0x3F);
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            // 4 字节 UTF-8 (代理对)
            if (i + 3 >= len) break; // 确保不会越界
            uint32_t codepoint = ((c & 0x07) << 18) | ((utf8_str[i + 1] & 0x3F) << 12) | ((utf8_str[i + 2] & 0x3F) << 6) | (utf8_str[i + 3] & 0x3F);
            codepoint -= 0x10000;
            utf16_str[j++] = 0xD800 | (codepoint >> 10);
            utf16_str[j++] = 0xDC00 | (codepoint & 0x3FF);
            i += 4;
        } else {
            // 无效的 UTF-8 字符或不支持的编码
            free(utf16_str);
            return NULL;
        }
    }
    utf16_str[j] = 0; // 终止符

    return utf16_str;
}

Object* create_java_string(ClassLoader *loader ,const char *str) {
    if (find_interned_string(str)!=NULL){
        return find_interned_string(str);
    }
    uint16_t *utf16_str = utf8_to_utf16(str);
    Object * java_chars = new_chars_object(load_class(loader,"[C"),utf16_str);
    Object * java_string = new_object(load_class(loader,"java/lang/String"));
    set_ref_var(java_string,"value","[C",java_chars);
    if (internedStrings == NULL){
        internedStrings = (StringPool *) malloc(sizeof(StringPool));
        internedStrings->str = (char *) malloc(strlen(str) + 1);
        strcpy(internedStrings->str, str);
        internedStrings->string = java_string;
        internedStrings->next = NULL;
        return java_string;
    }
    StringPool *current = internedStrings;
    while (current->next!= NULL) {
        current = current->next;
    }
    current->next = (StringPool *) malloc(sizeof(StringPool));
    current->str = (char *) malloc(strlen(str) + 1);
    strcpy(current->str, str);
    current->string = java_string;
    current->next = NULL;
    return java_string;
}
char* to_c_string(Object*ref){
    Object * r = get_ref_var(ref,"value", "[C");
    uint16_t * string = chars(r);
    char* str = utf16_to_utf8(string, r->length);
    return str;
}
char* utf16_to_utf8(const uint16_t* utf16_str, size_t utf16_len) {
    // UTF-8 字符串通常比 UTF-16 要长，因此我们预留一个足够大的缓冲区
    size_t utf8_len = utf16_len * 3;
    char* utf8_str = (char*)malloc(utf8_len + 1); // +1 用于结尾的 '\0'
    if (!utf8_str) {
        return NULL;
    }

    char* utf8_ptr = utf8_str;
    for (size_t i = 0; i < utf16_len; ++i) {
        uint16_t wc = utf16_str[i];

        if (wc < 0x80) {
            *utf8_ptr++ = (char)wc;
        } else if (wc < 0x800) {
            *utf8_ptr++ = (char)(0xC0 | (wc >> 6));
            *utf8_ptr++ = (char)(0x80 | (wc & 0x3F));
        } else {
            *utf8_ptr++ = (char)(0xE0 | (wc >> 12));
            *utf8_ptr++ = (char)(0x80 | ((wc >> 6) & 0x3F));
            *utf8_ptr++ = (char)(0x80 | (wc & 0x3F));
        }
    }

    *utf8_ptr = '\0'; // 终止符
    return utf8_str;
}

Object* find_interned_string(const char *str) {
    StringPool *current = internedStrings;
    while (current != NULL) {
        if (strcmp(current->str, str) == 0) {
            return current->string;
        }
        current = current->next;
    }
    return NULL;
}