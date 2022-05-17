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
//Creation of the Server Socket
int network_socket;
network_socket=socket(AF_INET,SOCK_STREAM,0);
//Definition of the Server Address
struct sockaddr_in server_addr;
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(port_number);
server_addr.sin_addr.s_addr=INADDR_ANY;
//Establishing a Connection with the Server
int connection_status=connect(network_socket,(struct
sockaddr*)&server_addr,sizeof(server_addr));
//Check if there is some error in the connection
if(connection_status==-1)
{
printf("error");
}
else
{
 printf("Connected\n");
}
int ack=0,frame_size=6;
while(ack<frame_size)
{
 for(int i=ack;i<frame_size;i++)
{
int x;
recv(network_socket,&x,sizeof(x),0);
printf("\nFrame recieved %d",x);
}
printf("\nInput the negative ack");
scanf("%d",&ack);
int code=send(network_socket,&ack,sizeof(ack),0);
printf("\n The ack sent%d",ack);
}
close(network_socket);
return 0;
}
