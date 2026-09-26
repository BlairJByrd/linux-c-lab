/* client_bigmsg.c - Q4: sends a 10,000-character message. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BIG 10000

int main() {
    int sock, n;
    struct sockaddr_in server_addr;
    char *big = malloc(BIG + 1);
    memset(big, 'A', BIG);
    big[BIG] = '\0';

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Sending %d characters...\n", BIG);
    send(sock, big, BIG, 0);

    char reply[256];
    n = read(sock, reply, sizeof(reply) - 1);
    if (n < 0) n = 0;
    reply[n] = '\0';
    printf("Server response: %s\n", reply);

    close(sock);
    free(big);
    return 0;
}
