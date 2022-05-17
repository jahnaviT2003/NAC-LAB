#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080

int main()
{
//CREATION OF SERVER SOCKET.
int server_socket;
if ((server_socket=socket(AF_INET,SOCK_STREAM,0)) < 0)
{
    perror("Socket Creation Failed..!!");
    exit(EXIT_FAILURE);
}
else
{
    printf("\nSocket Created Successfully..!!\n");
}
//DEFINITION OF SERVER ADDRESS
struct sockaddr_in server_addr;
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);
server_addr.sin_addr.s_addr=INADDR_ANY;
//BINDING THE SOCKET
if (bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
{
    perror("Binding Failed...!!");
    exit(EXIT_FAILURE);
}
else
{
    printf("Socket successfully binded..!!\n");
}
//LISTENING
if (listen(server_socket,5) < 0)
{
    perror("Listen");
    exit(EXIT_FAILURE);
}
else
{
    printf("Listening to the Receiver's side message..!!\n");
}

//Accepting the request for connection
int client_socket;
client_socket=accept(server_socket,NULL,NULL);
int ack=0,nak=0;
int window_size=6;
printf("Waiting for the ACKNOWLEDGEMENTS from the RECEIVER..!!\n");
while(ack<window_size)
{
for(int i=ack;i<window_size;i++)
{
printf("Frame %d is Transmitted.\n",i);
int code=send(client_socket,&i,sizeof(i),0);
}
recv(client_socket,&ack,sizeof(ack),0);
printf("ACK %d is recieved..!!\n",ack);
recv(client_socket,&nak,sizeof(nak),0);
printf("NAK %d is recieved..!!\n",nak);
}
close(server_socket);
return 0;
}

