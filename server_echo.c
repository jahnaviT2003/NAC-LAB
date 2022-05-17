#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 5035
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    int n;
    printf("Enter number of clients : ");
    scanf("%d",&n);
    printf("Server side:\n");
    printf("Waiting for the messages from the clients..!!\n");
    for (int i=0;i<n;i++) {
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        } else 
            printf("Creating the Socket...!!\n");
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                    &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        } 
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );

        if (bind(server_fd, (struct sockaddr *)&address, 
                                    sizeof(address))<0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        } else 
            printf("Binding the socket..!!\n");
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        } else 
            printf("Listening to the Client message..!!\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                        (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        } else 
            printf("Message Accepted Successfully..!!\n");
    
        valread = read( new_socket , buffer, 1024);
        printf("Client Side-%d : %s\n",i+1,buffer);
        printf("Server Side : Client message received and echoed successfully !\n");
    }
    return 0;
}
