#include "parport.hh"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/ppdev.h>

ParportDriver::ParportDriver() : fd(-1) {
}

bool ParportDriver::open(std::string const& filename, uint8_t default_state) {
  if ((fd = ::open(filename.c_str(), O_RDWR)) < 0) {
    perror("Could not open");
    return false;
  }

  int i = 0;

  if (ioctl(fd,PPEXCL,&i)) {
    perror("no exclusive rights");
    ::close(fd);
    fd = -1;
    return false;
  }

  if (ioctl(fd,PPCLAIM,&i)) {
    perror("claim failed");
    ::close(fd);
    fd = -1;
    return false;
  }

  pins = default_state;
  if (!writePins()) {
    ::close(fd);
    fd = -1;
    return false;
  }

  return true;
}

void ParportDriver::close() {
  int i = 0;

  if (ioctl(fd,PPRELEASE,&i))
    perror("could not release");
  ::close(fd);

  fd = -1;
}

bool ParportDriver::writePins() {
  if (ioctl(fd,PPWDATA,&pins)) {
    perror("write ioctl failed");
    return false;
  }
  return true;
}

bool ParportDriver::setDataPin(unsigned pin) {
  pins |= 1 << pin;
  return writePins();
}

bool ParportDriver::resetDataPin(unsigned pin) {
  pins &= ~(1 << pin);
  return writePins();
}
