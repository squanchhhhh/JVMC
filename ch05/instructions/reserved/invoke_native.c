//
// Created by Squanch on 2024/6/13.
//

#include "invoke_native.h"
#include "../../native/java/lang/system.h"


void init_INVOKE_NATIVE(INVOKE_NATIVE*self) {
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_INVOKE_NATIVE;
}
void execute_INVOKE_NATIVE(void*self,Frame*frame){
    init();
    RtMethods * methods = frame->method;
    char* class_name  = methods->base->class->name;
    char * descriptor = methods->base->descriptor;
    char * method_name = methods->base->name;
    NativeMethod na = find_native_method(class_name,method_name,descriptor);
    if (na == NULL) {
        // 计算错误信息的长度
        size_t method_info_len = strlen(class_name) + 1 + strlen(method_name) + strlen(descriptor) + 1;
        char *method_info = (char *)malloc(method_info_len);
        if (method_info == NULL) {
            perror("Failed to allocate memory for method_info");
            exit(EXIT_FAILURE);
        }

        // 拼接错误信息
        snprintf(method_info, method_info_len, "%s.%s%s", class_name, method_name, descriptor);
        printf("java.lang.UnsatisfiedLinkError: %s\n", method_info);
        free(method_info);
        return;  // 避免调用 NULL 指针
    }
    na(frame);
}