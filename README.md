# API-broadcast-in-LAN
Build client-server program:
+ Server: has two ports UDP (ex: 7000), TCP (ex: 6000). In particular, UDP is used to broadcast periodically on the network for about 1 seconds, with the content "Hello;ip=ip of the server;p=TCP port of the server"
           * after receiving the tcp message from the client, the server prints the client's content to the screen and responds with a "server ok" message
+ Client: Receives boardcast packets from the server, gets ip address and TCP port information from the server.
           * establish a tcp connection to the server, send a message with the content: "Client hello;ip=client's ip address"
           * After receiving the ok message from the server, the client closes the connection to the server.

To run the above program, follow these steps:
- Compile the program: make all
- Run the server file you just compiled: ./server
- Run the client file you just compiled: ./client
- Clean file: make clean

Note: to run this program you need 2 computers on the same network: one running the server file and one running the client file.
