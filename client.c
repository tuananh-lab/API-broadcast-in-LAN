#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UDP_PORT 7000
#define TCP_PORT 6000
#define MAX_BUF_SIZE 1024

void handle_tcp_connection(int tcp_socket, struct sockaddr_in server_addr) {
    char buffer[MAX_BUF_SIZE];
    ssize_t bytes_received;

    // Send message to server
    snprintf(buffer, MAX_BUF_SIZE, "Client hello;ip=%s", inet_ntoa(server_addr.sin_addr));
    send(tcp_socket, buffer, strlen(buffer), 0);
    printf("Sent message to server: %s\n", buffer);

    // Receive response from server
    bytes_received = recv(tcp_socket, buffer, MAX_BUF_SIZE, 0);
    if (bytes_received == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    } else if (bytes_received == 0) {
        printf("Server disconnected.\n");
    } else {
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    // Close TCP socket
    close(tcp_socket);
}

int main() {
    int udp_socket, tcp_socket;
    struct sockaddr_in udp_server_addr;
    socklen_t udp_server_addr_len = sizeof(udp_server_addr);

    // Create UDP socket
    if ((udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("UDP socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&udp_server_addr, 0, sizeof(udp_server_addr));
    udp_server_addr.sin_family = AF_INET;
    udp_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    udp_server_addr.sin_port = htons(UDP_PORT);

    // Bind UDP socket
    if (bind(udp_socket, (struct sockaddr*)&udp_server_addr, sizeof(udp_server_addr)) == -1) {
        perror("UDP bind failed");
        exit(EXIT_FAILURE);
    }

    // Receive broadcast message from server
    char buffer[MAX_BUF_SIZE];
    recvfrom(udp_socket, buffer, MAX_BUF_SIZE, 0, (struct sockaddr*)&udp_server_addr, &udp_server_addr_len);
    printf("Received broadcast message from server: %s\n", buffer);


    char server_ip[]="192.168.200.128";

    // Create TCP socket
    if ((tcp_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("TCP socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.200.128");
    server_addr.sin_port = htons(TCP_PORT);

    // Connect to server
    if (connect(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server at %s:%d\n", server_ip, TCP_PORT);

    // Handle TCP connection
    handle_tcp_connection(tcp_socket, server_addr);

    close(udp_socket);
    return 0;
}
