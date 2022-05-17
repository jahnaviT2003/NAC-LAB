#include <stdio.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in server;
    char *str_1=malloc(80);
    char *str_2=malloc(80);
    char *str_3=malloc(80);
    int x1,x2,x3;
    char buffer[100] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0) 
    {
        printf("\nAddress not supported!\n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    int i;
    printf("Enter length of the header : ");
    fgets(str_1,80,stdin);
    send(sock ,str_1, strlen(str_1),0);
    printf("Message successfully sent by the client !!\n");
    printf("Enter flag value : ");
    fgets(str_2,80,stdin);
    send(sock ,str_2 ,strlen(str_2) ,0);
    printf("Message successfully sent by the client !!\n");
    printf("Enter time to live : ");
    fgets(str_3,80,stdin);
    send(sock ,str_3 ,strlen(str_3) ,0);
    printf("Message successfully sent by the client !!\n");
    return 0;
}
