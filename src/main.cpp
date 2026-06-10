#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "fighter.hpp"
#include "characterselect.hpp"

int main()
{
    // =========================
    // VENTANA PRINCIPAL
    // =========================
    sf::RenderWindow window(
        sf::VideoMode({1280u, 720u}),
        "Mortal Kombat"
    );

    // =========================
    // PORTADA (si ya la tienes, la puedes dejar o eliminar)
    // =========================
    sf::Texture portadaTexture;

    if(!portadaTexture.loadFromFile("assets/imagenes/portada.png"))
        return -1;

    sf::Sprite portadaSprite(portadaTexture);

    portadaSprite.setScale(
        {
            1280.f / portadaTexture.getSize().x,
            720.f / portadaTexture.getSize().y
        }
    );

    bool startScreen = true;

    while(window.isOpen() && startScreen)
    {
        while(auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();

            if(event->is<sf::Event::KeyPressed>())
                startScreen = false;
        }

        window.clear();
        window.draw(portadaSprite);
        window.display();
    }

    // =========================
    // SELECCIÓN GRÁFICA (AQUÍ SE ELIMINA CIN / COUT)
    // =========================
    CharacterSelect select;
    select.Run(window);

    // =========================
    // CREACIÓN DE PERSONAJES
    // =========================
    Fighter player1(
        200,
        500,
        select.GetPlayer1()
    );

    Fighter player2(
        900,
        500,
        select.GetPlayer2()
    );

    // =========================
    // JUEGO PRINCIPAL
    // =========================
    while(window.isOpen())
    {
        while(auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();
        }

        // PLAYER 1
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
            player1.MoveLeft();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
            player1.MoveRight();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
            player1.Jump();

        // PLAYER 2
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
            player2.MoveLeft();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
            player2.MoveRight();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
            player2.Jump();

        player1.Update();
        player2.Update();

        // ORIENTACIÓN
        if(player1.GetPosition().x < player2.GetPosition().x)
        {
            player1.FaceRight();
            player2.FaceLeft();
        }
        else
        {
            player1.FaceLeft();
            player2.FaceRight();
        }

        // COLISIÓN
        auto p1Bounds = player1.GetBounds();
        auto p2Bounds = player2.GetBounds();

        if(auto overlap = p1Bounds.findIntersection(p2Bounds))
        {
            float correction = overlap->size.x / 2.f;

            if(player1.GetPosition().x < player2.GetPosition().x)
            {
                player1.SetPosition(player1.GetPosition().x - correction, player1.GetPosition().y);
                player2.SetPosition(player2.GetPosition().x + correction, player2.GetPosition().y);
            }
            else
            {
                player1.SetPosition(player1.GetPosition().x + correction, player1.GetPosition().y);
                player2.SetPosition(player2.GetPosition().x - correction, player2.GetPosition().y);
            }
        }

        window.clear();

        window.draw(player1.GetSprite());
        window.draw(player2.GetSprite());

        window.display();
    }

    return 0;
}

