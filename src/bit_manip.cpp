#include "bit_manip.h"

BEGIN_STEGGYNOGRAPHY_NAMESPACE

byte setBit(byte character, byte n, byte bit)
{
  // clear the nth bit of character,
  // then set it to be the value of bit
  return (character & ~(1u << n)) | (bit << n);
}

byte getBit(byte character, byte n)
{
  // shift until the bit we want is lsb,
  // bitwise AND with 1 to ensure it is the only bit set
  return (character >> n) & 1u;
}

END_STEGGYNOGRAPHY_NAMESPACE
