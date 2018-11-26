#ifndef INCLUDED_IMAGEUTILS_H
#define INCLUDED_IMAGEUTILS_H

#include "types.h"

#include <OpenImageIO/imageio.h>

BEGIN_STEGGYNOGRAPHY_NAMESPACE

template <typename T>
void writeImage(const string_view _filename,
                const span<T> _data,
                const uinteger2 _imageDim);

template <typename T>
auto readImage(const string_view _filename);

END_STEGGYNOGRAPHY_NAMESPACE

#include "image_util.inl"  //template definitions

#endif  // INCLUDED_IMAGEUTILS_H
