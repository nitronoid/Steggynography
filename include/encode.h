#ifndef INCLUDED_ENCODE_H
#define INCLUDED_ENCODE_H

#include "types.h"

#include <vector>

BEGIN_STEGGYNOGRAPHY_NAMESPACE

void encode(span<byte3> _sourceImage,
            const string_view _text,
            const uinteger _offset = 0u);

END_STEGGYNOGRAPHY_NAMESPACE

#endif  // INCLUDED_ENCODE_H
