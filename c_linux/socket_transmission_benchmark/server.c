/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr, "ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
         error("ERROR on binding");
     listen(sockfd, 5);
     clilen = sizeof(cli_addr);
		 printf("\n");
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer, 256);
     if ((n = read(newsockfd, buffer, 255)) >= 2) {
			 time_t t1, t0 = clock();
			 long bandwidth = 0;
			 while ((n = read(newsockfd, buffer, 255)) >= 2) {
				 bandwidth += n;
				 t1 = clock();
				 if (t1 - t0 > 10 * CLOCKS_PER_SEC) {
					 break;
				 }
			 }
			 printf("%ld\n", t0);
			 printf("%ld\n", t1);
			 printf("%ld\n", CLOCKS_PER_SEC);
			 //printf("Received %ld in %ld second(s)", bandwidth, (t1 - t0) / CLOCKS_PER_SEC);
			 printf("Received %ld in %ld second(s)", bandwidth, (t1 - t0) / CLOCKS_PER_SEC);
		 }
     printf("Connection closed\n");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
