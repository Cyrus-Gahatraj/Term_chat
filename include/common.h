#pragma once
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 7007
#define IP "127.0.0.1"

typedef struct User {
	char name[32];
	char message[512];
} User;

int get_tcp4() {
	return socket(AF_INET, SOCK_STREAM, 0);
}

void connect_tcp4(struct sockaddr_in *address) {
	address->sin_family = AF_INET;
	address->sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &address->sin_addr);
} 
