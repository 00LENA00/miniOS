#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int ipc_pipes(){
 char write_msg[BUFFER_SIZE]="Greetings";
 char read_msg[BUFFER_SIZE];
 int fd[2];
 pid_t pid;
 
 if (pipe(fd)==-1) { //create the pipe
  fprintf(stderr, "Pipe failed");
  return 1;
 }
 pid=fork(); //fork a child process
 if (pid<0) { /*error occurred*/
  fprintf(stderr, "Fork failed");
  return 1;
 }
 else if (pid>0) { /*parent process*/
  close(fd[READ_END]); //close the unused end of the pipe
  write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
  printf("write_msg -> %s\n", write_msg);
  close(fd[WRITE_END]);
  wait(0); //wait for child terminate
 }
 else { /*child process*/
  close(fd[WRITE_END]);
  read(fd[READ_END], read_msg, BUFFER_SIZE);
  printf("read_msg -> %s\n", read_msg);
  close(fd[READ_END]);
  exit(0); //child terminate
 }
 return 0;
}
