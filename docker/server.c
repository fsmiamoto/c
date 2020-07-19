// Based on the awesome video from Jacob Sorter
// https://www.youtube.com/watch?v=esXw4bdaZkc
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 3333

#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...);

int main(int argc, char **argv) {
  int listenfd, connfd, n;
  struct sockaddr_in servaddr;
  uint8_t buff[MAXLINE + 1];
  uint8_t recvline[MAXLINE + 1];
  int port;

  char *port_env = getenv("PORT");
  if (port_env) {
    port = atoi(port_env);
  } else {
    port = SERVER_PORT;
  }

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_n_die("Socket error");

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
    err_n_die("bind error.");

  if (listen(listenfd, 10) < 0)
    err_n_die("listen error.");

  // Infinite loop for accepting connections
  for (;;) {
    printf("Waiting for a connection o port %d\n", port);
    fflush(stdout);

    // Whenever a client connects, accept returns a socket
    connfd = accept(listenfd, (SA *)NULL, NULL);

    memset(recvline, 0, MAXLINE);
    while ((n = read(connfd, recvline, MAXLINE - 1)) > 0) {
      // Print the request
      fprintf(stdout, "%s", recvline);
      fflush(stdout);

      // Detect the end of the request, not robust
      if (recvline[n - 1] == '\n') {
        break;
      }

      memset(recvline, 0, MAXLINE);
    }

    if (n < 0)
      err_n_die("read error");

    snprintf((char *)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello");
    write(connfd, (char *)buff, strlen((char *)buff));
    close(connfd);
  }
}

void err_n_die(const char *fmt, ...) {
  int errno_save;
  va_list ap;

  errno_save = errno;

  va_start(ap, fmt);
  vfprintf(stdout, fmt, ap);
  fprintf(stdout, "\n");
  fflush(stdout);

  if (errno_save != 0) {
    fprintf(stdout, "(errno = %d): %s\n", errno_save, strerror(errno_save));
    fprintf(stdout, "\n");
    fflush(stdout);
  }

  va_end(ap);

  exit(1);
}
