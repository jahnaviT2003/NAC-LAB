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
    char str_msg[100];
    struct sockaddr_in  servaddr;

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("\nSocket Created Successfully..!!\n");
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    int n, len;
    for (int i=0;i<5;i++){
    printf("\nEnter any Message : ");
    fgets(str_msg, 100, stdin);
    sendto(sockfd, (const char *)str_msg, strlen(str_msg),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Message has been sent..!\n");
          
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server msg : %s %d\n",buffer,i+1);
    }
    close(sockfd);
    printf("\nSent 5 Frames..!!\n");
    printf("Conversation ended succesfully..!!\n");
    printf("Thank you!\n");
    return 0;
}




