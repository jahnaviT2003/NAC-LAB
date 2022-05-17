#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<string.h>
#define PORT 8080

 int main(int argc, char const *argv[])
 {
     int sock = 0, valread;
     struct sockaddr_in serv_addr;
     char hello[100];
     printf("Enter any string: ");
     fgets(hello, 100, stdin);
     char buffer[1024] = {0};
     char vowel[1024] = {0};

     if((sock=socket(AF_INET, SOCK_STREAM, 0))<0)
     {
         printf("\n Socket Creation Error \n");
         return -1;
     }
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(PORT);

     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <=0)
     {
         printf("\nInvalid address \n");
         return -1;
     }
     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
     {
         printf("\nConnection Failed \n");
         return -1;
     }
     printf("Connected with SERVER\n");
     printf("Hello,from server Side !\n");
     send (sock, hello, strlen(hello), 0);
     printf("Message sent Successfully..!\n");
     valread = read(sock, buffer, 1024);
     printf("%s\n",buffer);
     valread = read(sock, vowel, 1024);
     printf("No of vowels in the string : %s\n",vowel);
     return 0;
 }
