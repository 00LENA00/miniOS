#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "system.h"
void func_id();
void minisystem();
void print_minios(char* str);
int fork_call();
int ipc_pipes();

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }

        else if (strcmp(input,"minisystem") == 0){
            minisystem();
        }
   	
   	else if (strcmp(input,"func_id") == 0){
            func_id();
        }
	else if (strcmp(input, "fork_call") == 0){
		fork_call();
	}
	else if (strcmp(input, "ipc_pipes") == 0){
		ipc_pipes();
	}
	else if (strcmp(input, "pi") == 0){
		pi_mc();
	}
        else system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
