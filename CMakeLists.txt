cmake_minimum_required(VERSION 3.27)
project(JVMC C)

set(CMAKE_C_STANDARD 11)

add_executable(JVMC main.c
        ch05/instructions/base/instruction.c
        ch05/instructions/base/instruction.h
        ch05/rtda/heap/object.c
        ch05/rtda/heap/object.h
        ch05/rtda/thread.c
        ch05/rtda/thread.h
        ch05/instructions/factory.c
        ch05/instructions/factory.h
        ch05/instructions/constants/const.c
        ch05/instructions/constants/const.h
        ch05/instructions/constants/ipush.c
        ch05/instructions/constants/ipush.h
        ch05/instructions/base/bytecode_reader.c
        ch05/instructions/base/bytecode_reader.h
        ch05/instructions/loads/iload.c
        ch05/instructions/loads/iload.h
        ch05/instructions/stores/lstore.c
        ch05/instructions/stores/lstore.h
        ch05/instructions/stack/pop.c
        ch05/instructions/stack/pop.h
        ch05/instructions/stack/dup.c
        ch05/instructions/stack/dup.h
        ch05/instructions/stack/swap.c
        ch05/instructions/stack/swap.h
        ch05/instructions/math/rem.c
        ch05/instructions/math/rem.h
        ch05/instructions/math/sh.c
        ch05/instructions/math/sh.h
        ch05/instructions/math/boolean.c
        ch05/instructions/math/boolean.h
        ch05/instructions/math/iinc.c
        ch05/instructions/math/iinc.h
        ch05/instructions/conversions/d2x.c
        ch05/instructions/conversions/d2x.h
        ch05/instructions/conversions/i2x.c
        ch05/instructions/conversions/i2x.h
        ch05/instructions/comparisons/cmp.c
        ch05/instructions/comparisons/cmp.h
        ch05/instructions/comparisons/ifcond.c
        ch05/instructions/comparisons/ifcond.h
        ch05/instructions/comparisons/if_icmp.c
        ch05/instructions/comparisons/if_icmp.h
        ch05/instructions/comparisons/if_acmp.c
        ch05/instructions/comparisons/if_acmp.h
        ch05/instructions/control/goto.c
        ch05/instructions/control/goto.h
        ch05/instructions/control/tableswitch.c
        ch05/instructions/control/tableswitch.h
        ch05/instructions/control/lookupswitch.c
        ch05/instructions/control/lookupswitch.h
        ch05/instructions/extended/wide.c
        ch05/instructions/extended/wide.h
        ch05/instructions/extended/ifnull.c
        ch05/instructions/extended/ifnull.h
        ch05/interpret.c
        ch05/cmd.c
        ch05/cmd.h
        ch05/classpath/entry.c
        ch05/classpath/entry.h
        ch05/interpret.h
        ch05/all_headers.h
        ch05/classfile/class_reader.c
        ch05/classfile/class_reader.h
        ch05/classfile/class_file.c
        ch05/classfile/class_file.h
        ch05/classfile/constant_pool.c
        ch05/classfile/constant_pool.h
        ch05/classfile/attr_info.c
        ch05/classfile/attr_info.h
        ch05/classfile/member_info.c
        ch05/classfile/member_info.h
        ch05/all_class_headers.h
        ch05/classfile/common_classfile_struct.h
        ch05/rtda/heap/class.c
        ch05/rtda/heap/class.h
        ch05/rtda/common_rtda_struct.h
        ch05/instructions/reference/new.c
        ch05/instructions/reference/new.h
        ch05/instructions/constants/ldc.c
        ch05/instructions/constants/ldc.h
        ch05/instructions/control/return.c
        ch05/instructions/control/return.h
        ch05/instructions/reference/invoke.c
        ch05/instructions/reference/invoke.h
        ch05/rtda/heap/string_pool.c
        ch05/rtda/heap/string_pool.h
        ch05/native/register.c
        ch05/native/register.h
        ch05/instructions/reserved/invoke_native.c
        ch05/instructions/reserved/invoke_native.h
        ch05/native/java/lang/system.c
        ch05/native/java/lang/system.h
)
