#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/ppdev.h>

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr,"Usage: %s <parport-dev> <pinstate>\n",argv[0]);
    return 1;
  }

  int pins = strtol(argv[2],NULL,0);

  int fd;
  if ((fd = open(argv[1], O_RDWR)) < 0) {
    perror("Could not open");
    return 1;
  }

  int i = 0;

  if (ioctl(fd,PPEXCL,&i)) {
    perror("no exclusive rights");
    close(fd);
    return 1;
  }

  if (ioctl(fd,PPCLAIM,&i)) {
    perror("claim failed");
    close(fd);
    return 1;
  }

  if (ioctl(fd,PPWDATA,&pins)) {
    perror("write ioctl failed");
    if (ioctl(fd,PPRELEASE,&i))
      perror("could not release");
    close(fd);
    return 1;
  }

  close(fd);

  return 0;
}
