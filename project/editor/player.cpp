#include "player.hpp"
#include "core/application.hpp"

void PlayerScript::onStart()
{
    spriteComponent = &getComponent<SpriteComponent>();
    transform = &getComponent<TransformComponent>().transform;
    player = getEntityByName("player");
    Application::get()->renderer.loadTexture("Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Idle.png");
    Application::get()->renderer.loadTexture("Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Run.png");
    Application::get()->renderer.loadTexture("Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_WallClimbNoMovement.png");
    Application::get()->renderer.loadTexture("Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Crouch.png");
}
void PlayerScript::onUpdate(float dt)
{
    static float t = 0;
    t += dt;
    spriteComponent->texturePath = "Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Idle.png";
    spriteComponent->spriteCount.x = 10;
    if (keyboard.a)
    {
        spriteComponent->texturePath = "Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Run.png";
        spriteComponent->spriteCount.x = -10;
        transform->position.x -= 5;
    }
    if (keyboard.d)
    {
        spriteComponent->texturePath = "Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Run.png";
        spriteComponent->spriteCount.x = 10;
        transform->position.x += 5;
    }
    if (keyboard.w)
    {
        jump();
    }
    if (keyboard.s)
    {
        spriteComponent->texturePath = "Assets/Textures/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Crouch.png";
        spriteComponent->spriteCount.x = 1;
    }

    if (t > 0.1)
    {
        spriteComponent->spriteIndex.x++;
        t = 0;
    }
}

void PlayerScript::jump()
{
}
