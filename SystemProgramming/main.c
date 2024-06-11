#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "file_operations.h"
#include "system_operations.h"
#include "ipc_operations.h"

int main() {
    const char *src_file = "example.txt";

    // 디렉터리 내용 출력
    list_directory(".");

    // 파일 입/출력 예시 실행
    file_io_example();

    // 파일 정보 출력
    print_file_info(src_file);

    // 시스템 정보 출력
    print_system_info();

    // 프로세스 정보 출력
    print_process_info();

    // 프로세스 생성 및 명령 실행
    create_process_example("ls");

    // 시그널 핸들러 설정
    signal(SIGINT, signal_handler);
    printf("Press Ctrl+C to send SIGINT\n");
    sleep(5);

    // 메모리 매핑 예시
    memory_mapping_example();

    // 파이프 예시
    pipe_example();

    // 메시지 큐 예시
    message_queue_example("Message queue example");

    // 공유 메모리 예시
    shared_memory_example("Shared memory example");

    return 0;
}

