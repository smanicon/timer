#include "TrameManager.hpp"
#include "Trame.hpp"
#include "tm1638.h"
#include <stdint.h>
#include <vector>

void TrameManager::new_trame() {
  _trames.push_back(Trame());
}

void TrameManager::write_bit(pin_value v) {
  _trames.back().add_bit(v);
}

pin_value TrameManager::read_bit() { return LOW; }

void TrameManager::insert_read_value(uint8_t) {}

Trame TrameManager::lastTrame() {
  return _trames.back();
}

