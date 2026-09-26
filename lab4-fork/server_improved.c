/* server_improved.c - Exercise 3 challenge questions 1, 3, 4, 5:
     Q1 zombies    -> reap children via waitpid() in a SIGCHLD handler
     Q3 port reuse -> setsockopt(SO_REUSEADDR)
     Q4 overflow   -> chunked reading, never overflow the buffer
     Q5 shutdown   -> "shutdown" command exits the server cleanly
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define PORT 8080
#define CHUNK 256

int server_sock;

void reap_children(int sig) {
    (void) sig;
    while (waitpid(-1, NULL, WNOHANG) > 0) { }
}

void handle_client(int client_sock) {
    char chunk[CHUNK];
    char first[CHUNK + 1] = {0};
    long total = 0;
    int n, saved_first = 0;

    while ((n = read(client_sock, chunk, sizeof(chunk))) > 0) {
        if (!saved_first) {
            int c = n < CHUNK ? n : CHUNK;
            memcpy(first, chunk, c);
            first[c] = '\0';
            saved_first = 1;
        }
        total += n;
        if (n < (int)sizeof(chunk)) break;
    }
    printf("Received %ld bytes. First bytes: %s\n", total, first);

    if (strncmp(first, "shutdown", 8) == 0) {
        write(client_sock, "Server shutting down.", 21);
        close(client_sock);
        printf("Shutdown command received. Closing server cleanly.\n");
        close(server_sock);
        exit(0);
    }

    char reply[64];
    int len = snprintf(reply, sizeof(reply), "Got %ld bytes", total);
    write(client_sock, reply, len);
    close(client_sock);
}

int main() {
    int client_sock, opt = 1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    setvbuf(stdout, NULL, _IONBF, 0);

    struct sigaction sa;
    sa.sa_handler = reap_children;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind"); return 1;
    }
    listen(server_sock, 10);
    printf("Improved server listening on port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        if (client_sock < 0) continue;
        if (fork() == 0) {
            close(server_sock);
            handle_client(client_sock);
            exit(0);
        }
        close(client_sock);
    }
    return 0;
}
