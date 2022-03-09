// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/time.h>

#define PORT	8080
#define MAXLINE 1

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *msg = "c";
	struct sockaddr_in	 servaddr;

    // Time measurement stuff
    struct timeval t1, t2;
    int elapsedTime;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	socklen_t len = 0;
    int n = 0;
	
    while(1)
    {
        gettimeofday(&t1, NULL);
        sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_usec - t1.tv_usec);
        printf("elapsed time: %d\n", elapsedTime);
    }

	close(sockfd);
	return 0;
}
