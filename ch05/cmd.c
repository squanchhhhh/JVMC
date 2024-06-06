//
// Created by Squanch on 2024/6/3.
//
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "cmd.h"

// 打印帮助信息
void print_help() {
    printf("Usage: example_program [options]\n");
    printf("Options:\n");
    printf("  -h, --help        Display this help message\n");
    printf("  -c, --classpath PATH  Specify classpath\n");
}

Cmd* parse_cmd(int argc, char *argv[]) {
    static struct option long_options[] = {
            {"help",      no_argument,       0, 'h'},
            {"classpath", required_argument, 0, 'c'},
            {0, 0, 0, 0} // 结束标志
    };

    int opt;
    int option_index = 0;
    Cmd* cmd = (Cmd*)malloc(sizeof(Cmd));
    if (cmd == NULL) {
        fprintf(stderr, "Failed to allocate memory for cmd structure\n");
        exit(EXIT_FAILURE);
    }
    cmd->classpath = NULL; // Initialize to NULL
    cmd->args = NULL;
    cmd->num_args = 0;

    // 解析命令行选项
    while ((opt = getopt_long(argc, argv, "hc:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
            case 'c':
                cmd->classpath = (char*)malloc(strlen(optarg) + 1);
                if (cmd->classpath == NULL) {
                    fprintf(stderr, "Failed to allocate memory for classpath\n");
                    free(cmd); // Free previously allocated memory
                    exit(EXIT_FAILURE);
                }
                memcpy(cmd->classpath, optarg, strlen(optarg) + 1);
                printf("Option --classpath with argument: %s\n", cmd->classpath);
                break;
            default:
                print_help();
                free(cmd->classpath); // Free any allocated memory
                free(cmd);
                exit(EXIT_FAILURE);
        }
    }

    // 处理非选项参数
    if (optind < argc) {
        cmd->num_args = argc - optind;
        cmd->args = (char**)malloc(cmd->num_args * sizeof(char*));
        if (cmd->args == NULL) {
            fprintf(stderr, "Failed to allocate memory for arguments\n");
            free(cmd->classpath); // Free any allocated memory
            free(cmd);
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < cmd->num_args; i++) {
            cmd->args[i] = argv[optind + i];
        }

        printf("Non-option arguments: ");
        for (int i = 0; i < cmd->num_args; i++) {
            printf("%s ", cmd->args[i]);
        }
        printf("\n");
    }
    return cmd;
}