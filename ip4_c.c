#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
	int buff;
	buff=0;
	printf("Enter the Version : ");
	scanf("%d", &buff);
	write(sockfd, &buff, sizeof(int));
	int buff1=0;
	printf("Enter the Header Length: ");
	scanf("%d", &buff1);
	write(sockfd, &buff1, sizeof(int));
	int buff2=0;
	printf("Enter the Type of Service: ");
	scanf("%d", &buff2);
	write(sockfd, &buff2, sizeof(int));
	int buff3=0;
	printf("Enter the Total Length: ");
	scanf("%d", &buff3);
	write(sockfd, &buff3, sizeof(int));
	int buff4=0;
	printf("Enter the Identification: ");
	scanf("%d", &buff4);
	write(sockfd, &buff4, sizeof(int));
    	int buff5=0;
	printf("Enter the Flags: ");
	scanf("%d", &buff5);
	write(sockfd, &buff5, sizeof(int));
    	int buff6=0;
	printf("Enter the Fragmentation Offset: ");
	scanf("%d", &buff6);
	write(sockfd, &buff6, sizeof(int));
    	int buff7=0;
	printf("Enter the Time to Live: ");
	scanf("%d", &buff7);
	write(sockfd, &buff7, sizeof(int));
    	int buff8=0;
	printf("Enter the Protocol: ");
	scanf("%d", &buff8);
	write(sockfd, &buff8, sizeof(int));
	int checksum[16];
	bzero(checksum, sizeof(checksum));
	
	read(sockfd, checksum, sizeof(checksum));
	printf("Header Checksum from Server: ");
	for(int i=0; i<16; i++)
	{
		printf("%d", checksum[i]);
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	func(sockfd);

	// close the socket
	close(sockfd);
}