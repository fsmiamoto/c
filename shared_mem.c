// Based on the excellent material provided by Prof. Maziero
// http://wiki.inf.ufpr.br/maziero/lib/exe/fetch.php?media=socm:socm-video-09.mkv

// Compile with `-lrt`

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd, value, *ptr;

  // Open/create a shared memory area
  fd = shm_open("/sharedmeme", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    perror("shm_open");
    exit(1);
  }

  // Adjust the shared area size
  if (ftruncate(fd, sizeof(value)) == -1) {
    perror("ftruncate");
    exit(1);
  }

  // Map the shared area to the address space of this process
  ptr = mmap(NULL, sizeof(value), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  for (;;) {
    value = random() % 1000;

    // Write on the shared area
    (*ptr) = value;
    printf("Wrote value %i\n", value);
    sleep(1);

    // Read from the shared area
    value = (*ptr);
    printf("Read value %i\n", value);
    sleep(1);
  }
}
