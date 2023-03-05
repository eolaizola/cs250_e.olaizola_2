/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_2
Filename: FrameBuffer.cpp

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 01/30/2023
----------------------------------------------------------------------------------------------------------*/
#include "FrameBuffer.h"

int             FrameBuffer::width     = 0;
int             FrameBuffer::height    = 0;
unsigned char * FrameBuffer::imageData = nullptr;

/*
*
* \brief Initializes the frame buffer
*
*/
void FrameBuffer::Init(int w, int h)
{
    width     = w;
    height    = h;
    int size  = 3 * width * height;
    imageData = new unsigned char[size];
}

/*
*
* \brief Frees the frame buffer
*
*/
void FrameBuffer::Free()
{
    Clear(0, 0, 0);
    delete[] imageData;
}

/*
*
* \brief Clears the frame buffer
*
*/
void FrameBuffer::Clear(unsigned char r, unsigned char g, unsigned char b)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            imageData[(y * width + x) * 3 + 0] = r;
            imageData[(y * width + x) * 3 + 1] = g;
            imageData[(y * width + x) * 3 + 2] = b;
        }
    }
}

/*
*
* \brief Sets the pixel in the designated location
*
*/
void FrameBuffer::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    //Sanity check
    if ((x > width || x < 0) || (y > height || y < 0))
        return;

    imageData[(y * width + x) * 3 + 0] = r;
    imageData[(y * width + x) * 3 + 1] = g;
    imageData[(y * width + x) * 3 + 2] = b;
}

/*
*
* \brief Gets the pixel in the designated location
*
*/
void FrameBuffer::GetPixel(int x, int y, unsigned char & r, unsigned char & g, unsigned char & b)
{
    //Sanity check
    if ((x > width || x < 0) || (y > height || y < 0))
        return;

    r = imageData[(y * width + x) * 3 + 0];
    g = imageData[(y * width + x) * 3 + 1];
    b = imageData[(y * width + x) * 3 + 2];
}

// Convert the custom framebuffer to SFML format
void FrameBuffer::ConvertFrameBufferToSFMLImage(sf::Image & image)
{
    int w = FrameBuffer::GetWidth();
    int h = FrameBuffer::GetHeight();

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            unsigned char r, b, g;
            FrameBuffer::GetPixel(x, y, r, g, b);
            image.setPixel(x, y, sf::Color(r, g, b));
        }
    }
}