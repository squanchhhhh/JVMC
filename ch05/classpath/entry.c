//
// Created by Squanch on 2024/6/4.
//


#include "entry.h"
int contains(const char *str, char c) {
    return strchr(str, c) != NULL;
}

int has_suffix(const char *str, const char *suffix) {
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (str_len < suffix_len) {
        return 0;
    }
    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}


void dir_entry_read_class(void* self, const char* className, unsigned char** data, size_t* length, int* err){

}

