#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int count_vowels(char *string)
{
    int vowels=0,consonants=0;
    int i;
    char s;
    for (i=0;string[i] !='\0';i++)
    {
        s=string[i];
        if(s=='A' || s=='E' || s=='I' || s=='O' || s=='U' || 
        s=='a' || s=='e' || s=='i' || s=='o' || s=='u')
            vowels++;
        else if(s==' ')
            continue;
    }
    return vowels;
}
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt=1;
    int addrlen =sizeof(address);
    char buffer[1024]={0};
    char *hello="Server is working with VOWELS Count...!!";
    char vowel_count[100];

    if((server_fd=socket(AF_INET, SOCK_STREAM, 0))==0)
    {
        perror("SOCKET FAILED");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, 
    SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);
    if(bind(server_fd,(struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("BIND FAILED");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3)<0)
    {
        perror("LISTEN");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, 
    (struct sockaddr *)&address, (socklen_t *)&addrlen))<0)
    {
        perror("ACCEPT");
        exit(EXIT_FAILURE);
    }
    printf("Connected with the CLIENT\n");
    printf("Socket Created Successfully..!!\n");
    printf("Message Received\n");
    valread = read(new_socket, buffer, 1024);
    printf("Received message is : ");
    printf("%s",buffer);
    int vol_count = count_vowels(buffer);
    sprintf(vowel_count,"%d",vol_count);
    send(new_socket, hello, strlen(hello), 0);
    printf("Server Message Sent\n");
    send(new_socket, vowel_count, strlen(vowel_count), 0);
    return 0;
}

