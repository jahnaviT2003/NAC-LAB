#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8080
#define SA struct sockaddr
int sum[16];
int checksum[16];
int* inttobin(int* arr, int n, int x)
{
	int i;
	for(i=0;i<x;i++)
	{
		arr[i]=n%2;
		n=n/2;	
	}
	return arr;	
}
void display(int arr[], int x)
{
	for(int i=x-1;i>=0;i--)
		printf("%d", arr[i]);
	printf("\n");
}
void disp(int arr[], int x)
{
	for(int i=0;i<x;i++)
		printf("%d", arr[i]);
	printf("\n");
}

int* summation(int bin1[], int bin2[])
{
    // int sum[16];
    int i;
    int carry=0;
    for(i=0;i<16;i++)
    {
        if(bin1[i]==0 && bin2[i]==0 && carry==0)
            {
                sum[i]=0;
                carry=0;
            }
            else if(bin1[i]==0 && bin2[i]==0 && carry==1)
            {
                sum[i]=1;
                carry=0;
 
            }
            else if(bin1[i]==0 && bin2[i]==1 && carry==0)
            {
                sum[i]=1;
                carry=0;
 
            }
            else if(bin1[i]==0 && bin2[i]==1 && carry==1)
            {
                sum[i]=0;
                carry=1;
 
            }
            else if(bin1[i]==1 && bin2[i]==0 && carry==0)
            {
                sum[i]=1;
                carry=0;
 
            }
            else if(bin1[i]==1 && bin2[i]==0 && carry==1)
            {
                sum[i]=0;
                carry=1;
 
            }
            else if(bin1[i]==1 && bin2[i]==1 && carry==0)
            {
                sum[i]=0;
                carry=1;
 
            }
            else if(bin1[i]==1 && bin2[i]==1 && carry==1)
            {
                sum[i]=1;
                carry=1;
 
            }
            else
                break;
        }
    return sum;
}
void check_sum(int arr[])
{
	for(int i=0; i<=15; i++)
	{
		if(arr[i]==1)
			checksum[i]=0;
		else
			checksum[i]=1;
	}
}
void func(int sockfd)
{
	int buff;
	buff=0;
	read(sockfd, &buff, sizeof(int));
	int ver[4];     
	inttobin(ver, buff, 4);
	printf("Version: ");
	display(ver,4);
	int buff1=0;
	read(sockfd, &buff1, sizeof(int));
	//printf("%d", buff1);
	int hlen[4];
	inttobin(hlen, buff1, 4);
	printf("Internet Header Length: ");
	display(hlen, 4);
	int buff2=0;
	read(sockfd, &buff2, sizeof(int));
	int ds[8];
	inttobin(ds, buff2, 8);
	printf("Type of Service: ");
	display(ds, 8);
	int buff3=0;
	read(sockfd, &buff3, sizeof(int));
	int totallength[16];
	inttobin(totallength, buff3, 16);
	printf("Total Length");
	display(totallength, 16);
	int buff4=0;
	read(sockfd, &buff4, sizeof(int));
	int identification[16];
	inttobin(identification, buff4, 16);
	printf("Identification: ");
	display(identification, 16);

    	int buff5=0;
	read(sockfd, &buff5, sizeof(int));
	int flags[3];
	inttobin(flags, buff5, 3);
	printf("Flags: ");
	display(flags, 3);

    	int buff6=0;
	read(sockfd, &buff6, sizeof(int));
	int fo[13];
	inttobin(fo, buff6, 13);
	printf("Fragment Offset: ");
	display(fo, 13);

    	int buff7=0;
	read(sockfd, &buff7, sizeof(int));
	int ttl[8];
	inttobin(ttl, buff7, 8);
	printf("Time to Live: ");
	display(ttl, 8);

    	int buff8=0;
	read(sockfd, &buff8, sizeof(int));
	int protocol[8];
	inttobin(protocol, buff8, 8);
	printf("Protocol: ");
	display(protocol, 8);

    	int row1[16], i;
    	for(i=0; i<4; i++)
    	{
    		row1[i]=ver[3-i];
    	}
    	for(int j=0; j<4; j++)
    	{
    		row1[i]=hlen[3-j];
    		i++;
    	}
    	for(int j=0; j<8; j++)
    	{
    		
    		row1[i]=ds[7-j];
    		i++;
    	}
    	//disp(row1, 16);
    	int row2[16];
    	for(i=0; i<16;i++)
    	{
    		row2[i]=totallength[15-i];
    	}
    	int row3[16];
    	for(i=0; i<16;i++)
    	{
    		row3[i]=identification[15-i];
    	}
    	int row4[16];
    	for(i=0; i<3; i++)
    	{
    		row4[i]=flags[2-i];
    	}
    	for(int j=0; j<13; j++)
    	{
    		row4[i]=fo[12-j];
    		i++;
    	}
    	int row5[16];
    	for(i=0; i<8; i++)
    	{
    		row5[i]=ttl[7-i];
    	}
    	for(int j=0; j<8; j++)
    	{
    		row5[i]=protocol[7-j];
    		i++;
    	}
    	//disp(row1,16);
    	//disp(row2,16);
    	//disp(row3,16);
    	//disp(row4,16);
    	//disp(row5, 16);
    	summation(row1, row2);
    	summation(sum, row3);
    	summation(sum, row4);
    	summation(sum, row5);
    	printf("Sum: ");
    	disp(sum, 16);
    	check_sum(sum);
    	printf("Header Checksum: ");
    	disp(checksum, 16);
    	write(sockfd, checksum, sizeof(checksum));
}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}