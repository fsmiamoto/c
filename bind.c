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

int main() {
  struct addrinfo hints, *res;
  int sockfd;

  // first, load up address structs with getaddrinfo():

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // use IPv4 or IPv6, whichever
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // fill in my IP for me

  int err = getaddrinfo(NULL, "3490", &hints, &res);
  if (err == -1) {
    perror("deu ruim");
    exit(1);
  }

  // make a socket:

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // bind it to the port we passed in to getaddrinfo():

  err = bind(sockfd, res->ai_addr, res->ai_addrlen);
  if (err == -1) {
    perror("deu ruim");
    exit(1);
  }

  for (;;) {
  }
}
