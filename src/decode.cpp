#include "decode.h"

#include <iostream>

BEGIN_STEGGYNOGRAPHY_NAMESPACE

std::string decode(const span<byte3> _encodedImage,
                   const uinteger _textLength,
                   const uinteger _offset)
{
  constexpr auto nbits     = charbits{}.size();
  const auto numBitsInText = _textLength * nbits;
  // allocate space for the text
  std::vector<byte> textArray(_textLength);

  // Keep a counter of what bit we need to write to
  uinteger bit = 0u;
  // Iterate over enough pixels to give us the full text
  for (uinteger pidx = _offset; bit < numBitsInText; ++pidx)
  {
    // Get the current pixel
    const byte3& pixel = _encodedImage[pidx];
    // Iterate over each channel of the current pixel
    for (uinteger i = 0u; i < 3 && bit < numBitsInText; ++i, ++bit)
    {
      // create a bitset from this channel
      charbits channelBits(pixel[i]);

      // get the char we are writing to
      byte& c = textArray[bit / nbits];
      // create a bitset from the char
      charbits charBits(c);

      // Set the bit we are writing to as the lsb of this channel
      charBits.set(bit % nbits, channelBits[0u]);
      // copy the bitset back to our array
      c = charBits.to_ulong();
    }
  }

  return std::string(std::make_move_iterator(textArray.begin()),
                     std::make_move_iterator(textArray.end()));
}

END_STEGGYNOGRAPHY_NAMESPACE
