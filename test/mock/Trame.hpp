#ifndef TRAME_H
#define TRAME_H

#include "tm1638.h"
#include <ostream>
#include <stdint.h>
#include <vector>
class Trame {
public:
  Trame();
  Trame(const std::vector<uint8_t> &);
  void add_bit(pin_value);
  std::vector<uint8_t> get_trame_value();
  bool operator==(const Trame &) const;

  friend std::ostream &operator<<(std::ostream &, const Trame &);

private:
  std::vector<uint8_t> _trame;
  uint8_t _bitCount;
};

#endif
