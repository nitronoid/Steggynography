#ifndef INCLUDED_BIT_MANIP_H
#define INCLUDED_BIT_MANIP_H

#include "types.h"

BEGIN_STEGGYNOGRAPHY_NAMESPACE

byte setBit(byte character, byte n, byte bit);

byte getBit(byte character, byte n);

END_STEGGYNOGRAPHY_NAMESPACE

#endif//INCLUDED_BIT_MANIP_H
