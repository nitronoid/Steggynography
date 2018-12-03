#include "decode.h"
#include "bit_manip.h"

#include <iostream>
#include <limits>

BEGIN_STEGGYNOGRAPHY_NAMESPACE

std::string decode(const span<byte3> _encodedImage,
                   const uinteger _textLength,
                   const uinteger _characterOffset,
                   const uinteger _pixelOffset)
{
  constexpr auto nbits = std::numeric_limits<byte>::digits;
  const auto numBitsInText = _textLength * nbits;
  // allocate space for the text
  std::vector<byte> textArray(_textLength);

  // Keep a counter of what bit we need to write to
  uinteger bitCount = 0u;

  // Character offset in number of bits
  const uinteger bitOffset = _characterOffset * nbits;
  // Calculate how many pixels we need to offset for this
  const uinteger bitPxOffset = bitOffset / 3u;
  // Get the total pixel offset
  uinteger pidx = _pixelOffset + bitPxOffset;
  // Calculate the channel offset into out first pixel
  uinteger channel = bitOffset - bitPxOffset * 3u;

  // Iterate over enough pixels to give us the full text
  for (; bitCount < numBitsInText; ++pidx)
  {
    // Get the current pixel
    const byte3& pixel = _encodedImage[pidx];
    // Iterate over each channel of the current pixel
    for (; channel < 3 && bitCount < numBitsInText; ++channel, ++bitCount)
    {
      const uinteger charCount = bitCount / nbits;
      // get the char we are writing to
      byte& c = textArray[charCount];

      // bitCount - charCount * nbits is faster than bitCount % nbits
      c = setBit(c, bitCount - charCount * nbits, getBit(pixel[channel], 0u));
    }
    channel = 0u;
  }

  return std::string(std::make_move_iterator(textArray.begin()),
                     std::make_move_iterator(textArray.end()));
}

END_STEGGYNOGRAPHY_NAMESPACE
