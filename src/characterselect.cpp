#include "characterselect.hpp"

CharacterSelect::CharacterSelect()
{
    p1Index = 0;
    p2Index = 3;

    p1Ready = false;
    p2Ready = false;

    imagePaths[0] = "assets/imagenes/selec chavo.jpeg";
    imagePaths[1] = "assets/imagenes/selec omniman.jpeg";
    imagePaths[2] = "assets/imagenes/selec kratos.jpeg";
    imagePaths[3] = "assets/imagenes/selec rengoku.jpeg";

    positions[0] = {180.f, 120.f};
    positions[1] = {700.f, 120.f};
    positions[2] = {180.f, 400.f};
    positions[3] = {700.f, 400.f};

    LoadCharacters();

    cursorP1.setSize({200.f, 200.f});
    cursorP1.setFillColor(sf::Color::Transparent);
    cursorP1.setOutlineThickness(5.f);
    cursorP1.setOutlineColor(sf::Color::Green);

    cursorP2.setSize({200.f, 200.f});
    cursorP2.setFillColor(sf::Color::Transparent);
    cursorP2.setOutlineThickness(5.f);
    cursorP2.setOutlineColor(sf::Color::Red);

    UpdateCursorPositions();
}

void CharacterSelect::LoadCharacters()
{
    sprites.clear();

    for(int i = 0; i < CHARACTER_COUNT; i++)
    {
        textures[i].loadFromFile(imagePaths[i]);

        sprites.emplace_back(textures[i]);

        // Las imágenes originales son de 1254x1254.
        // Esta escala las deja aproximadamente en 200x200.
        sprites[i].setScale({0.16f, 0.16f});

        sprites[i].setPosition(positions[i]);
    }
}

void CharacterSelect::UpdateCursorPositions()
{
    cursorP1.setPosition(positions[p1Index]);
    cursorP2.setPosition(positions[p2Index]);
}

void CharacterSelect::MoveP1(sf::Keyboard::Scancode key)
{
    if(p1Ready)
        return;

    switch(key)
    {
        case sf::Keyboard::Scancode::A:

            if(p1Index == 1)
                p1Index = 0;

            else if(p1Index == 3)
                p1Index = 2;

        break;

        case sf::Keyboard::Scancode::D:

            if(p1Index == 0)
                p1Index = 1;

            else if(p1Index == 2)
                p1Index = 3;

        break;

        case sf::Keyboard::Scancode::W:

            if(p1Index >= 2)
                p1Index -= 2;

        break;

        case sf::Keyboard::Scancode::S:

            if(p1Index <= 1)
                p1Index += 2;

        break;

        default:
        break;
    }

    UpdateCursorPositions();
}

void CharacterSelect::MoveP2(sf::Keyboard::Scancode key)
{
    if(p2Ready)
        return;

    switch(key)
    {
        case sf::Keyboard::Scancode::Left:

            if(p2Index == 1)
                p2Index = 0;

            else if(p2Index == 3)
                p2Index = 2;

        break;

        case sf::Keyboard::Scancode::Right:

            if(p2Index == 0)
                p2Index = 1;

            else if(p2Index == 2)
                p2Index = 3;

        break;

        case sf::Keyboard::Scancode::Up:

            if(p2Index >= 2)
                p2Index -= 2;

        break;

        case sf::Keyboard::Scancode::Down:

            if(p2Index <= 1)
                p2Index += 2;

        break;

        default:
        break;
    }

    UpdateCursorPositions();
}
void CharacterSelect::ConfirmP1()
{
    // Evita que ambos jugadores escojan el mismo personaje
    if(p1Index == p2Index && p2Ready)
        return;

    p1Ready = true;
    p1Result = imagePaths[p1Index];
}

void CharacterSelect::ConfirmP2()
{
    // Evita que ambos jugadores escojan el mismo personaje
    if(p1Index == p2Index && p1Ready)
        return;

    p2Ready = true;
    p2Result = imagePaths[p2Index];
}

void CharacterSelect::Draw(sf::RenderWindow& window)
{
    for(int i = 0; i < CHARACTER_COUNT; i++)
    {
        window.draw(sprites[i]);
    }

    window.draw(cursorP1);
    window.draw(cursorP2);
}

void CharacterSelect::Run(sf::RenderWindow& window)
{
    while(window.isOpen())
    {
        while(auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
                return;
            }

            if(auto key = event->getIf<sf::Event::KeyPressed>())
            {
                // Movimiento jugador 1
                MoveP1(key->scancode);

                // Movimiento jugador 2
                MoveP2(key->scancode);

                // Confirmar jugador 1
                if(key->scancode == sf::Keyboard::Scancode::Space)
                {
                    ConfirmP1();
                }

                // Confirmar jugador 2
                if(key->scancode == sf::Keyboard::Scancode::Enter)
                {
                    ConfirmP2();
                }
            }
        }

        window.clear(sf::Color(30,30,30));

        Draw(window);

        window.display();

        if(p1Ready && p2Ready)
        {
            return;
        }
    }
}

std::string CharacterSelect::GetPlayer1() const
{
    return p1Result;
}

std::string CharacterSelect::GetPlayer2() const
{
    return p2Result;
}

