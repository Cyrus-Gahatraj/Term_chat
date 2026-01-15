# Term_chat

A simple multi-client chat server written in C for linux.

Clients connect, choose a name, and exchange messages in real time through a central server.

## Build

Compile the server and the client

```bash
gcc server.c -o server
gcc client.c -o client
```


## Demo

Start the server:
```bash
./server
```

In different terminal 
```bash
./client
What's your name: Bob

./client  # Another terminal
What's your name: Alice

# Alice and Bob's chat continues...
```

## Notes
This project is built for learning low-level networking, threading in C.
It uses TCP, for reliable message delivery.
