#include "Trame.hpp"
#include "tm1638.h"
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <ostream>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

Trame::Trame() {}
Trame::Trame(const std::vector<uint8_t> &trame) {
  _trame = trame;
}

void Trame::add_bit(pin_value v) {
  if (_bitCount >= 8) {
    _bitCount = 0;
    _trame.push_back(0x00);
  }

  if (v == HIGH)
    _trame.back() |= (1 << _bitCount);
  _bitCount++;
}

std::vector<uint8_t>Trame::get_trame_value() {
  return std::vector<uint8_t>(_trame);
}

bool Trame::operator==(const Trame &other) const
{
  return _trame == other._trame;
}

std::ostream & operator<<(std::ostream &os, const Trame &t) {
  for(size_t i = 0; i <= t._trame.size(); i++) {
    os << "0x"
       << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(t._trame[i]);

    if(i != t._trame.size())
      os << " ";
  }
  return os;
}
