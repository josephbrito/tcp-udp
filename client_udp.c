#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int socket_fd;
    struct sockaddr_in server_addr;
    char *message = "Request UDP";

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("Error on create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("IP address to binary failed");
        exit(EXIT_FAILURE);
    }

    sendto(socket_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buffer[1024] = {0};
    recvfrom(socket_fd, buffer, sizeof(buffer), 0, NULL, NULL);
    printf("Server response: %s\n", buffer);

    close(socket_fd);

    return 0;
}
