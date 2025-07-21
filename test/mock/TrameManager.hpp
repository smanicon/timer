#ifndef TRAMEMANAGER_H
#define TRAMEMANAGER_H
#include "Trame.hpp"
#include "tm1638.h"
#include <stdint.h>
#include <vector>

class TrameManager {
public:
  void new_trame();
  void write_bit(pin_value);
  pin_value read_bit();
  void insert_read_value(uint8_t);
  Trame lastTrame();
private:
  std::vector<Trame> _trames = {};
};
#endif
