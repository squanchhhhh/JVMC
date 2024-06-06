//
// Created by Squanch on 2024/6/5.
//

#include "member_info.h"

MemberInfo **read_members(ClassReader*reader,ConstantPool*pool){
    int count = read_uint16_class(reader);
    MemberInfo ** members = (MemberInfo**)malloc(count * sizeof(MemberInfo*));
    for (int i = 0; i < count; ++i) {
        members[i] = read_member(reader,pool);
    }
    return members;
}
MemberInfo *read_member(ClassReader*reader,ConstantPool*pool){
    MemberInfo * member = (MemberInfo*)malloc(sizeof(MemberInfo));
    member->access_flags = read_uint16_class(reader);
    member->name_index = read_uint16_class(reader);
    member->descriptor_index = read_uint16_class(reader);
    member->attributes = read_attributes(reader,pool);
    return member;
}

char* read_member_name(MemberInfo *self,ConstantPool*pool){
    return get_utf8_string(pool,self->name_index);
}
