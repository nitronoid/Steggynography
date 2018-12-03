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

  // Character offset in number of bits
  const uinteger bitOffset = _characterOffset * nbits;
  // Calculate how many pixels we need to offset for this
  const uinteger bitPxOffset = bitOffset / 3u;
  // Get the total pixel offset
  const uinteger pixelOffset = _pixelOffset + bitPxOffset;
  // Calculate the channel offset into out first pixel
  const uinteger channelOffset = bitOffset - bitPxOffset * 3u;

  byte* bptr = &_sourceImage[pixelOffset][channelOffset];

  // Iterate over every byte of the text
  for (byte c : _text)
  {
    // iterate over all bits of the char
    for (byte bitCount = 0u; bitCount < nbits; ++bitCount, ++bptr)
    {
      // set the lsb to be the current bit of our char
      *bptr = setBit(*bptr, 0u, getBit(c, bitCount));
    }
  }
}

END_STEGGYNOGRAPHY_NAMESPACE
