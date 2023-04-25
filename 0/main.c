#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARGS_ERROR "You should use two positive, non-zero integer arguments\n"
#define CHILD_PROCESS_ERROR "Failed to create child process.\n"

#define RESULT_OUTPUT "Result of child process execution: %d\n"

#define CHILD_APP_PATH "./child"
#define CHILD_APP_NAME "child"

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf(ARGS_ERROR);
        return 1;
    }

    int exponentNumP = atoi(argv[1]);
    int commonNumK = atoi(argv[2]);

    if(commonNumK < 1 && exponentNumP < 1) {
        printf(ARGS_ERROR);
        return 1;
    }

    pid_t pid = fork();

    if(pid == 0) {
        execl(CHILD_APP_PATH, CHILD_APP_NAME, argv[1], argv[2], NULL);
    } else if(pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if(WIFEXITED(status)) {
            int result = WEXITSTATUS(status);
            printf(RESULT_OUTPUT, result);
        }
    } else {
        printf(CHILD_PROCESS_ERROR);
        return 1;
    }

    return 0;
}
