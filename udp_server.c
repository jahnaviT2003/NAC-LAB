#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#define PORT  8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *server_msg="ACK Received - ";
    struct sockaddr_in servaddr, cliaddr;
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("Socket Creation Failed..!!");
        exit(EXIT_FAILURE);
    }
    else {
        printf("\nSocket Created Successfully..!!\n");
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family    = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("Bind Failed...!!");
        exit(EXIT_FAILURE);
    }
    else{
    printf("Socket successfully binded..!!\n");
    }
    int len, n;
    printf("Waiting for frames from client side..!!\n");
    len = sizeof(cliaddr);  
    for (int i=0;i<5;i++){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("\nClient : %s\n", buffer);
    sendto(sockfd, (const char *)server_msg, strlen(server_msg), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Acknowledgement - %d sent from server side....!\n",i+1); 
    }
    printf("\nReceived 5 Frames..!!\n");
    printf("Conversation ended succesfully..!!\n");
    return 0;
}

