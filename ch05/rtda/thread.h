//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_THREAD_H
#define JVMC_THREAD_H
#include "heap/object.h"
#include <stdio.h>
#include <stdlib.h>
#include <libc.h>
typedef struct Thread Thread;
typedef struct Frame Frame;
typedef struct Object Object;
typedef struct RtMethods RtMethods;
typedef struct{
    int num;
    Object *ref;
}Slot;

typedef struct LocalVars {
    Slot *slots;     // 指向Slot数组
    unsigned int size;   // 数组大小
} LocalVars;

LocalVars* new_local_vars(unsigned int size);

void set_int(LocalVars *local_vars,int index,int value);

int get_int(LocalVars *local_vars,int index);

void set_ref(LocalVars *local_vars,int index,Object *ref);

Object *get_ref(LocalVars *local_vars,int index);

void set_long(LocalVars *local_vars,int index,long value);

long get_long(LocalVars *local_vars,int index);

void set_float(LocalVars *local_vars,int index,float value);

float get_float(LocalVars *local_vars,int index);

double get_double(LocalVars *local_vars,int index);

void set_double(LocalVars *local_vars,int index,double value);

void set_slot(LocalVars *local_vars,int index,Slot slot);

Slot get_slot(LocalVars *local_vars,int index);
typedef struct {
    unsigned int size;  // 当前栈大小
    Slot *slots;    // 指向Slot数组
    unsigned int max_size; // 栈的最大容量
} OperandStack;

OperandStack* new_operand_stack(unsigned int max_stack);

void push_int(OperandStack* operand_stack,int val);

int pop_int(OperandStack* operand_stack);

void push_long(OperandStack* operand_stack,long val);

long pop_long(OperandStack* operand_stack);

void push_float(OperandStack* operand_stack,float val);

float pop_float(OperandStack* operand_stack);

void push_double(OperandStack* operand_stack,double val);

double pop_double(OperandStack* operand_stack);

void push_ref(OperandStack* operand_stack,Object *ref);

Object *pop_ref(OperandStack* operand_stack);

void push_slot(OperandStack* operand_stack,Slot slot);

Slot pop_slot(OperandStack* operand_stack);

Object * get_ref_from_top(OperandStack*self,uint index);
//--------------------------帧--------------------------------------
struct Frame{
    struct Frame *lower;
    LocalVars * local_vars;
    OperandStack* operand_stack;
    Thread * thread;
    int next_pc;
    RtMethods *method;
};
void set_next_pc(Frame*frame,int pc);
//new指令需要将pc前移
void revert_next_pc(Frame*frame);

Frame *new_frame(Thread *thread, RtMethods *method);

//--------------------------------------线程栈------------------------------------------------
typedef struct {
    unsigned int max_size;
    unsigned int size;
    Frame *_top;
}Stack;

Stack *new_stack(unsigned int size);

void push(Stack *stack, Frame *frame);

Frame *pop(Stack *stack);

Frame *top(Stack *stack);


//----------------------------------------线程结构体-------------------------------------------------
struct Thread {
    int pc;
    Stack *stack;
};

Thread *new_thread();
int is_empty(Thread *thread);
Frame * new_frame_thread(Thread*thread,RtMethods*method);
int pc(Thread *thread);


//设置pc
void set_pc(Thread *thread,int pc);

//推入栈帧
void push_frame(Thread *thread,Frame *frame);

//弹出当前栈帧
Frame *pop_frame(Thread *thread);

//获取当前栈帧
Frame *top_frame(Thread *thread);

#endif //JVMC_THREAD_H
