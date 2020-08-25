// Based on the excellent material provided by Prof. Maziero
// http://wiki.inf.ufpr.br/maziero/lib/exe/fetch.php?media=socm:socm-video-09.mkv

// Compile with `-lrt`
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define QUEUE "/my_queue"

int main(int argc, char *argv[]) {
  mqd_t queue;
  struct mq_attr attr;
  int msg;

  attr.mq_maxmsg = 10;
  attr.mq_msgsize = sizeof(msg);
  attr.mq_flags = 0;

  umask(0);

  if ((queue = mq_open(QUEUE, O_RDWR | O_CREAT, 0666, &attr)) < 0) {
    perror("mq_open");
    exit(1);
  }

  for (;;) {
    if ((mq_receive(queue, (void *)&msg, sizeof(msg), 0)) < 0) {
      perror("mq_receive");
      exit(1);
    }
    printf("Received msg value %d\n", msg);
  }
}
