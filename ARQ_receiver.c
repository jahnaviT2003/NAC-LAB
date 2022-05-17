#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080

int main()
{
//CREATION OF SOCKET
int network_socket;
if ((network_socket=socket(AF_INET,SOCK_STREAM,0)) < 0)
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
//Establishing a Connection with the SENDER
int connection_status=connect(network_socket,(struct
sockaddr*)&server_addr,sizeof(server_addr));
//Check if there is some error in the connection
if(connection_status < 0)
{
printf("Connection Failed..!!\n");
}
else
{
 printf("Connected with the SENDER side !!\n");
}
int ack=0,nak=0,frame_size=6;
while(ack<frame_size)
{
 for(int i=ack;i<frame_size;i++)
{
int x;
recv(network_socket,&x,sizeof(x),0);
printf("Frame %d is Received.\n",x);
}
printf("Input the negative ACK : ");
scanf("%d",&ack);
int code=send(network_socket,&ack,sizeof(ack),0);
printf("ACK %d is Sent.\n",ack);
printf("Input the negative NAK : ");
scanf("%d",&nak);
int code_n=send(network_socket,&nak,sizeof(nak),0);
printf("NAK %d is Sent.\n",nak);
}
close(network_socket);
return 0;
}
