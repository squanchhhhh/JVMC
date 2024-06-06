//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_CMD_H
#define JVMC_CMD_H
#include <getopt.h>
#include <stdlib.h>
#include <printf.h>
typedef struct{
    char *classpath;
    char**args;
    int num_args;
}Cmd;
Cmd* parse_cmd(int argc, char * argv[]);
#endif //JVMC_CMD_H
