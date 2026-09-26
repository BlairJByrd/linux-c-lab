/* client_shutdown.c - Q5: tells the server to shut down gracefully. */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock, n;
    struct sockaddr_in server_addr;
    char buffer[64] = "shutdown";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    send(sock, buffer, strlen(buffer), 0);
    n = read(sock, buffer, sizeof(buffer) - 1);
    if (n < 0) n = 0;
    buffer[n] = '\0';
    printf("Server response: %s\n", buffer);
    close(sock);
    return 0;
}
