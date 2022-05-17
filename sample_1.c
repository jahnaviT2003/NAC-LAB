#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <unistd.h>
int main()
{
int port_number;
printf("Input the port number");
scanf("%d",&port_number);
//Creation of the server socket
int server_socket;
server_socket=socket(AF_INET,SOCK_STREAM,0);
//Definition of the server address
struct sockaddr_in server_addr;
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(port_number);
server_addr.sin_addr.s_addr=INADDR_ANY;
//To bind the socket
bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
listen(server_socket,5);
//Accepting the request for connection
int client_socket;
client_socket=accept(server_socket,NULL,NULL);
int window_size=6,ack=0;
while(ack<window_size)
{
for(int i=ack;i<window_size;i++)
{
printf("Frame %d transmitted\n",i);
int code=send(client_socket,&i,sizeof(i),0);
}
recv(client_socket,&ack,sizeof(ack),0);
printf("the ack recieved %d\n",ack);
}
close(server_socket);
 return 0;
}

