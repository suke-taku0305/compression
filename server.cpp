#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
using namespace std;


int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM, 0);
    if(sockfd < 0){
        cout << "Error socket:" << strerror(errno);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) <0){
        cout << "Error bind:" << strerror(errno);
        exit(1);
    }

    if(listen(sockfd, SOMAXCONN) < 0){
        cout << "Error listen:" << strerror(errno);
        close(sockfd);
        exit(1);
    }

    struct sockaddr_in get_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int connect = accept(sockfd, (struct sockaddr*)&get_addr, &len);

    if(connect < 0){
        cout << "Error accept:" << strerror(errno);
        exit(1);
    }

    char str[12];
    recv(connect, str, 12, 0);
    cout << str << endl;

    send(connect, str, 12, 0);
    cout << str << endl;

    close(connect);
    close(sockfd);

    return 0;
}