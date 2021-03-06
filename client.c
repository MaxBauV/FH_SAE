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
#include "common.h"


// Driver code
int main() {
	int sockfd;
	char buffer[BUFF_SIZE];
    char msg[BUFF_SIZE] = {'c'};
	
	struct sockaddr_in	 servaddr;

    #if DEBUG
        long debug_data[3][MEASURE_CNT] = {0};
    #else
        long data[MEASURE_CNT] = {0};
    #endif

    FILE *csv_fpt;

    // Time measurement stuff
    struct timeval t1, t2;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = IP_HEX;
	
	socklen_t len = 0;
    int n = 0;
	
    // Send and receive UDP message. Measure time
    for (int i = 0; i < MEASURE_CNT; i++)
    {
        gettimeofday(&t1, NULL);
        sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
        n = recvfrom(sockfd, (char *)buffer, BUFF_SIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
        #if DEBUG
            printf("Client received[%d]: %s\n", i, buffer);
        #endif
        gettimeofday(&t2, NULL);
        #if DEBUG
            debug_data[0][i] = 1000000 * t1.tv_sec + t1.tv_usec;
            debug_data[1][i] = 1000000 * t2.tv_sec + t2.tv_usec;
            debug_data[2][i] = 1000000 * (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec);
        #else
            data[i] = 1000000 * (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec);
        #endif
    }
    close(sockfd);

    csv_fpt = fopen("Measurement.csv", "w+");

    #if DEBUG
        fprintf(csv_fpt,"t1, t2\n");
        for (int i = 0; i < MEASURE_CNT; i++)
        {
            fprintf(csv_fpt, "%ld, %ld, %ld\n", debug_data[0][i], debug_data[1][i], debug_data[2][i]);
        }
    #else
        fprintf(csv_fpt,"time\n");
        for (int i = 0; i < MEASURE_CNT; i++)
        {
            fprintf(csv_fpt, "%ld\n", data[i]);
        }
    #endif
    fclose(csv_fpt);

	return 0;
}
