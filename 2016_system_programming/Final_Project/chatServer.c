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

#define MYMESSAGEPOS_Y 23
#define CHATMESSAGEPOS_Y 0
#define NOTIFICATION_Y 21
#define CHATMESSAGE_LONG 16

typedef struct sockaddr_in sockaddr_in;
typedef enum {false, true} bool;

static char inputBuf[BUF_SIZE];
static char outputBuf[BUF_SIZE];
static char serverSaveBuf[SAVE_SIZE * BUF_SIZE] = { 0, };

char myFuckingName[NAME_SIZE];

static int serv_sock, clnt_sock;
static int recv_len;
bool serverIsConnected = false;
bool serverThreadMade = false;
static int nowChatNum = 0;

void connectWithClient();
static void *thread1Func(void *v);
static void *thread2Func(void *v);
void error(char * message);
void setName();

void filesave(void * str, size_t nbytes);
void fileopen(char * buffer,ssize_t nread);

void error(char *message)
{
    fputs(message, stderr);
    fputc(' ', stderr);
    exit(1);
}

void filesave(void * str, size_t nbytes)
{
    int fd = 0;
    if(0<(fd = open("./serverChat.txt",O_RDWR|O_CREAT|O_APPEND,00777)))
    {
        write(fd, str, nbytes);
        close(fd);
    }
}

void fileopen(char * buffer, ssize_t nread)
{
    // 여기 저장, 로드하는 것부터 시작해야함.
    int fd = open("serverChat.txt",O_RDWR);
    nread = read(fd, serverSaveBuf, BUF_SIZE * SAVE_SIZE);
    printf("%s", serverSaveBuf);
    close(fd);    
}

void * thread1Func(void * data) // read and print
{
    while(1)
    {
        recv_len = read(clnt_sock, inputBuf, BUF_SIZE);

        if (recv_len > 1)
        {
            inputBuf[recv_len] = 0;

            if (strcmp(inputBuf, "q") == 0)
            {
                printf("상대방이 채팅을 종료하였습니다.\n");
                serverThreadMade = false;
                break;
            }

            printf("%s\n", inputBuf);
            
            strcat(inputBuf, "\n");
            filesave(inputBuf, strlen(inputBuf));
        }
    }

    return NULL;
}

void * thread2Func(void * data) // write and send
{
    char tempBuf[BUF_SIZE] = { 0, };

    while (1)
    {
        fgets(tempBuf, BUF_SIZE, stdin);
        tempBuf[strlen(tempBuf) - 1] = '\0';

        if(!serverThreadMade)
        {
            break;
        }

        if (strcmp(tempBuf, "load") == 0)
        {
            fileopen(serverSaveBuf, BUF_SIZE * SAVE_SIZE);
            printf("채팅 정보가 로드되었습니다.\n");
            continue;
        }

        if (strcmp(tempBuf, "q") == 0)
        {
            write(clnt_sock, tempBuf, BUF_SIZE);
            serverIsConnected = false;
            break;
        }

        strcpy(outputBuf, myFuckingName);
        strcat(outputBuf, " : ");
        strcat(outputBuf, tempBuf);

        write(clnt_sock, outputBuf, BUF_SIZE);

        strcat(outputBuf, "\n");
        filesave(outputBuf, strlen(outputBuf));
    }
    return NULL;
}

void connectWithClient()
{
    sockaddr_in serv_addr;
    sockaddr_in clnt_addr;
    char PORT[5];
    socklen_t clnt_addr_sz;

    if (!serverIsConnected)
    {
        strcpy(PORT, "5000"); // local port

        serv_sock = socket(PF_INET, SOCK_STREAM, 0); // id return?
        if (serv_sock == -1)
            error("socket() error");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(atoi(PORT));

        if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
            error("bind() error");

        if (listen(serv_sock, 5) == -1)
            error("listen() error");
    }

    printf("상대방을 기다리는 중입니다.\n");

    clnt_addr_sz = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_sock, &clnt_addr_sz);
    if(clnt_sock == -1)
        error("connect() error!");

    printf("상대방과 연결되었습니다.\n");
    serverIsConnected = true;
}

void setName()
{
	printf("채팅아이디를 입력하세요.");
	fgets(myFuckingName, NAME_SIZE, stdin);
    myFuckingName[strlen(myFuckingName) - 1] = '\0';
}

int main(int argc, char** argv)
{
    pthread_t th1, th2;

    system("clear");
    setName();

    while (1)
    {
        connectWithClient();

        if (!serverThreadMade)
        {
            serverThreadMade = true;
            if (pthread_create(&th1, NULL, thread1Func, NULL))
            {
                error("error making thread 1\n");
            }
            if (pthread_create(&th2, NULL, thread2Func, NULL))
            {
                error("error making thread 2\n");
            }
        }

        while (1)
        {
            if (!serverIsConnected)
            {
                break;
            }
            if (!serverThreadMade)
            {
                char ch = 0;
                printf("재연결을 시도합니다. 재연결을 기다리시겠습니까?(y/n) : ");
                scanf(" %c", &ch);
                if (ch == 'n')
                {
                    serverIsConnected = false;
                }
                break;
            }
        }
        if (!serverIsConnected)
        {
            printf("채팅을 종료합니다.\n");
            break;
        }
    }

    close(clnt_sock);
    close(serv_sock);

    return 0;
}
