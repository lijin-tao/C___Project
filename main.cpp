#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>

using namespace std;
void process_conn_server(int s){
    char buffer[]="D1593076-F4CF-184F-F3D2-1687845AA6EE\n";
    send(s,buffer, std::strlen(buffer)+1 ,0);

}
int main(){
    pid_t pid;
    struct sockaddr_in addr_in;
    struct sockaddr_in Caddr_in;
    int sockfd,Csockfd;
    int CaddrLen;
    sockfd= socket(AF_INET,SOCK_STREAM,0);
    addr_in.sin_family=AF_INET;
    addr_in.sin_port= htons(1080);
    inet_pton(AF_INET,"0.0.0.0",&addr_in.sin_addr.s_addr);
    bzero(&(addr_in.sin_zero),8);
    if (bind(sockfd,(sockaddr*)&addr_in, sizeof(addr_in))==-1){
        return -1;
    }
    if (listen(sockfd,5)==-1){
        return -1;
    }
    for(;;){
        socklen_t addrlen=sizeof(struct sockaddr);
        Csockfd= accept(sockfd,(sockaddr *)&Caddr_in,&addrlen);
        if (Csockfd<0){
            continue;
        }
        cout << "有程序接入连接" << inet_ntoa(Caddr_in.sin_addr) << endl;
        thread t(process_conn_server,Csockfd);
        t.detach();
    }

}
