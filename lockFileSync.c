//
// Created by ran on 6/18/24.
// ran wurembrand 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>


int input_Is_valid(int argc,char* argv[]){
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <parent_message> <child1_message> <child2_message> <count>\n",
                argv[0]);
        return 0;
    }
    return 1;
}

void write_message(const char *message, int count) {
//    printf("inside write messages function \n");
    for (int i = 0; i < count; i++) {
        printf("%s", message);
        usleep((rand() % 100) * 1000); // Random delay between 0 and 99 milliseconds

    }
}

char** getMessages(char* argv[], int cnt) {
    char **messages = malloc(cnt * sizeof(char*));
    if (messages == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    // Copy each argument into the messages array and append a newline
    for (int i = 0; i < cnt; i++) {
        int len = strlen(argv[i + 1]);
        messages[i] = malloc(len + 2); // +2 for newline and null terminator
        if (messages[i] == NULL) {
            perror("Failed to allocate memory for message");
            // Cleanup previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(messages[j]);
            }
            free(messages);
            return NULL;
        }
        sprintf(messages[i], "%s\n", argv[i + 1]); // Copy and append a newline
    }
    return messages;
}

void freeMessages(char** messages,int cnt){
    // Free allocated memory
    for (int i = 0; i < cnt; i++) {
        free(messages[i]);
    }
    free(messages);
}


int synchronizeWriting(char** messages,int timesToWrite,int children_num){
    pid_t pid;
    int lockFile = 0;
    for (int i = 0; i <= children_num; i++) {
        pid = fork();

        if (pid == 0) {  // in child process
            // open() returns -1 if failed,
            lockFile = open("lockfile.lock", O_CREAT | O_RDWR| O_EXCL,S_IRWXU);
//            printf("in %d children, before loop\n",i);
            while(lockFile < 0){
                lockFile = open("lockfile.lock", O_CREAT | O_RDWR| O_EXCL,S_IRWXU);            
       }
            write_message(messages[i],timesToWrite);
            // After you're done with the file
            if (unlink("lockfile.lock") == -1) {
                perror("Error deleting lockfile");
                exit(EXIT_FAILURE);
            }
            exit(0);  // Child exits
        } else if (pid > 0) {
            continue;
        } else {
            // Fork failed
            perror("fork");
            return -1;
        }
    }
    while (wait(NULL) > 0);// if wait == -1 means that there are no more children alive
    return 0;
}


int main(int argc, char* argv[]){
    if(!input_Is_valid(argc,argv)){ return 1; }
    int numOfChildren = argc - 3; // argv[0] is program name, argv[argc - 1] == times to print,the argv[1] is parent    
    int timesToWrite= atoi(argv[argc-1]);
    char** messages = getMessages(argv,numOfChildren + 1);
    synchronizeWriting(messages,timesToWrite,numOfChildren);
    freeMessages(messages,numOfChildren + 1);
    

    return 0;
}
