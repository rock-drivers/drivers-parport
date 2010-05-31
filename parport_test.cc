
#include "parport.hh"

int main(int argc, char ** argv) {
  ParportDriver ppdrv;
  if (!ppdrv.open("/dev/parport0"))
    return 1;

  if (!ppdrv.setDataPin(0))
    return 1;

  if (!ppdrv.resetDataPin(0))
    return 1;

  return 0;
}
