#include "encode.h"
#include "bit_manip.h"

#include <limits>
#include <iostream>

BEGIN_STEGGYNOGRAPHY_NAMESPACE

void encode(span<byte3> _sourceImage,
            const string_view _text,
            const uinteger _characterOffset,
            const uinteger _pixelOffset)
{
  constexpr auto nbits = std::numeric_limits<byte>::digits;

  const auto pxOffset = _pixelOffset + (_characterOffset * nbits) / 3; 
  const auto channelOffset = (_characterOffset * nbits) % 3; 

  byte* bptr = &_sourceImage[pxOffset][channelOffset];

  // Iterate over every byte of the text
  for (byte c : _text)
  {
    // iterate over all bits of the char
    for (byte bit = 0u; bit < nbits; ++bit, ++bptr)
    {
      // set the lsb to be the current bit of our char
      *bptr = setBit(*bptr, 0u, getBit(c, bit));
    }
  }
}

END_STEGGYNOGRAPHY_NAMESPACE
