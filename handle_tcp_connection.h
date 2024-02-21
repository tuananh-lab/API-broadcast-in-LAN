#ifndef HANDLE_TCP_CONNECTION_H
#define HANDLE_TCP_CONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TCP_PORT 6000
#define MAX_BUF_SIZE 1024

void handle_tcp_connection(int client_socket);
int create_tcp_socket(struct sockaddr_in *server_addr, int port);

#endif
