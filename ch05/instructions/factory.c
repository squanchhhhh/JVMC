//
// Created by Squanch on 2024/6/3.
//

#include "factory.h"
#define CREATE_INSTRUCTION(opcode, type) \
    case opcode: { \
        type *instruction = M(type); \
        init_##type(instruction); \
        return (Instruction *) instruction; \
    }
#define M(x) (x*)malloc(sizeof(x))
Instruction * new_instruction(unsigned char * opcode){
    switch (*opcode) {
        case 0x00: return NULL; //M(NOP);
        CREATE_INSTRUCTION(0x01,ACONST_NULL)
        CREATE_INSTRUCTION(0x02,ICONST_M1)
        CREATE_INSTRUCTION(0x03,ICONST_0)
        CREATE_INSTRUCTION(0x04,ICONST_1)
        CREATE_INSTRUCTION(0x05,ICONST_2)
        CREATE_INSTRUCTION(0x06,ICONST_3)
        CREATE_INSTRUCTION(0x07,ICONST_4)
        CREATE_INSTRUCTION(0x08,ICONST_5)
        CREATE_INSTRUCTION(0x09,LCONST_0)
        CREATE_INSTRUCTION(0x0A,LCONST_1)
        CREATE_INSTRUCTION(0x0B,FCONST_0)
        CREATE_INSTRUCTION(0x0C,FCONST_1)
        CREATE_INSTRUCTION(0x0D,FCONST_2)
        CREATE_INSTRUCTION(0x0E,DCONST_0)
        CREATE_INSTRUCTION(0x0F,DCONST_1)
        CREATE_INSTRUCTION(0x10,BIPUSH)
        CREATE_INSTRUCTION(0x11,SIPUSH)
//        CREATE_INSTRUCTION(0x12,LDC)
//        CREATE_INSTRUCTION(0x13,LDC_W)
//        CREATE_INSTRUCTION(0x14,LDC2_W)
        CREATE_INSTRUCTION(0x15,ILOAD)
        CREATE_INSTRUCTION(0x16,LLOAD)
        CREATE_INSTRUCTION(0x17,FLOAD)
        CREATE_INSTRUCTION(0x18,DLOAD)
        CREATE_INSTRUCTION(0x19,ALOAD)
        CREATE_INSTRUCTION(0x1A,ILOAD_0)
        CREATE_INSTRUCTION(0x1B,ILOAD_1)
        CREATE_INSTRUCTION(0x1C,ILOAD_2)
        CREATE_INSTRUCTION(0x1D,ILOAD_3)
        CREATE_INSTRUCTION(0x1E,LLOAD_0)
        CREATE_INSTRUCTION(0x1F,LLOAD_1)
        CREATE_INSTRUCTION(0x20,LLOAD_2)
        CREATE_INSTRUCTION(0x21,LLOAD_3)
        CREATE_INSTRUCTION(0x22,FLOAD_0)
        CREATE_INSTRUCTION(0x23,FLOAD_1)
        CREATE_INSTRUCTION(0x24,FLOAD_2)
        CREATE_INSTRUCTION(0x25,FLOAD_3)
        CREATE_INSTRUCTION(0x26,DLOAD_0)
        CREATE_INSTRUCTION(0x27,DLOAD_1)
        CREATE_INSTRUCTION(0x28,DLOAD_2)
        CREATE_INSTRUCTION(0x29,DLOAD_3)
        CREATE_INSTRUCTION(0x2A,ALOAD_0)
        CREATE_INSTRUCTION(0x2B,ALOAD_1)
        CREATE_INSTRUCTION(0x2C,ALOAD_2)
        CREATE_INSTRUCTION(0x2D,ALOAD_3)
//        CREATE_INSTRUCTION(0x2E,IALOAD)
//        CREATE_INSTRUCTION(0x2F,LALOAD)
//        CREATE_INSTRUCTION(0x30,FALOAD)
//        CREATE_INSTRUCTION(0x31,DALOAD)
//        CREATE_INSTRUCTION(0x32,AALOAD)
//        CREATE_INSTRUCTION(0x33,BALOAD)
//        CREATE_INSTRUCTION(0x34,CALOAD)
//        CREATE_INSTRUCTION(0x35,SALOAD)
//        CREATE_INSTRUCTION(0x36,ISTORE)
        CREATE_INSTRUCTION(0x37,LSTORE)
//        CREATE_INSTRUCTION(0x38,FSTORE)
//        CREATE_INSTRUCTION(0x39,DSTORE)
//        CREATE_INSTRUCTION(0x3A,ASTORE)
//        CREATE_INSTRUCTION(0x3B,ISTORE_0)
//        CREATE_INSTRUCTION(0x3C,ISTORE_1)
//        CREATE_INSTRUCTION(0x3D,ISTORE_2)
//        CREATE_INSTRUCTION(0x3E,ISTORE_3)
        CREATE_INSTRUCTION(0x3F,LSTORE_0)
        CREATE_INSTRUCTION(0x40,LSTORE_1)
        CREATE_INSTRUCTION(0x41,LSTORE_2)
        CREATE_INSTRUCTION(0x42,LSTORE_3)
//        CREATE_INSTRUCTION(0x43,FSTORE_0)
//        CREATE_INSTRUCTION(0x44,FSTORE_1)
//        CREATE_INSTRUCTION(0x45,FSTORE_2)
//        CREATE_INSTRUCTION(0x46,FSTORE_3)
//        CREATE_INSTRUCTION(0x47,DSTORE_0)
//        CREATE_INSTRUCTION(0x48,DSTORE_1)
//        CREATE_INSTRUCTION(0x49,DSTORE_2)
//        CREATE_INSTRUCTION(0x4A,DSTORE_3)
//        CREATE_INSTRUCTION(0x4B,ASTORE_0)
//        CREATE_INSTRUCTION(0x4C,ASTORE_1)
//        CREATE_INSTRUCTION(0x4D,ASTORE_2)
//        CREATE_INSTRUCTION(0x4E,ASTORE_3)
//        CREATE_INSTRUCTION(0x4F,IASTORE)
//        CREATE_INSTRUCTION(0x50,LASTORE)
//        CREATE_INSTRUCTION(0x51,FASTORE)
//        CREATE_INSTRUCTION(0x52,DASTORE)
//        CREATE_INSTRUCTION(0x53,AASTORE)
//        CREATE_INSTRUCTION(0x54,BASTORE)
//        CREATE_INSTRUCTION(0x55,CASTORE)
//        CREATE_INSTRUCTION(0x56,SASTORE)
        CREATE_INSTRUCTION(0x57,POP)
        CREATE_INSTRUCTION(0x58,POP2)
        CREATE_INSTRUCTION(0x59,DUP)
        CREATE_INSTRUCTION(0x5A,DUP_X1)
        CREATE_INSTRUCTION(0x5B,DUP_X2)
        CREATE_INSTRUCTION(0x5C,DUP2)
        CREATE_INSTRUCTION(0x5D,DUP2_X1)
        CREATE_INSTRUCTION(0x5E,DUP2_X2)
        CREATE_INSTRUCTION(0x5F,SWAP)
//        CREATE_INSTRUCTION(0x60,IADD)
//        CREATE_INSTRUCTION(0x61,LADD)
//        CREATE_INSTRUCTION(0x62,FADD)
//        CREATE_INSTRUCTION(0x63,DADD)
//        CREATE_INSTRUCTION(0x64,ISUB)
//        CREATE_INSTRUCTION(0x65,LSUB)
//        CREATE_INSTRUCTION(0x66,FSUB)
//        CREATE_INSTRUCTION(0x67,DSUB)
//        CREATE_INSTRUCTION(0x68,IMUL)
//        CREATE_INSTRUCTION(0x69,LMUL)
//        CREATE_INSTRUCTION(0x6A,FMUL)
//        CREATE_INSTRUCTION(0x6B,DMUL)
//        CREATE_INSTRUCTION(0x6C,IDIV)
//        CREATE_INSTRUCTION(0x6D,LDIV)
//        CREATE_INSTRUCTION(0x6E,FDIV)
//        CREATE_INSTRUCTION(0x6F,DDIV)
        CREATE_INSTRUCTION(0x70,IREM)
        CREATE_INSTRUCTION(0x71,LREM)
        CREATE_INSTRUCTION(0x72,FREM)
        CREATE_INSTRUCTION(0x73,DREM)
//        CREATE_INSTRUCTION(0x74,INEG)
//        CREATE_INSTRUCTION(0x75,LNEG)
//        CREATE_INSTRUCTION(0x76,FNEG)
//        CREATE_INSTRUCTION(0x77,DNEG)
        CREATE_INSTRUCTION(0x78,ISHL)
        CREATE_INSTRUCTION(0x79,LSHL)
        CREATE_INSTRUCTION(0x7A,ISHR)
        CREATE_INSTRUCTION(0x7B,LSHR)
        CREATE_INSTRUCTION(0x7C,IUSHR)
        CREATE_INSTRUCTION(0x7D,LUSHR)
        CREATE_INSTRUCTION(0x7E,IAND)
        CREATE_INSTRUCTION(0x7F,LAND)
        CREATE_INSTRUCTION(0x80,IOR)
        CREATE_INSTRUCTION(0x81,LOR)
        CREATE_INSTRUCTION(0x82,IXOR)
        CREATE_INSTRUCTION(0x83,LXOR)
        CREATE_INSTRUCTION(0x84,IINC)
        CREATE_INSTRUCTION(0x85,I2L)
        CREATE_INSTRUCTION(0x86,I2F)
        CREATE_INSTRUCTION(0x87,I2D)
        CREATE_INSTRUCTION(0x88,L2I)
        CREATE_INSTRUCTION(0x89,L2F)
        CREATE_INSTRUCTION(0x8A,L2D)
        CREATE_INSTRUCTION(0x8B,F2I)
        CREATE_INSTRUCTION(0x8C,F2L)
        CREATE_INSTRUCTION(0x8D,F2D)
        CREATE_INSTRUCTION(0x8E,D2I)
        CREATE_INSTRUCTION(0x8F,D2L)
        CREATE_INSTRUCTION(0x90,D2F)
//        CREATE_INSTRUCTION(0x91,I2B)
//        CREATE_INSTRUCTION(0x92,I2C)
//        CREATE_INSTRUCTION(0x93,I2S)
        CREATE_INSTRUCTION(0x94,LCMP)
        CREATE_INSTRUCTION(0x95,FCMPL)
        CREATE_INSTRUCTION(0x96,FCMPG)
        CREATE_INSTRUCTION(0x97,DCMPL)
        CREATE_INSTRUCTION(0x98,DCMPG)
        CREATE_INSTRUCTION(0x99,IFEQ)
        CREATE_INSTRUCTION(0x9A,IFNE)
        CREATE_INSTRUCTION(0x9B,IFLT)
        CREATE_INSTRUCTION(0x9C,IFGE)
        CREATE_INSTRUCTION(0x9D,IFGT)
        CREATE_INSTRUCTION(0x9E,IFLE)
        CREATE_INSTRUCTION(0x9F,IF_ICMPEQ)
        CREATE_INSTRUCTION(0xA0,IF_ICMPNE)
        CREATE_INSTRUCTION(0xA1,IF_ICMPLT)
        CREATE_INSTRUCTION(0xA2,IF_ICMPGE)
        CREATE_INSTRUCTION(0xA3,IF_ICMPGT)
        CREATE_INSTRUCTION(0xA4,IF_ICMPLE)
        CREATE_INSTRUCTION(0xA5,IF_ACMPEQ)
        CREATE_INSTRUCTION(0xA6,IF_ACMPNE)
        CREATE_INSTRUCTION(0xA7,GOTO)
//        CREATE_INSTRUCTION(0xA8,JSR)
//        CREATE_INSTRUCTION(0xA9,RET)
//        CREATE_INSTRUCTION(0xAA,TABLESWITCH)
//        CREATE_INSTRUCTION(0xAB,LOOKUPSWITCH)
//        CREATE_INSTRUCTION(0xAC,IRETURN)
//        CREATE_INSTRUCTION(0xAD,LRETURN)
//        CREATE_INSTRUCTION(0xAE,FRETURN)
//        CREATE_INSTRUCTION(0xAF,DRETURN)
//        CREATE_INSTRUCTION(0xB0,ARETURN)
//        CREATE_INSTRUCTION(0xB1,RETURN)
//        CREATE_INSTRUCTION(0xB2,GETSTATIC)
//        CREATE_INSTRUCTION(0xB3,PUTSTATIC)
//        CREATE_INSTRUCTION(0xB4,GETFIELD)
//        CREATE_INSTRUCTION(0xB5,PUTFIELD)
//        CREATE_INSTRUCTION(0xB6,INVOKEVIRTUAL)
//        CREATE_INSTRUCTION(0xB7,INVOKESPECIAL)
//        CREATE_INSTRUCTION(0xB8,INVOKESTATIC)
//        CREATE_INSTRUCTION(0xB9,INVOKEINTERFACE)
//        CREATE_INSTRUCTION(0xBA,INVOKEDYNAMIC)
//        CREATE_INSTRUCTION(0xBB,NEW)
//        CREATE_INSTRUCTION(0xBC,NEWARRAY)
//        CREATE_INSTRUCTION(0xBD,ANEWARRAY)
//        CREATE_INSTRUCTION(0xBE,ARRAYLENGTH)
//        CREATE_INSTRUCTION(0xBF,ATHROW)
//        CREATE_INSTRUCTION(0xC0,CHECKCAST)
//        CREATE_INSTRUCTION(0xC1,INSTANCEOF)
//        CREATE_INSTRUCTION(0xC2,MONITORENTER)
//        CREATE_INSTRUCTION(0xC3,MONITOREXIT)
        CREATE_INSTRUCTION(0xC4,WIDE)
//        CREATE_INSTRUCTION(0xC5,MULTIANEWARRAY)
//        CREATE_INSTRUCTION(0xC6,IFNULL)
//        CREATE_INSTRUCTION(0xC7,IFNONNULL)
//        CREATE_INSTRUCTION(0xC8,GOTO_W)
//        CREATE_INSTRUCTION(0xC9,JSR_W)
        default:
            printf("Unknown instruction code %d\n",*opcode);
            exit(1);
    }
}