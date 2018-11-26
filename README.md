# Requirements

- qmake (tested with version 3.1)
- OpenImageIO (tested with 1.8 and 1.9)
- GLM (tested with 0.9.9)
- string-view-lite (pulled as a submodule)
- span-lite (pulled as a submodule)

Tested on Fedora linux 29 using c++14 with gcc and clang


# Set-up

\> git submodule update --init --recursive

\> qmake

\> make (-j)


# Usage

\> help: ./steg -h

\> encode: ./steg -s "images/some\_img.png" -o "output/secret\_message.png" -t "my message"

\> decode: ./steg -s "output/secret\_message.png" -l 7
