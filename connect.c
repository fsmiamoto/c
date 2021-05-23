#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 2048

int main(int argc, char **argv) {
  struct addrinfo hints, *res;
  int sockfd;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo("fsmiamoto.xyz", "80", &hints, &res) == -1) {
    perror("error");
    exit(1);
  };

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
    perror("error");
    exit(1);
  };

  char sendline[BUFSIZE];
  sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
  int sendbytes = strlen(sendline);

  // Send the request
  if (write(sockfd, sendline, sendbytes) != sendbytes) {
    perror("error");
    exit(1);
  }

  char buffer[BUFSIZE];
  while (read(sockfd, buffer, BUFSIZE) > 0) {
    printf("%s", buffer);
  }
}
