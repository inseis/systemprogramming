CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = backup_system

OBJS = main.o file_operations.o system_operations.o ipc_operations.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c file_operations.h system_operations.h ipc_operations.h
	$(CC) $(CFLAGS) -c main.c

file_operations.o: file_operations.c file_operations.h
	$(CC) $(CFLAGS) -c file_operations.c

system_operations.o: system_operations.c system_operations.h
	$(CC) $(CFLAGS) -c system_operations.c

ipc_operations.o: ipc_operations.c ipc_operations.h
	$(CC) $(CFLAGS) -c ipc_operations.c

clean:
	rm -f $(TARGET) $(OBJS)

