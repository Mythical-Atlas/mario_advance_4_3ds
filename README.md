# Super Mario Advance 4 for 3DS

This is a port of the GBA game by the same name.

![running on 3DS](/photo.jpg)

Uses CTR User Library: https://github.com/devkitPro/libctru

Interesting notes:
- The CTR user library only has basic audio functions, so all audio loading and handling code was custom-written for this.
- Only world 1-1 is implemented, but there is modular support for multiple different levels.
- Will be the basis for my future 3DS game projects.

# Notes for Compiling

Requires:
- MinGW https://sourceforge.net/projects/mingw/files/OldFiles/
- C:/MinGW/bin added to PATH environment variable
- Visual Studio Code (not required, but recommended)