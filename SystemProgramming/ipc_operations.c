#include "ipc_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <dirent.h>
#include <errno.h>

#define SHM_SIZE 1024  // 공유 메모리 크기

const char *shm_key_file = "/tmp/shm_example";
#define MSG_KEY 1234

struct msgbuf {
    long mtype;
    char mtext[100];
};

// 파이프를 사용하는 함수
void pipe_example() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[100];

    if (pipe(pipe_fd) < 0) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스
        close(pipe_fd[0]);
        write(pipe_fd[1], "Hello from child", 16);
        close(pipe_fd[1]);
    } else {
        // 부모 프로세스
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, 16);
        printf("Received from child: %s\n", buffer);
        close(pipe_fd[0]);
    }
}

// 메시지 큐를 사용하는 함수
void message_queue_example(const char *message) {
    int msgid;
    struct msgbuf msg;

    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    msg.mtype = 1;
    strncpy(msg.mtext, message, sizeof(msg.mtext));
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) < 0) {
        perror("msgsnd");
        exit(1);
    }
}

// 공유 메모리를 사용하는 함수
void shared_memory_example(const char *message) {
    int shm_fd;
    char *shm_addr;

    // 공유 메모리가 존재할 경우 삭제
    shm_unlink(shm_key_file);

    // 공유 메모리 객체 생성
    shm_fd = shm_open(shm_key_file, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        perror("shm_open");
        exit(1);
    }

    // 공유 메모리 크기 설정
    if (ftruncate(shm_fd, SHM_SIZE) != 0) {
        perror("ftruncate");
        close(shm_fd);
        exit(1);
    }

    // 공유 메모리 매핑
    shm_addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        exit(1);
    }

    // 공유 메모리에 메시지 저장
    strncpy(shm_addr, message, SHM_SIZE);

    // 공유 메모리 언매핑 및 파일 디스크립터 닫기
    munmap(shm_addr, SHM_SIZE);
    close(shm_fd);
}

