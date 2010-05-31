#ifndef __PARPORT_DRIVER_HH__
#define __PARPORT_DRIVER_HH__

#include <stdint.h>
#include <string>

class ParportDriver {
private:
  int fd;
  uint8_t pins;

  bool writePins();
public:
  ParportDriver();

  bool open(std::string const& filename);
  void close();

  bool setDataPin(unsigned pin);
  bool resetDataPin(unsigned pin);
};

#endif /*__PARPORT_DRIVER_HH__*/

