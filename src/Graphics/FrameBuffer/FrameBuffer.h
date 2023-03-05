/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_2
Filename: FrameBuffer.h

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 01/30/2023
----------------------------------------------------------------------------------------------------------*/

#pragma once
#include <SFML/Graphics.hpp>

class FrameBuffer
{
  public:
    static void Init(int w, int h);
    static void Free();

    static void Clear(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
    static void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
    static void GetPixel(int x, int y, unsigned char & r, unsigned char & g, unsigned char & b);
    static int  GetWidth() { return width; }
    static int  GetHeight() { return height; }

    static void ConvertFrameBufferToSFMLImage(sf::Image & image);

  private:
    static int             width;
    static int             height;
    static unsigned char * imageData;
};