#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MapManager {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string currentMap;

    void setupSprite();

public:
    MapManager();

    void loadRandomMap();
    void draw(sf::RenderWindow& window);
};
