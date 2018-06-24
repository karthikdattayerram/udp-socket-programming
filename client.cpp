#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAX 255

using namespace std;

// void send_message(struct sockaddr_in servaddr, int sockfd){
    
//     char str[MAX];

//     while(1){

//     fgets(str, MAX, stdin);
     
//     sendto(sockfd, (const char *)str, strlen(str),
//         MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
//             sizeof(servaddr));

//     }
// }

// void read_message(struct sockaddr_in servaddr, int sockfd){

//     char buffer[MAX];

//     int n;
//     socklen_t len;

//     n = recvfrom(sockfd, (char *)buffer, MAX, 
//                 0, (struct sockaddr *) &servaddr,
//                 &len);

//     buffer[n] = '\0';
//     printf("Server : %s\n", buffer);

// }
 
int main(int argc, char const *argv[]) {

     if(argc < 2){
        printf("Port number not provided. \n");
        return 0;
    }

    char buffer[MAX];
    char str[MAX];
    int port_no = atoi(argv[1]);
    
    struct sockaddr_in servaddr;
 
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);        

    if(sockfd < 0){                                    //returns non negative integer if successful
        perror("Failed to create a socket");
        return 0;
    }

    //We do not bind the socket to a port for a client because it does not matter
    //which port you use to send the data
    //The port that receives the data is important so we bind the server socket

    memset(&servaddr, 0, sizeof(servaddr));
 
    // Filling server information
    servaddr.sin_family = AF_INET;
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_addr.s_addr = inet_addr("15.19.67.1");
    servaddr.sin_port = htons(port_no);
     
    int n;
    socklen_t len;

    while(1){

    fgets(str, MAX, stdin);
     
    sendto(sockfd, (const char *)str, strlen(str),
        0, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    
         
    n = recvfrom(sockfd, (char *)buffer, MAX, 
                0, (struct sockaddr *) &servaddr,
                &len);

    //printf("Hello \n");


    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

}
 
    close(sockfd);
    return 0;
}