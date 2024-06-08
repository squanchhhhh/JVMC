//
// Created by Squanch on 2024/6/3.
//

#include "interpret.h"
void loop(Thread *thread, unsigned char *bytecode){
    Frame * frame = pop_frame(thread);
    BytecodeReader * reader = (BytecodeReader*)malloc(sizeof(BytecodeReader));
    while(1){
        printf("operand_stack: %2d %2d\n",frame->operand_stack->slots[0].num,frame->operand_stack->slots[1].num);
        printf("local_vars:%2d  %2d   %2d\n", frame->local_vars->slots[0].num, frame->local_vars->slots[1].num,frame->local_vars->slots[2].num);
        int pc = frame->next_pc;
        thread->pc = pc;
        // add pc
        reset(reader,bytecode,pc);
        uint8_t opcode = read_int8(reader);
        Instruction * inst = new_instruction(&opcode);
        inst->FetchOperands(inst,reader);
        set_next_pc(frame,reader->pc);
        printf("pc:%2d\n", pc);
        inst->Execute(inst,frame);
    }
}

void interpret(MemberInfo * member){
    CodeAttribute *codeAttribute =get_code_attribute(member);
    int max_locals = codeAttribute->max_locals;
    int max_stack = codeAttribute->max_stack;
    uint8_t* code = codeAttribute->code;
    Thread * thread = new_thread();
    Frame * frame = new_frame(thread, max_locals, max_stack, NULL);
    push_frame(thread,frame);
    loop(thread,code);
}
