//
// Created by Squanch on 2024/6/3.
//


#include "thread.h"

Thread *new_thread() {
    Thread *thread = (Thread *) malloc(sizeof(Thread));
    thread->stack = new_stack(1024);
    return thread;
}
Frame * new_frame_thread(Thread*thread,RtMethods*method){
    new_frame(thread,method);
}

int pc(Thread *thread) {
    return thread->pc;
}

void set_pc(Thread *thread, int pc) {
    thread->pc = pc;
}

void push_frame(Thread *thread, Frame *frame) {
    push(thread->stack, frame);
}

Frame *pop_frame(Thread *thread) {
    return (Frame *) pop(thread->stack);
}

Frame *current_frame(Thread *thread) {
    return (Frame *) top(thread->stack);
}


Stack *new_stack(unsigned int size) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->max_size = size;
    return stack;
}

void push(Stack *stack, Frame *frame) {
    if (stack->size >= stack->max_size) {
        printf("java.lang.StackOverflowError\n");
        return;
    }
    if (stack->_top != NULL) {
        frame->lower = stack->_top;
    }
    stack->_top = frame;
    stack->size++;
}

void set_next_pc(Frame *frame, int pc) {
    frame->next_pc = pc;
}

Frame *pop(Stack *stack) {
    if (stack->size == 0) {
        printf("jvm stack is empty!\n");
        return NULL;
    }
    Frame *frame = stack->_top;
    stack->_top = frame->lower;
    stack->size--;
    return frame;
}

Frame *top(Stack *stack) {
    if (stack->size == 0) {
        printf("jvm stack is empty!\n");
        return NULL;
    }
    return stack->_top;
}


Frame *new_frame(Thread *thread,RtMethods *method) {
    Frame *frame = (Frame *) malloc(sizeof(Frame));
    frame->thread = thread;
    frame->local_vars = new_local_vars(method->max_locals);
    frame->operand_stack = new_operand_stack(method->max_stack);
    return frame;
}

LocalVars *new_local_vars(unsigned int max_locals) {
    LocalVars *localVars = (LocalVars *) malloc(sizeof(LocalVars));
    if (max_locals > 0) {
        localVars->slots = (Slot *) malloc(sizeof(Slot) * max_locals);
        if (localVars->slots != NULL) {
            localVars->size = max_locals;
        } else {
            localVars->size = 0; // 分配失败时设置size为0
        }
    } else {
        localVars->slots = NULL;
        localVars->size = 0;
    }
    return localVars;
}

OperandStack *new_operand_stack(unsigned int max_stack) {
    // 在堆上分配 OperandStack 结构体
    OperandStack *operandStack = (OperandStack *) malloc(sizeof(OperandStack));
    if (operandStack != NULL && max_stack > 0) {
        operandStack->slots = (Slot *) malloc(sizeof(Slot) * max_stack);
        if (operandStack->slots != NULL) {
            operandStack->max_size = max_stack;
            operandStack->size = 0;
        } else {
            // 如果分配 slots 失败，释放 OperandStack 并返回 NULL
            free(operandStack);
            operandStack = NULL;
        }
    }
    return operandStack;
}


void set_int(LocalVars *local_vars, int index, int value) {
    local_vars->slots[index].num = value;
}

int get_int(LocalVars *local_vars, int index) {
    return local_vars->slots[index].num;
}

void set_ref(LocalVars *local_vars, int index, Object *ref) {
    local_vars->slots[index].ref = ref;
}

Object *get_ref(LocalVars *local_vars, int index) {
    return local_vars->slots[index].ref;
}

void set_long(LocalVars *local_vars, int index, long val) {
    if (index + 1 < local_vars->size) {
        local_vars->slots[index].num = (int32_t) val;
        local_vars->slots[index + 1].num = (int32_t) (val >> 32);
    }
}

long get_long(LocalVars *local_vars, int index) {
    if (index + 1 < local_vars->size) {
        uint32_t low = (uint32_t) local_vars->slots[index].num;
        uint32_t high = (uint32_t) local_vars->slots[index + 1].num;
        return ((int64_t) high << 32) | (int64_t) low;
    }
    return 0;
}

void set_float(LocalVars *local_vars, int index, float value) {
    memcpy(&local_vars->slots[index].num, &value, sizeof(float));
}

float get_float(LocalVars *local_vars, int index) {
    float value;
    memcpy(&value, &local_vars->slots[index].num, sizeof(float));
    return value;
}

void set_double(LocalVars *local_vars, int index, double value) {
    if (index + 1 < local_vars->size) {
        // 使用 uint64_t 存储 double 的位表示
        uint64_t bits;
        memcpy(&bits, &value, sizeof(bits));

        // 拆分成两个 int32_t
        local_vars->slots[index].num = (int32_t) (bits & 0xFFFFFFFF);
        local_vars->slots[index + 1].num = (int32_t) (bits >> 32);
    }
}

