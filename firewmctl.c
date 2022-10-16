#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "firewm-msg.c"
#include "FoxString.h"
#include "firewmctl.h"

void print_commands() {

    printf("\n");
    printf("FireWM 6.3\n\n");
    for (int i = 0; i < 7; i++) {
        printf("%s %s -> %s\n", commands[i], params[i], comments[i]);
    }
    printf("\nINT    ( integer is required as parameter )\n");
    printf("STRING ( word is required as parameter )\n\n");
}

void print_help() {
    printf("\n");
    printf("FireWM 6.3\n\n");
    printf("ignore -> respond from commands won't show\n");
    printf("get monitors -> retrieves list of monitors\n");
    printf("get tags -> retrieves list of tags and with their specified mask\n");
    printf("get layouts -> retrieves list of layouts to which you can switch\n");
    printf("help commands -> Show list of every command supported by FireWMctl\n");
    printf("<command> <params> -> run command with params which will execute FireWM api function\n\n");
}

int main(int argc, char *argv[]) {

    connect_to_socket();

    if (sock_fd == -1) {
        fprintf(stderr, "Failed to connect to socket\n");
        return 1;
    }

    int i = 2;
    if (argc > 1 && strcmp(argv[i], "execute")) {
        char *command = argv[i];
        char **command_args = argv + ++i;
        int command_argc = argc - i;
        run_command(command, command_args, command_argc);
        return 0;
    }

    while (1) {
        printf("[\033[31;1mFireWM\033[0m] \033[31;1m>>\033[0m ");
        FoxString in = FoxStringInput();
        while (in.data[in.size-1] == ' ') FoxString_Pop(&in);

        if (FoxString_Compare(in, FoxString_New("help"))) {
            print_help();
        } else if (FoxString_Compare(in, FoxString_New("help commands"))) {
            print_commands();
        } else if (FoxString_Compare(in, FoxString_New("exit")) || FoxString_Compare(in, FoxString_New("quit"))) {
            break;
        } else {
            for (int i = 0; i < 7; i++) {
                if (strncmp(commands[i], in.data, strlen(commands[i])) == 0) {
                    int args_start = FoxString_Find(in, ' ');
                    if (args_start == NOT_FOUND) {
                        printf("Missing args of type %s\n", params[i]);
                        break;
                    }

                    int args_length = strlen((in.data+args_start));
                    char **args = malloc(sizeof(char**));
                    int offset = 0;
                    int j = 0;

                    FoxString_Add(&in, ' ');

                    FoxString args_wrapped = FoxString_New(strndup((in.data+args_start+1), args_length));

                    for (; j < FoxString_Count(args_wrapped, ' ')+1; j++) {
                        FoxString temp = FoxString_New((args_wrapped.data+offset));
                        int end = FoxString_Find(temp, ' ');
                        args[j] = strndup(temp.data, end);
                        args = realloc(args, (j+2) * sizeof(char**));
                        offset += end+1;
                    }
                    char *cmd = strndup(in.data, strlen(commands[i]));
                    run_command(cmd, args, j-1);
                }
            }
        }
    }
    return 0;
}