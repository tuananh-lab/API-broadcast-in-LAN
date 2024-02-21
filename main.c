#include "broadcast_udp.h"
#include "handle_tcp_connection.h"

int main() {
    int udp_socket, tcp_socket, client_socket;
    struct sockaddr_in udp_server_addr, tcp_server_addr, client_addr;

    // Create UDP socket and bind
    udp_socket = create_udp_socket(&udp_server_addr, UDP_PORT);

    // Create TCP socket and bind
    tcp_socket = create_tcp_socket(&tcp_server_addr, TCP_PORT);

    printf("Server started.\n");

    // Start broadcasting UDP packets in a separate process
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        broadcast_udp(udp_socket);
        exit(EXIT_SUCCESS);
    }

    // Parent process listens for incoming TCP connections
    if (listen(tcp_socket, 1) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Accept incoming TCP connections
        socklen_t client_addr_len = sizeof(struct sockaddr_in);
        if ((client_socket = accept(tcp_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        // Handle TCP connection
        handle_tcp_connection(client_socket);
    }

    // Close sockets
    close(udp_socket);
    close(tcp_socket);

    return 0;
}
