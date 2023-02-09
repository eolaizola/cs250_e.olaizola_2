#include "FrameBuffer.h"

int             FrameBuffer::width     = 0;
int             FrameBuffer::height    = 0;
unsigned char * FrameBuffer::imageData = nullptr;

void FrameBuffer::Init(int w, int h)
{
    width     = w;
    height    = h;
    int size  = 3 * width * height;
    imageData = new unsigned char[size];
}

void FrameBuffer::Free()
{
    Clear(0, 0, 0);
    delete[] imageData;
}

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

void FrameBuffer::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    //Sanity check
    if ((x > width || x < 0) || (y > height || y < 0))
        return;

    imageData[(y * width + x) * 3 + 0] = r;
    imageData[(y * width + x) * 3 + 1] = g;
    imageData[(y * width + x) * 3 + 2] = b;
}

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