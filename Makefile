CC=gcc
CLIENT=client
SERVER=server

all: client.c server.c
	$(CC) $(CLIENT).c -o $(CLIENT)
	$(CC) $(SERVER).c -o $(SERVER)

clean: 
	rm -f $(CLIENT) $(SERVER) 
