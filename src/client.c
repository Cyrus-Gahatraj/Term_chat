#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include "common.h"


struct sockaddr_in address;

typedef struct User {
	char name[32];
	char message[512];
} User;

User user;

void set_name(int sock){
	printf("What's your name: ");
	fgets(user.name, sizeof(user.name), stdin);
	user.name[strlen(user.name) - 1] = '\0';
	send(sock, user.name, strlen(user.name) + 1, 0);
}

void* recv_message(void * arg){
	int sock = *(int*)arg;

	char buffer[600];
	while (1) {
		recv(sock, buffer, sizeof(buffer), 0);
		printf("%s\n", buffer);
		fflush(stdout);
	}

	return NULL;
}

int main() {

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &address.sin_addr);

	int connection = connect(sock, (void*) &address, sizeof(address));
	if (connection != 0){
		perror("Connetion was not made properly\n");
		exit(1);
	}
	
	pthread_t t;
	pthread_create(&t, NULL, &recv_message, &sock);

	set_name(sock);
	 while(1){
		fgets(user.message, sizeof(user.message), stdin);
		user.message[strlen(user.message) - 1] = '\0';
		if (strcmp(user.message, "/exit") == 0) {
			char leave_message[8] = "/exit";
			send(sock, leave_message, sizeof(leave_message), 0);
			printf("Thank's for using\n");
			break;
		}
		send(sock, user.message, strlen(user.message), 0);
	}

	close(sock);
	return 0;
		
}
