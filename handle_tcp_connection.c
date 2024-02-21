#include "handle_tcp_connection.h"

void handle_tcp_connection(int client_socket) {
    char buffer[MAX_BUF_SIZE];
    ssize_t bytes_received;

    // Receive data from client
    bytes_received = recv(client_socket, buffer, MAX_BUF_SIZE, 0);
    if (bytes_received == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    } else if (bytes_received == 0) {
        printf("Client disconnected.\n");
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    printf("Received from client: %s\n", buffer);

    // Send response to client
    send(client_socket, "server ok", strlen("server ok"), 0);

    // Close client socket
    close(client_socket);
}

int create_tcp_socket(struct sockaddr_in *server_addr, int port) {
    int tcp_socket;

    if ((tcp_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("TCP socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(server_addr, 0, sizeof(*server_addr));
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr->sin_port = htons(port);

    if (bind(tcp_socket, (struct sockaddr*)server_addr, sizeof(*server_addr)) == -1) {
        perror("TCP bind failed");
        exit(EXIT_FAILURE);
    }

    return tcp_socket;
}
