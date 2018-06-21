// Write a program that opens a file (with the `open()` system call) and then calls `fork()` to
// create a new process. Can both the child and parent access the file descriptor returned by `open()`?
// What happens when they are write to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE* fp;
    fp = fopen("text.txt", "w");

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child process here\n");
        char *child_str = "This is child string!\n";
        fwrite(child_str, sizeof(char), strlen(child_str), fp);
    } else {
        printf("parent process here\n");
        char *parent_str = "This is parent string!\n";
        fwrite(parent_str, sizeof(char), strlen(parent_str), fp);
    }
    fclose(fp);
    return 0;
}
