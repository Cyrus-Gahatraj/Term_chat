#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include "common.h"


struct sockaddr_in address;

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

	int client_sock = get_tcp4(); 
	connect_tcp4(&address);


	int connection = connect(client_sock, (void*) &address, sizeof(address));
	if (connection != 0){
		perror("Connetion was not made properly\n");
		exit(1);
	}
	
	pthread_t t;
	pthread_create(&t, NULL, &recv_message, &client_sock);

	set_name(client_sock);
	 while(1){
		fgets(user.message, sizeof(user.message), stdin);
		user.message[strlen(user.message) - 1] = '\0';
		if (strcmp(user.message, "/exit") == 0) {
			char leave_message[8] = "/exit";
			send(client_sock, leave_message, sizeof(leave_message), 0);
			printf("Thank's for using\n");
			break;
		}
		send(client_sock, user.message, strlen(user.message), 0);
	}

	close(client_sock);
	return 0;
		
}
