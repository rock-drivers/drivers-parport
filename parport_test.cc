
#include <unistd.h>

#include "parport.hh"

int main(int argc, char ** argv) {
  ParportDriver ppdrv;
  if (!ppdrv.open("/dev/parport0"))
    return 1;

  int i;
  for(i = 0; i < 10; i++) {

    if (!ppdrv.resetDataPin(0))
      return 1;

    usleep(200000);

    if (!ppdrv.setDataPin(0))
      return 1;

    usleep(200000);
  }

  return 0;
}
