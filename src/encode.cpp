#include "encode.h"

#include <iostream>

BEGIN_STEGGYNOGRAPHY_NAMESPACE

void encode(span<byte3> _image, const string_view _text, const uinteger _offset)
{
  constexpr auto nbits = charbits{}.size();

  byte* bptr = &_image[_offset].x;

  // Iterate over every byte of the text
  for (byte c : _text)
  {
    // create a bitset from this char
    charbits charBits(c);

    // iterate over all bits of the char
    for (byte bit = 0u; bit < nbits; ++bit, ++bptr)
    {
      // create a bitset from the current channel of the current pixel
      charbits channelBits(*bptr);
      // set the lsb to be the current bit of our char
      channelBits.set(0u, charBits[bit]);
      // write the new channel byte into our image
      *bptr = channelBits.to_ulong();
    }
  }
}

END_STEGGYNOGRAPHY_NAMESPACE
