CC=gcc
FLAG=-Iinclude
CLIENT=client
SERVER=server
SRC_DIR=./src

all: $(SRC_DIR)/$(CLIENT).c $(SRC_DIR)/$(SERVER).c 
	$(CC) $(FLAG) $(SRC_DIR)/$(CLIENT).c -o $(CLIENT)
	$(CC) $(FLAG) $(SRC_DIR)/$(SERVER).c -o $(SERVER)

clean: 
	rm -f $(CLIENT) $(SERVER) 
