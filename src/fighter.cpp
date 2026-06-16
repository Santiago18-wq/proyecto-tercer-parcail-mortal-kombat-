#include "fighter.hpp"
#include <iostream>
#include <cmath>

Fighter::Fighter(float x, float y, const std::string& characterName)
{
    health = 100;
    currentAnimation = IDLE;
    currentFrame = 0;

    std::string basePath = "assets/imagenes/sprites/" + characterName;

    // Adaptado EXACTAMENTE a los nombres de tus archivos con "_1" y minúsculas/mayúsculas reales
    if (characterName == "chavo")
    {
        LoadAnimationFolder(basePath, "chavo_basico_1", 1, idleTextures);
        LoadAnimationFolder(basePath, "chavo_caminar", 1, walkTextures);
        LoadAnimationFolder(basePath, "chavo_salto", 1, jumpTextures);
        LoadAnimationFolder(basePath, "chavo_ataque", 1, attackTextures);
    }
    else if (characterName == "Kratos" || characterName == "kratos")
    {
        // Nota el uso de "Kratos_ataque_1" que es el que tienes en tu carpeta para Kratos
        LoadAnimationFolder(basePath, "Kratos_ataque_1", 1, idleTextures);
        LoadAnimationFolder(basePath, "kratos_caminar", 1, walkTextures);
        LoadAnimationFolder(basePath, "kratos_salto", 1, jumpTextures);
        LoadAnimationFolder(basePath, "kratos_ataque", 1, attackTextures);
    }
    else
    {
        LoadAnimationFolder(basePath, characterName + "_basico_1", 1, idleTextures);
        LoadAnimationFolder(basePath, characterName + "_caminar", 1, walkTextures);
        LoadAnimationFolder(basePath, characterName + "_salto", 1, jumpTextures);
        LoadAnimationFolder(basePath, characterName + "_ataque", 1, attackTextures);
    }

    // Inicialización del sprite con la textura cargada
    if (!idleTextures.empty() && idleTextures[0])
    {
        sprite = std::make_unique<sf::Sprite>(*idleTextures[0]);
        
        // SFML 3: Le asignamos un cuadro de recorte inicial (por ejemplo, 100x150 píxeles) 
        // para asegurarnos de que la tira grande muestre al menos el primer cuadro del personaje
        sprite->setTextureRect(sf::IntRect({0, 0}, {120, 150}));
    }
    else
    {
        static sf::Texture dummyTexture;
        sprite = std::make_unique<sf::Sprite>(dummyTexture);
    }

    // Ubicar al personaje en el suelo del escenario
    sprite->setPosition({x, y});
}

void Fighter::LoadAnimationFolder(const std::string& basePath, const std::string& animName, int count, std::vector<std::unique_ptr<sf::Texture>>& container)
{
    std::string fullPath = basePath + "/" + animName + ".png";
    auto texture = std::make_unique<sf::Texture>();
    
    if (texture->loadFromFile(fullPath))
    {
        container.push_back(std::move(texture));
    }
    else
    {
        std::cout << "Alerta: No se encontro la imagen en: " << fullPath << "\n";
        auto fallback = std::make_unique<sf::Texture>();
        container.push_back(std::move(fallback));
    }
}

void Fighter::Update()
{
    // Aquí se actualizará el cuadro de animación moviendo el IntRect en el eje X de la tira
}

sf::FloatRect Fighter::GetBounds() const
{
    if (!sprite) return sf::FloatRect();
    return sprite->getGlobalBounds();
}

sf::Vector2f Fighter::GetPosition() const
{
    if (!sprite) return {0.f, 0.f};
    return sprite->getPosition();
}

const sf::Sprite& Fighter::GetSprite() const
{
    return *sprite;
}

int Fighter::GetHealth() const { return health; }

void Fighter::TakeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
}

bool Fighter::IsAlive() const { return health > 0; }

void Fighter::MoveLeft()
{
    if (sprite) sprite->move({-5.f, 0.f});
    currentAnimation = WALK;
}

void Fighter::MoveRight()
{
    if (sprite) sprite->move({5.f, 0.f});
    currentAnimation = WALK;
}

void Fighter::Jump()
{
    currentAnimation = JUMP;
}

void Fighter::FaceRight()
{
    if (sprite)
    {
        sprite->setScale({std::abs(sprite->getScale().x), sprite->getScale().y});
    }
}

void Fighter::FaceLeft()
{
    if (sprite)
    {
        sprite->setScale({-std::abs(sprite->getScale().x), sprite->getScale().y});
    }
}

void Fighter::StartAttack()
{
    currentAnimation = ATTACK;
    currentFrame = 0;
}

void Fighter::StopAttack() {}
bool Fighter::IsAttacking() const { return currentAnimation == ATTACK; }
void Fighter::SetIdle() { currentAnimation = IDLE; }
void Fighter::SetWalk() { currentAnimation = WALK; }
void Fighter::SetAttack() { currentAnimation = ATTACK; }

Fighter::~Fighter()
{
}
