
BEGIN_STEGGYNOGRAPHY_NAMESPACE

template <typename T>
void writeImage(const string_view _filename,
                const span<T> _data,
                const uinteger2 _imageDim)
{
  std::cout << "Writing image to " << _filename << '\n';
  // OpenImageIO namespace
  using namespace OIIO;
  // unique_ptr with custom deleter to close file on exit
  std::unique_ptr<ImageOutput, void (*)(ImageOutput*)> output(
    ImageOutput::create(_filename.data())
#if OIIO_VERSION >= 10900
      .release()
#endif
      ,
    [](auto ptr) {
      ptr->close();
      delete ptr;
    });
  ImageSpec is(_imageDim.x,
               _imageDim.y,
               sizeof(T) / sizeof(std::declval<T>()[0]),
               TypeDesc::UINT8);
  output->open(_filename.data(), is);
  output->write_image(TypeDesc::UINT8, _data.data());
}

template <typename T>
auto readImage(const string_view _filename)
{
  // OpenImageIO namespace
  using namespace OIIO;
  // unique_ptr with custom deleter to close file on exit
  std::unique_ptr<ImageInput, void (*)(ImageInput*)> input(
    ImageInput::open(_filename.data())
#if OIIO_VERSION >= 10900
      .release()
#endif
      ,
    [](auto ptr) {
      ptr->close();
      delete ptr;
    });
  // Get the image specification and store the dimensions
  auto&& spec = input->spec();
  uinteger2 dim{spec.width, spec.height};

  // Allocated an array for our data
  std::vector<T> data(dim.x * dim.y);
  // Read the data into our array, with a specified stride of how many floats
  // the user requested, i.e. for byte3 we ignore the alpha channel
  input->read_image(
    TypeDesc::UINT8, data.data(), sizeof(T), AutoStride, AutoStride);

  // return an owning span
  struct OwningSpan
  {
    std::vector<T> m_data;
    uinteger2 m_imageDim;
  };
  return OwningSpan{std::move(data), std::move(dim)};
}

END_STEGGYNOGRAPHY_NAMESPACE
