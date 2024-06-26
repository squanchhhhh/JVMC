//
// Created by Squanch on 2024/6/3.
//

#include "instruction.h"
void NoOperands_instruction_fetch(){
    //do nothing
}
void NoOperands_instruction_init(NoOperandsInstruction * self){
    self->base.FetchOperands = NoOperands_instruction_fetch;
}
void Branch_instruction_fetch(void *self,BytecodeReader*reader){
    BranchInstruction* branchInstr = (BranchInstruction*)self;
    branchInstr->offset = (int)read_int16(reader);
}
void Branch_instruction_init(BranchInstruction *self){
    self->base.FetchOperands = Branch_instruction_fetch;
}
void Index8_instruction_fetch(void *self,BytecodeReader *reader){
    Index8Instruction* indexInstr = (Index8Instruction*)self;
    indexInstr->index = (int)read_int8(reader);
}
void Index8_instruction_init(Index8Instruction *self){
    self->base.FetchOperands = Index8_instruction_fetch;
}
void Index16_instruction_fetch(void *self,BytecodeReader *reader){
    Index16Instruction* indexInstr = (Index16Instruction*)self;
    indexInstr->index = (int)read_int16(reader);
}
void Index16_instruction_init(Index16Instruction *self){
    self->base.FetchOperands = Index16_instruction_fetch;
}
void branch(Frame*frame,int offset){
    int pc = frame->thread->pc;
    int next_pc = pc+offset;
    frame->next_pc = next_pc;
}

void init_NOP(NoOperandsInstruction * self){
    self->base.FetchOperands=fetch_NOP;
    self->base.Execute=execute_NOP;
}
void fetch_NOP(void * self,BytecodeReader *reader){

}
void execute_NOP(void * self,Frame*frame){

}

void invoke_method(Frame *frame, RtMethods *method) {
    Thread *thread = frame->thread;
    Frame *new_frame = new_frame_thread(thread, method);
    push_frame(thread, new_frame);
    int args = method->arg_slots_count;
    if (args > 0) {
        for (int i = args - 1; i >= 0; --i) {
            Slot slot = pop_slot(frame->operand_stack);
            set_slot(new_frame->local_vars, i, slot);
        }
    }
}
void schedule_clinit(Thread *thread, Class *class) {
    RtMethods *clinit = get_clinit_method(class);
    if (clinit != NULL) {
        Frame *frame = new_frame_thread(thread, clinit);
        push_frame(thread, frame);
    }
}

void init_super_class(Thread *thread, Class *class) {
    if (!is_interface(class)) {
        Class *super_class = class->super_class;
        if (super_class != NULL && !super_class->initialized) {
            init_class(thread, super_class);
        }
    }
}

void init_class(Thread *thread, Class *class) {
    class->initialized = 1;
    schedule_clinit(thread, class);
    init_super_class(thread, class);
}

Class * arr_class(Class * class){
    char * name = get_arr_name(class->name);
    return load_class(class->loader,name);
}
Class* ComponentClass(Class *self) {
    char* componentClassName = get_component_class_name(self->name);
    Class* componentClass = load_class(self->loader, componentClassName);
    free(componentClassName);
    return componentClass;
}