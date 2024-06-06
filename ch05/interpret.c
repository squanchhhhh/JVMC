//
// Created by Squanch on 2024/6/3.
//

#include "interpret.h"
void loop(Thread *thread, unsigned char *bytecode){
    Frame * frame = pop_frame(thread);
    BytecodeReader * reader = (BytecodeReader*)malloc(sizeof(BytecodeReader));
    while(1){
        int pc = frame->next_pc;
        thread->pc = pc;
        reset(reader,bytecode,pc);
        uint8_t opcode = read_int8(reader);
        Instruction * inst = new_instruction(&opcode);
        inst->FetchOperands(inst,reader);
        set_pc(thread,reader->pc);
        inst->Execute(thread,frame);
    }
}
