#ifndef INCLUDED_DECODE_H
#define INCLUDED_DECODE_H

#include "types.h"

#include <vector>

BEGIN_STEGGYNOGRAPHY_NAMESPACE

std::string decode(const span<byte3> _encodedImage,
                   const uinteger _textLength,
                   const uinteger _characterOffset = 0u,
                   const uinteger _pixelOffset = 0u);

END_STEGGYNOGRAPHY_NAMESPACE

#endif  // INCLUDED_DECODE_H
