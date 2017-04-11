#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <pthread.h>
#include <fcntl.h>

#define BUF_SIZE 1024
#define NAME_SIZE 100
#define SAVE_SIZE 100

typedef struct sockaddr_in sockaddr_in;
typedef enum {false, true} bool;

static int recv_len;
static int clnt_sock;
static char inputBuf[BUF_SIZE];
static char outputBuf[BUF_SIZE];
static char clientSaveBuf[SAVE_SIZE * BUF_SIZE];

static char myName[NAME_SIZE];
bool clientIsConnected = false;

void connectToServer();
void error(char * message);
static void *thread1Func(void *v);
static void *thread2Func(void *v);
void setName();

void filesave(void * str, size_t nbytes);
void fileopen(char * buffer, ssize_t nread);

void filesave(void * str, size_t nbytes)
{
    int fd = 0;
    if(0<(fd = open("./clientChat.txt",O_RDWR|O_CREAT|O_APPEND,00777)))
    {
        write(fd, str, nbytes);
        close(fd);
    }
}

void fileopen(char * buffer, ssize_t nread)
{
    // 여기 저장, 로드하는 것부터 시작해야함.
    int fd = open("clientChat.txt",O_RDWR);
    nread = read(fd, clientSaveBuf, BUF_SIZE * SAVE_SIZE);
    printf("%s", clientSaveBuf);
    close(fd);    
}

void connectToServer()
{
    sockaddr_in clnt_addr;
    socklen_t clnt_addr_sz;
    char PORT[5];
    char IP[16];

	strcpy(IP, "127.0.0.1");
    strcpy(PORT, "5000");

    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1)
		error("socker() error");

    memset(&clnt_addr, 0, sizeof(clnt_addr));
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(IP);
    clnt_addr.sin_port = htons(atoi(PORT));

    clnt_addr_sz = sizeof(clnt_addr);
    if (connect(clnt_sock, (struct sockaddr *)&clnt_addr, clnt_addr_sz) == -1)
		error("connect() error");

    printf("상대방과 연결 되었습니다\n");
	clientIsConnected = true;
}

void error(char *message)
{
    fputs(message, stderr);
    fputc(' ', stderr);
    exit(1);
}

void *thread1Func(void *v) // read and print
{
	while (1)
	{
		recv_len = read(clnt_sock, inputBuf, BUF_SIZE);
		if (recv_len > 1)
		{
			inputBuf[recv_len] = 0;

			if (strcmp(inputBuf, "q") == 0)
			{
				printf("상대방이 채팅을 종료하였습니다.\n");
				printf("서버가 종료되었습니다.\n");
				clientIsConnected = false;
				break;
			}

			if (strcmp(inputBuf, "test") == 0)
			{
				printf("test recognized.\n");
				continue;
			}

			printf("%s\n", inputBuf);

			strcat(inputBuf, "\n");
            filesave(inputBuf, strlen(inputBuf));
		}
	}

	return NULL;
}

void *thread2Func(void *v) // write and send
{
	char tempBuf[BUF_SIZE] = { 0, };

	while (1)
	{
		fgets(tempBuf, BUF_SIZE, stdin);
        tempBuf[strlen(tempBuf) - 1] = '\0';

		if (strcmp(tempBuf, "load") == 0)
        {
            fileopen(clientSaveBuf, BUF_SIZE * SAVE_SIZE);
            printf("채팅 정보가 로드되었습니다.\n");
            continue;
        }

		if (strcmp(tempBuf, "q") == 0)
        {
			write(clnt_sock, tempBuf, BUF_SIZE);
            clientIsConnected = false;
            break;
        }

        strcpy(outputBuf, myName);
        strcat(outputBuf, " : ");
        strcat(outputBuf, tempBuf);

	    write(clnt_sock, outputBuf, BUF_SIZE);

		strcat(outputBuf, "\n");
        filesave(outputBuf, strlen(outputBuf));
	}
	
	return NULL;
}

void setName()
{
	printf("채팅아이디를 입력하세요 :");
	fgets(myName, NAME_SIZE, stdin);
	myName[strlen(myName) - 1] = '\0';
}

int main()
{
	pthread_t th1, th2;

	setName();
	connectToServer();

	if (pthread_create(&th1, NULL, thread1Func, NULL))
    {
        error("error making thread 1\n");
    }

    if (pthread_create(&th2, NULL, thread2Func, NULL))
    {
        error("error making thread 2\n");
    }

    while (1) 
	{
		if (!clientIsConnected)
		{
			printf("채팅을 종료합니다.\n");
			break;
		}
	}

    close(clnt_sock);

    return 0;
}
