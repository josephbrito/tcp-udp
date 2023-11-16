#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024] = {0};

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error on create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error on socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("Error on listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
        perror("Error on conection");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, sizeof(buffer));
    printf("client's message: %s\n", buffer);

    char *response = "Message received";
    send(new_socket, response, strlen(response), 0);

    return 0;
}
