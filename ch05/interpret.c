//
// Created by Squanch on 2024/6/3.
//

#include "interpret.h"
void loop(Thread *thread, unsigned char *bytecode){
    BytecodeReader * reader = (BytecodeReader*)malloc(sizeof(BytecodeReader));
    while(1){
        //printf("operand_stack: %2d %2d\n",frame->operand_stack->slots[0].num,frame->operand_stack->slots[1].num);
        //printf("local_vars:%2d  %2d   %2d\n", frame->local_vars->slots[0].num, frame->local_vars->slots[1].num,frame->local_vars->slots[2].num);
        Frame * frame = top_frame(thread);
        int pc = frame->next_pc;
        thread->pc = pc;
        // add pc
        reset(reader,frame->method->code,pc);
        uint8_t opcode = read_int8(reader);
//        printf("\n取指\n");
        Instruction * inst = new_instruction(&opcode);
        inst->FetchOperands(inst,reader);
        set_next_pc(frame,reader->pc);
        printf("current method : %s\n",frame->method->base->name);
        printf("current pc : %d\n",pc);
        printf("current operandStack length : %d\n",frame->operand_stack->size);
        for (int i = 0; i < frame->operand_stack->size;i++){
            printf("%d ",frame->operand_stack->slots[i].num);
        }
        printf("\n");
        printf("current localVars length : %d\n",frame->local_vars->size);
        for (int i = 0; i < frame->local_vars->size;i++){
            printf("%d ",frame->local_vars->slots[i].num);
        }
        printf("\n");
        inst->Execute(inst,frame);

        if (is_empty(thread)){
            break;
        }
    }
}

void interpret(RtMethods*methods,char**args,int argc){
    Thread * thread = new_thread();
    Frame * frame = new_frame_thread(thread,methods);
    push_frame(thread,frame);
    Object * argsArr = create_args_array(methods->base->class->loader,args,argc);
    set_ref(frame->local_vars,0,argsArr);
    loop(thread,methods->code);
}

//func createArgsArray(loader *heap.ClassLoader, args []string) *heap.Object {
//stringClass := loader.LoadClass("java/lang/String")
//argsArr := stringClass.ArrayClass().NewArray(uint(len(args)))
//jArgs := argsArr.Refs()
//for i, arg := range args {
//jArgs[i] = heap.JString(loader, arg)
//}
//return argsArr
//}

Object * create_args_array(ClassLoader*loader,char**args,int argc){
    Class * stringClass = load_class(loader,"java/lang/String");
    Object * argsArr = new_array(arr_class(stringClass),argc);
    Object ** jArgs = refs(argsArr);
    for (int i = 0; i < argc; ++i) {
        jArgs[i] = create_java_string(loader,args[i]);
    }
    return argsArr;
}