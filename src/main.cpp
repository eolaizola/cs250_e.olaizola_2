/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_2
Filename: main.cpp

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 01/30/2023
----------------------------------------------------------------------------------------------------------*/

#include <SFML/Graphics.hpp>

#include "../src/Graphics/FrameBuffer/FrameBuffer.h"
#include "../src/Utils/cs250Parser.h"
#include "../src/Graphics/Rasterizer/Rasterizer.h"
#include "../src/Input/Input.h"
#include "../src/Graphics/Camera/Camera.h"

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
    Input::GetInstance().InitInput();
    Camera cam;
    cam.UpdateCamera();
    
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
            cam.UpdateCamera();
        }

        // Fill framebuffer
        sf::Time elapsed = clock.getElapsedTime();
        int      time    = static_cast<int>(elapsed.asSeconds());

        cam.UpdateCamera();
        Input::GetInstance().UpdateInput(cam);
        Rasterizer::DrawObjects(WIDTH, HEIGHT, mWireframe, cam);

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