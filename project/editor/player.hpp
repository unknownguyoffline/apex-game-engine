#include "core/application.hpp"
#include "scene/component.hpp"
#include "scene/script.hpp"

class PlayerScript : public NativeScript
{
    SpriteComponent *spriteComponent;
    Transform *transform;
    KeyboardProperties &keyboard = Application::get()->keyboard;
    Entity player;
    void onStart() override;
    void onUpdate(float dt) override;
    void jump();
};
