#include <stdio.h>
#include "ch05/rtda/thread.h"
#include "ch05/cmd.h"
#include "ch05/all_class_headers.h"
#include "ch05/interpret.h"

void start_jvm() {
    char *class_name = "MyObject";
    ClassLoader *loader = new_class_loader();
    Class *main_class = load_non_array_class(loader, class_name);
    RtMethods *main_method = get_main_method_rt(main_class);
    interpret(main_method);

}

int main(int argc, char *argv[]) {
    start_jvm();
}




