#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

void ErrorHandling(const char* functionName, int errorCode);

int main(int argc,char* argv[]){
    WSADATA WSAData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;

    char message[30];
    int strLen;
    if(argc != 3){
        printf("Usage : %s <IP> <Port> \n",argv[0]);
        exit(1);
    }    

    if(WSAStartup(MAKEWORD(2,2),&WSAData)!=0)
        ErrorHandling("WSAStartup",WSAGetLastError());
    
    hSocket = socket(PF_INET,SOCK_STREAM,0);
    if(hSocket == INVALID_SOCKET)
        ErrorHandling("socket",WSAGetLastError());

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(argv[1]);
    servAddr.sin_port=htons(atoi(argv[2]));

    if(connect(hSocket,(SOCKADDR*)&servAddr,sizeof(servAddr))== SOCKET_ERROR)
        ErrorHandling("connect",WSAGetLastError());
    
    strLen = recv(hSocket,message,sizeof(servAddr)-1,0);
    if(strLen == -1 )
        ErrorHandling("connect",WSAGetLastError());
    
    printf("Message from server: %s \n",message);

    closesocket(hSocket);
    WSACleanup();
    return 0;
}

void ErrorHandling(const char* functionName, int errorCode) {
    fprintf(stderr, "%s() failed with error %d\n", functionName, errorCode);
    exit(1);
}
