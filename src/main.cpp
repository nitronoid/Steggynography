#include "decode.h"
#include "encode.h"
#include "image_util.h"
#include "types.h"

#include <cxxopts.hpp>

namespace
{
inline static auto getParser()
{
  cxxopts::Options parser("Steggynography", "Simple steganography tool");
  // clang-format off
  parser.allow_unrecognised_options().add_options() 
    ("h,help", "Print help") 
    ("s,source", "Source file name", cxxopts::value<std::string>()) 
    ("t,text", "Text to encode", cxxopts::value<std::string>()) 
    ("o,output", "Output file name (with extension)",
     cxxopts::value<std::string>()->default_value("message.png")) 
    ;
  // clang-format on
  return parser;
}

}  // namespace

int main(int argc, char* argv[])
{
  // Parse the commandline options
  auto parser     = getParser();
  const auto args = parser.parse(argc, argv);
  if (args.count("help") || !args.count("source") || !args.count("text"))
  {
    std::cout << parser.help() << '\n';
    std::exit(0);
  }

  // Read the source image in as an array of rgbf
  auto imgResult =
    steg::readImage<steg::byte3>(args["source"].as<std::string>());
  auto& sourceImageData = imgResult.m_data;
  const auto& imageDimensions = imgResult.m_imageDim;

  auto text = args["text"].as<std::string>();

  steg::encode(sourceImageData, text);
  steg::writeImage(args["output"].as<std::string>(),
                   steg::span<steg::byte3>(sourceImageData),
                   imageDimensions);

  auto decoded = steg::decode(sourceImageData, text.size());
  std::cout << "text: " << decoded << '\n';
}
