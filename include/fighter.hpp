#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

class Fighter
{
public:
    Fighter(float x, float y, const std::string& imagePath);
    ~Fighter();

    // Movimiento
    void MoveLeft();
    void MoveRight();
    void Jump();
    void Update();

    // Sprite
    const sf::Sprite& GetSprite() const;
    void SetPosition(float x, float y);
    sf::Vector2f GetPosition() const;
    sf::FloatRect GetBounds() const;

    // Dirección
    void FaceRight();
    void FaceLeft();

    // Vida
    int GetHealth() const;
    void TakeDamage(int damage);
    bool IsAlive() const;

    // Ataque
    void StartAttack();
    void StopAttack();
    bool IsAttacking() const;

    // ====== NUEVO ======
    void SetIdle();
    void SetWalk();
    void SetAttack();
    // ===================

private:

    // Movimiento
    float speed;
    float velocityY;
    float gravity;
    bool isJumping;
    float groundY;

    // Vida
    int health;

    // Ataque
    bool attacking;

    // Imagen
    std::unique_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite;

    //=================================================
    //              SISTEMA DE ANIMACIÓN
    //=================================================

    enum AnimationState
    {
        IDLE,
        WALK,
        ATTACK
    };

    AnimationState currentAnimation;

    std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> walkFrames;
    std::vector<sf::IntRect> attackFrames;

    int currentFrame;

    sf::Clock animationClock;

    float frameTime;

    void UpdateAnimation();

};
