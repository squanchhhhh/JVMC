#include <stdio.h>
#include "ch05/rtda/thread.h"
#include "ch05/cmd.h"
#include "ch05/all_class_headers.h"
#include "ch05/interpret.h"

int main(int argc,char * argv[]) {
    ClassFile * class_file = loadClassFile("/Users/squanch/CLionProjects/JVMC/GaussTest.class");
    MemberInfo * main = get_main_method(class_file);
    interpret(main);
}