double get_double(LocalVars *local_vars, int index) {
    if (index + 1 < local_vars->size) {
        // 组合两个 int32_t 成为 uint64_t
        uint32_t low = (uint32_t) local_vars->slots[index].num;
        uint32_t high = (uint32_t) local_vars->slots[index + 1].num;
        uint64_t bits = ((uint64_t) high << 32) | (uint64_t) low;

        // 使用 double 来存储这些位
        double val;
        memcpy(&val, &bits, sizeof(val));
        return val;
    }
    return 0.0; // 处理越界情况
}

void push_int(OperandStack *operand_stack, int val) {
    if (operand_stack->size >= operand_stack->max_size) {
        printf("java.lang.StackOverflowError\n");
        return;
    }
    operand_stack->slots[operand_stack->size].num = val;
    operand_stack->size++;
}

int pop_int(OperandStack *operand_stack) {
    if (operand_stack->size == 0) {
        printf("java.lang.StackOverflowError\n");
        return 0;
    }
    operand_stack->size--;
    return operand_stack->slots[operand_stack->size].num;
}

void push_long(OperandStack *operand_stack, long val) {
    if (operand_stack->size >= operand_stack->max_size) {
        printf("java.lang.StackOverflowError\n");
        return;
    }
    memcpy(&operand_stack->slots[operand_stack->size].num, &val, sizeof(int32_t));
    memcpy(&operand_stack->slots[operand_stack->size + 1].num, ((char *) &val) + sizeof(int32_t), sizeof(int32_t));
    operand_stack->size += 2;
}

long pop_long(OperandStack *operand_stack) {
    if (operand_stack->size == 0) {
        printf("java.lang.StackOverflowError\n");
        return 0;
    }
    operand_stack->size -= 2;
    int64_t high = (int64_t) (uint32_t) operand_stack->slots[operand_stack->size + 1].num;
    int64_t low = (int64_t) (uint32_t) operand_stack->slots[operand_stack->size].num;
    return (high << 32) | low;
}

void push_float(OperandStack *operand_stack, float val) {
    if (operand_stack->size >= operand_stack->max_size) {
        printf("java.lang.StackOverflowError\n");
        return;
    }
    memcpy(&operand_stack->slots[operand_stack->size].num, &val, sizeof(float));
    operand_stack->size++;
}

float pop_float(OperandStack *operand_stack) {
    if (operand_stack->size == 0) {
        printf("java.lang.StackUnderflowError\n");
        return 0.0f;
    }
    operand_stack->size--;
    float val;
    memcpy(&val, &operand_stack->slots[operand_stack->size].num, sizeof(float));
    return val;
}

void push_double(OperandStack *operand_stack, double val) {
    if (operand_stack->size >= operand_stack->max_size) {
        printf("java.lang.StackOverflowError\n");
        return;
    }
    // 使用 uint64_t 存储 double 的位表示
    uint64_t bits;
    memcpy(&bits, &val, sizeof(bits));

    // 拆分成两个 int32_t
    operand_stack->slots[operand_stack->size].num = (int32_t) (bits & 0xFFFFFFFF);
    operand_stack->slots[operand_stack->size + 1].num = (int32_t) (bits >> 32);
    operand_stack->size += 2;
}

double pop_double(OperandStack *operand_stack) {
    if (operand_stack->size == 0) {
        printf("java.lang.StackOverflowError\n");
        return 0;
    }
    operand_stack->size -= 2;
    // 组合两个 int32_t 成为 uint64_t
    uint32_t low = (uint32_t) operand_stack->slots[operand_stack->size].num;
    uint32_t high = (uint32_t) operand_stack->slots[operand_stack->size + 1].num;
    uint64_t bits = ((uint64_t) high << 32) | (uint64_t) low;

    // 使用 double 来存储这些位
    double val;
    memcpy(&val, &bits, sizeof(val));
    return val;
}

void push_ref(OperandStack *operand_stack, Object *ref) {
    if (operand_stack->size >= operand_stack->max_size) {
        printf("java.lang.StackOverflowError\n");
        return;
    }
    operand_stack->slots[operand_stack->size].ref = ref;
    operand_stack->size++;
}

Object *pop_ref(OperandStack *operand_stack) {
    if (operand_stack->size == 0) {
        printf("java.lang.StackOverflowError\n");
        return NULL;
    }
    operand_stack->size--;
    return operand_stack->slots[operand_stack->size].ref;
}
void push_slot(OperandStack* operand_stack,Slot slot){
    operand_stack->slots[operand_stack->size] = slot;
    operand_stack->size++;
}

Slot pop_slot(OperandStack* operand_stack){
    operand_stack->size--;
    return operand_stack->slots[operand_stack->size];
}