// Heavily based on the code shown by Prof. Jacob Sorber in his awesonme youtube
// channel: https://www.youtube.com/watch?v=Pg_4Jz8ZIH4&t=1s
#include <arpa/inet.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 100

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void *handle_connection(void *p_client_socket);
int check(int got, const char *msg);

int main(int argc, char **argv) {
  int server_socket, client_socket, addr_size;
  SA_IN server_addr, client_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(SERVERPORT);

  // Since we using SOCK_STREAM, this will use TCP
  check((server_socket = socket(AF_INET, SOCK_STREAM, 0)),
        "Failed to create socket");

  check(bind(server_socket, (SA *)&server_addr, sizeof(server_addr)),
        "Failed to bind");

  check(listen(server_socket, SERVER_BACKLOG), "Failed to listen!");

  for (;;) {
    printf("Listening for connections...\n");

    addr_size = sizeof(SA_IN);
    check((client_socket = accept(server_socket, (SA *)&client_addr,
                                  (socklen_t *)&addr_size)),
          "Failed to accept connection");
    printf("Connected!\n");

    pthread_t t;
    int *pclient = (int *)malloc(sizeof(int));
    *pclient = client_socket;
    pthread_create(&t, NULL, handle_connection, pclient);
  }

  return 0;
};

int check(int got, const char *msg) {
  if (got < 0)
    perror(msg);
  return got;
}

void *handle_connection(void *p_client_socket) {
  int client_socket = *((int *)p_client_socket);
  free(p_client_socket);

  char buffer[BUFSIZE];
  size_t bytes_read;
  int msgsize = 0;
  char actualpath[PATH_MAX + 1];

  while ((bytes_read = read(client_socket, buffer + msgsize,
                            sizeof(buffer) - msgsize - 1)) > 0) {
    msgsize += bytes_read;
    if (msgsize > BUFSIZE - 1 || buffer[msgsize - 1] == '\n')
      break;
  }
  check(bytes_read, "recv error");

  // Add null to the end for using it as a string
  buffer[msgsize - 1] = 0;

  printf("Request: %s\n", buffer);
  fflush(stdout);

  if (realpath(buffer, actualpath) == NULL) {
    printf("ERROR(bad path): %s\n", buffer);
    close(client_socket);
    return NULL;
  }

  FILE *fp = fopen(actualpath, "r");
  if (fp == NULL) {
    printf("ERROR(open): %s\n", buffer);
    close(client_socket);
    return NULL;
  }

  while ((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0) {
    printf("sending %zu bytes\n", bytes_read);
    write(client_socket, buffer, bytes_read);
  }

  close(client_socket);
  fclose(fp);
  printf("closing connection\n");

  return NULL;
}
