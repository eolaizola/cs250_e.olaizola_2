#include <SFML/Graphics.hpp>

#include "FrameBuffer.h"
#include "cs250Parser.h"
#include "Graphics/Rasterizer.h"

int main()
{
    const int WIDTH  = 1280;
    const int HEIGHT = 720;
    bool mWireframe = false;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    FrameBuffer::Init(WIDTH, HEIGHT);

    // Generate image and texture to display
    sf::Image   image;
    sf::Texture texture;
    sf::Sprite  sprite;
    texture.create(WIDTH, HEIGHT);
    image.create(WIDTH, HEIGHT, sf::Color::White);

    CS250Parser::LoadDataFromFile("src/input.txt");
    CS250Parser::UpdateObjects();

    // Init the clock
    sf::Clock clock;
    while (window.isOpen())
    {
        FrameBuffer::Clear(sf::Color::White.r, sf::Color::White.g, sf::Color::White.b);
        
        // Handle input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            mWireframe = true;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            mWireframe = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            CS250Parser::UnloadData();
            CS250Parser::LoadDataFromFile("src/input.txt");
            CS250Parser::UpdateObjects();
        }

        // Fill framebuffer
        sf::Time elapsed = clock.getElapsedTime();
        int      time    = static_cast<int>(elapsed.asSeconds());


        Rasterizer::DrawObjects(WIDTH, HEIGHT, mWireframe);

        // Show image on screen
        FrameBuffer::ConvertFrameBufferToSFMLImage(image);


        texture.update(image);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
    }
    
    FrameBuffer::Free();

    return 0;
}