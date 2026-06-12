#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class CharacterSelect
{
public:

    CharacterSelect();

    void Run(sf::RenderWindow& window);

    std::string GetPlayer1() const;
    std::string GetPlayer2() const;

private:

    static const int CHARACTER_COUNT = 4;

    int p1Index;
    int p2Index;

    bool p1Ready;
    bool p2Ready;

    std::string p1Result;
    std::string p2Result;

    // Imágenes que aparecen en la selección
    std::string selectPaths[CHARACTER_COUNT];

    // Imágenes que usará Fighter
    std::string fighterPaths[CHARACTER_COUNT];

    sf::Texture textures[CHARACTER_COUNT];

    std::vector<sf::Sprite> sprites;

    sf::Vector2f positions[CHARACTER_COUNT];

    sf::RectangleShape cursorP1;
    sf::RectangleShape cursorP2;

    void LoadCharacters();

    void UpdateCursorPositions();

    void MoveP1(sf::Keyboard::Scancode key);
    void MoveP2(sf::Keyboard::Scancode key);

    void ConfirmP1();
    void ConfirmP2();

    void Draw(sf::RenderWindow& window);
};
