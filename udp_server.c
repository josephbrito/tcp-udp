#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int socket_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024] = {0};

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("Error on create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error on socket");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connections...\n");

    recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
    printf("client's message: %s\n", buffer);

    char *response = "Message received";
    sendto(socket_fd, response, strlen(response), 0, (struct sockaddr *)&client_addr, addr_len);

    return 0;
}
