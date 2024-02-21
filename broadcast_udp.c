#include "broadcast_udp.h"

#define TCP_PORT 6000
void broadcast_udp(int udp_socket) {
    struct sockaddr_in broadcast_addr;
    int broadcast_enable = 1;
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(UDP_PORT);
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    if (setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) == -1) {
        perror("Setsockopt for broadcast failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char message[MAX_BUF_SIZE];
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        // Construct message
        snprintf(message, MAX_BUF_SIZE, "Hello;ip=%s;p=%d", "192.168.200.128", TCP_PORT);

        // Broadcast message
        sendto(udp_socket, message, strlen(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        printf("Broadcasted: %s\n", message);

        sleep(1);
    }
}

int create_udp_socket(struct sockaddr_in *server_addr, int port) {
    int udp_socket;
    
    if ((udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("UDP socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(server_addr, 0, sizeof(*server_addr));
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr->sin_port = htons(port);

    if (bind(udp_socket, (struct sockaddr*)server_addr, sizeof(*server_addr)) == -1) {
        perror("UDP bind failed");
        exit(EXIT_FAILURE);
    }

    return udp_socket;
}
