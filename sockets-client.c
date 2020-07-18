// Based on the awesome video from Jacob Sorter
// https://www.youtube.com/watch?v=bdIiTxtMaKA
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

#define SERVER_PORT 80

#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...);

int main(int argc, char **argv) {
  int sockfd, n;
  int sendbytes;
  struct sockaddr_in servaddr;
  struct hostent *he;
  struct in_addr **addr_list;
  char sendline[MAXLINE];
  char recvline[MAXLINE];
  char ip[100];

  if (argc != 2)
    err_n_die("usage: %s <server address>", argv[0]);

  // Get the IP from the hostname
  if ((he = gethostbyname(argv[1])) == NULL)
    err_n_die("Failed to get host by name");

  if ((addr_list = (struct in_addr **)he->h_addr_list) == NULL) {
    err_n_die("Failed to get address list");
  }

  strncpy(ip, inet_ntoa(**addr_list), 100);

  // Create the socket of stream type
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_n_die("Error while creating the socket!");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);

  // Convert the IP to the binary format
  if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0)
    err_n_die("inet_pton error for %s", ip);

  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
    err_n_die("connect failed!");

  // Super basic request, don't forget the two newlines at the end
  sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
  sendbytes = strlen(sendline);

  // Send the request
  if (write(sockfd, sendline, sendbytes) != sendbytes)
    err_n_die("write error!");

  // Get the response, hopefully...
  memset(recvline, 0, MAXLINE);
  while ((n = read(sockfd, recvline, MAXLINE - 1)) > 0) {
    printf("%s", recvline);
  }

  if (n < 0)
    err_n_die("read error");

  exit(0);
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
