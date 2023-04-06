#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
using namespace std;

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        cout << "Error socket:" << strerror(errno);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd,(struct sockaddr *) &addr, sizeof(struct sockaddr_in));

    char s_str[] = "Hello World!";
    send(sockfd, s_str, 12, 0);
    cout << s_str << endl;

    char r_str[12];
    recv(sockfd, r_str, 12, 0);
    cout << r_str << endl;

    close(sockfd);

    return 0;
}