#ifndef BROADCAST_UDP_H
#define BROADCAST_UDP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define UDP_PORT 7000
#define MAX_BUF_SIZE 1024

void broadcast_udp(int udp_socket);
int create_udp_socket(struct sockaddr_in *server_addr, int port);

#endif

