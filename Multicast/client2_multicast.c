#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>

struct sockaddr_in localSock;
struct ip_mreq group;
int sd;
int len;
char buffer[1000];
int main (int argc, char *argv[])
{

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("opening datagram socket");
		exit(EXIT_FAILURE);
	}
	
	{
	int reuse=1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) {
		perror("setting SO_REUSEADDR");
		close(sd);
		exit(EXIT_FAILURE);
	}
	}

	memset((char *) &localSock, 0, sizeof(localSock));
	localSock.sin_family = AF_INET;
	localSock.sin_port = htons(5555);;
	localSock.sin_addr.s_addr = INADDR_ANY;
	if (bind(sd, (struct sockaddr*)&localSock, sizeof(localSock))) {
		perror("binding datagram socket");
		close(sd);
		exit(EXIT_FAILURE);
	}
	
	group.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
	group.imr_interface.s_addr = inet_addr("127.0.0.1");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0) {
		perror("adding multicast group");
		close(sd);
		exit(EXIT_FAILURE);
	}
	printf("After ipproto, reading...\n");
	len=sizeof(buffer);
	if (read(sd, buffer, len) < 0) {
		perror("reading datagram message");
		close(sd);
		exit(EXIT_FAILURE);
	}
	printf("Message from server: %s",buffer);
	
}
