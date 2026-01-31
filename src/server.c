#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include "common.h"

#define MAX_CLIENTS 100

int clients[MAX_CLIENTS];
int client_count = 0;

struct sockaddr_in address;

void boardcast(int client, char* message_entry, size_t size) {
	for (int i = 0; i < client_count; i++){
		if (clients[i] != client)
			send(clients[i], message_entry, size, 0);
	}
}

void clear_message(char *message, size_t len) {
	for(int i = 0; i < len; i++) 
		message[i] = '\0';
}

void recv_name(int client, char* name, size_t size){
	recv(client, name, size, 0);
	char joining_message[600];
	sprintf(joining_message, "%s joins...\n", name);
	boardcast(client, joining_message, sizeof(joining_message));
}

void* client_thread(void * arg){
	int client = *(int*) arg;

	User user;
	recv_name(client, user.name, sizeof(user.name));
	while(1){
		clear_message(user.message, sizeof(user.message));
		if (recv(client, user.message, sizeof(user.message), 0) <= 0)
			break;
		
		char message[600];
		if (strcmp(user.message, "/exit") == 0)
			sprintf(message, "%s leaves....", user.name);
		else
			sprintf(message, "%s: %s\n", user.name, user.message);
		boardcast(client, message, sizeof(message));
	}

	close(client);
	return NULL;
}

int main() {
	pthread_t thread;
	
	int server_sock = get_tcp4(); 
	connect_tcp4(&address);
	
	int bind_addr = bind(server_sock, (void*)&address, sizeof(address));
	if (bind_addr != 0){
		printf("Binding failed\n");
		exit(1);
	}

	listen(server_sock, 10);
	while (1) {
		clients[client_count++] = accept(server_sock, NULL, NULL);

		pthread_t t;
		pthread_create(&t, NULL, client_thread, &clients[client_count - 1]);
		pthread_detach(t);
	}

	return 0;
}

