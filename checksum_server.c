#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int binadd(int xy,int y,int carry)
{
    int c=xy^y^carry;
    return c;
}
void octetbin(int y,int a[8])
{
    if(y>=128)
    {
        a[0]=1;
        y=y-128;
    }
    if(y>=64)
    {
        a[1]=1;
        y=y-64;
    }
    if(y>=32)
    {
        a[2]=1;
        y=y-32;
    }
    if(y>=16)
    {
        a[3]=1;
        y-=16;
    }
    if(y>=8)
    {
        a[4]=1;
        y-=8;
    }
    if(y>=4)
    {
        a[5]=1;
        y-=4;
    }
    if(y>=2)
    {
        a[6]=1;
        y-=2;
    }
    if(y==1)
    a[7]=1;
}
void display(int x[16])
{
    for(int i=0;i<16;i++)
    printf("%d ",x[i]);
    printf("\n");
}
int main(int argc, char const *argv[])
{
    int sockfd, new_socket, valread;
    struct sockaddr_in sockadd;
    int opt = 1;
    char *hello="Hey there!";
    int addrlen = sizeof(sockadd);
    char buffer[100] = {0};
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Socket created successfully !!\n");
    }
       
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    sockadd.sin_family = AF_INET;
    sockadd.sin_addr.s_addr = INADDR_ANY;
    sockadd.sin_port = htons( PORT );
    if (bind(sockfd, (struct sockaddr *)&sockadd, sizeof(sockadd))<0)
    {
        perror("Binding socket failed.");
        exit(EXIT_FAILURE);
    }
    else 
    {
        printf("Socket binding..!!\n");
    }
    if (listen(sockfd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Socket Listening !!\n");
    }
    if ((new_socket = accept(sockfd, (struct sockaddr *)
    &sockadd, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Socket Accepted successfully..!!!\n");
    }
    int i,i1,i2,i3;
    valread = read( new_socket , buffer, 100);
    i1=atoi(buffer);
    valread = read( new_socket , buffer, 100);
    i2=atoi(buffer);
    valread = read( new_socket , buffer, 100);
    i3=atoi(buffer);
    int version[4]={0,1,0,0};
    int idl[4]={0,0,0,0};
    if(i1>=8)
    {
    idl[0]=1;
    i1=i1-8;
    }
    if(i1>=4)
    {
        idl[1]=1;
        i1=i1-4;
    }
    if(i1>=2)
    {
        idl[2]=1;
        i1=i1-2;
    }
    if(i1==1)
    idl[3]=1;
    int totlen[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int service[8]={0,0,0,0,0,0,0,0};
    int protocol[8]={0,0,0,0,0,1,1,0};
    int flag[3]={0,0,0};
    if(i2>=4)
    {
        flag[0]=1;
        i2=i2-4;
    }
    if(i2>=2)
    {
        flag[1]=1;
        i2=i2-2;
    }
    if(i2==1)
    flag[2]=1;
    int id[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int offset[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    int t2l[]={0,0,0,0,0,0,0,0};
    octetbin(i3,t2l);
    int source1[]={1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0};
    int source2[]={0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0};
    int dest2[]={0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0};
    int vr_idl_ser[16]={0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(i=0;i<4;i++)
    {
        vr_idl_ser[i+4]=idl[i];
    }
    int flag_frag[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(i=0;i<3;i++)
    {
        flag_frag[i]=flag[i];
    }
    int pr_t2l[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(i=0;i<8;i++)
    {
        pr_t2l[i+8]=t2l[i];
    }
    int x;
    x=15;
    int sum[16],carry;
    carry=0;
    while(x!=-1)
    {
        sum[x]=binadd(vr_idl_ser[x],flag_frag[x],carry);
        if((vr_idl_ser[x]==1&&flag_frag[x]==1)||(carry==1))
        carry=1;
        else
        carry=0;
        x--;   
    }
    x=15;
    carry=0;
    while(x!=-1)
    {
        sum[x]=binadd(sum[x],pr_t2l[x],carry);
        if((sum[x]==1&&pr_t2l[x]==1)||(carry==1))
        carry=1;
        else
        carry=0;
        x--;   
    }
    x=15;
    carry=0;
    while(x!=-1)
    {
        sum[x]=binadd(sum[x],source1[x],carry);
        if((sum[x]==1&&source1[x]==1)||(carry==1))
        carry=1;
        else
        carry=0;
        x--;   
    }
    x=15;
    carry=0;
    while(x!=-1)
    {
        sum[x]=binadd(sum[x],source2[x],carry);
        if((sum[x]==1&&source2[x]==1)||(carry==1))
        carry=1;
        else
        carry=0;
        x--;   
    }
    x=15;
    carry=0;
    while(x!=-1)
    {
        sum[x]=binadd(sum[x],source1[x],carry);
        if((sum[x]==1&&source1[x]==1)||(carry==1))
        carry=1;
        else
        carry=0;
        x--;   
    }
    x=15;
    carry=0;
    while(x!=-1)
    {
        sum[x]=binadd(sum[x],dest2[x],carry);
        if((sum[x]==1&&dest2[x]==1)||(carry==1))
        carry=1;
        else
        carry=0;
        x--;   
    }
    printf("CHECKSUM : \n");
    for(int i=0;i<16;i++)
    {
        if(sum[i]==1)
        printf("0 ");
        else
        printf("1 ");
    }
    printf("\n");
    return 0;
}
