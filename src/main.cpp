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
    ("l,length", "Length of message to decode", cxxopts::value<steg::uinteger>())
    ("s,source", "Source file name", cxxopts::value<std::string>()) 
    ("t,text", "Text to encode", cxxopts::value<std::string>()) 
    ("p,pixel-offset", "Offset in number of pixels before encoding/decoding begins", 
     cxxopts::value<steg::uinteger>()->default_value("0")) 
    ("c,character-offset", "Offset in number of characters before encoding/decoding begins", 
     cxxopts::value<steg::uinteger>()->default_value("0")) 
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
  if (args.count("help") || !args.count("source") || !(args.count("length") != args.count("text")))
  {
    std::cout << parser.help() << '\n';
    std::exit(0);
  }

  // Read the source image in as an array of rgbf
  auto imgResult =
    steg::readImage<steg::byte3>(args["source"].as<std::string>());
  auto& sourceImageData = imgResult.m_data;
  const auto& imageDimensions = imgResult.m_imageDim;
  const auto pixelOffset = args["pixel-offset"].as<steg::uinteger>();
  const auto charOffset = args["character-offset"].as<steg::uinteger>();

  if (args.count("length"))
  {
    auto textLength = args["length"].as<steg::uinteger>();
    auto decoded = steg::decode(
        sourceImageData, 
        textLength, 
        charOffset, 
        pixelOffset);
    std::cout << "Decoded text is:\n" << decoded << '\n';
  }
  else
  {
    auto text = args["text"].as<std::string>();
    steg::encode(sourceImageData, text, charOffset, pixelOffset);
    steg::writeImage(args["output"].as<std::string>(),
                     steg::span<steg::byte3>(sourceImageData),
                     imageDimensions);
  }
}
