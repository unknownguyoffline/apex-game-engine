#include "scene/component.hpp"
#include "scene/scene.hpp"
#include "scene/system.hpp"
#include <engine.hpp>

class TestScript : public Script
{
    Transform *transform;
    float t = 0;
    void onStart() override
    {
        transform = &getComponent<TransformComponent>().transform;

        transform->position = {400, 300, 0};
        transform->scale = {100, 100, 1};
    }
    void onUpdate(float dt) override
    {
        t += dt;
        LOG("dt: %f", t);
        transform->position.x += sin(t) * 10.f;
    }
    void onEnd() override
    {
    }
};

class MainApplication : public Application
{
    Scene scene;
    ComponentSystem system;
    Entity entity;
    void onStart() override
    {
        system.initialize();
        system.selectScene(scene);

        entity = scene.createEntity();
        entity.addComponent<TransformComponent>();
        entity.addComponent<SpriteComponent>().texturePath = "/root/Downloads/wallpaper.jpg";
        entity.addComponent<ScriptComponent>().script.reset(new TestScript);

        renderer.loadTexture("/root/Downloads/wallpaper.jpg");
        renderer.getFont() = loadFontFromTTF("/usr/share/fonts/truetype/cascadia/ttf/CascadiaCode.ttf");

        system.startScript();
    }
    void onUpdate(float dt) override
    {

        system.updateScript(dt);

        renderer.startFrame(glm::vec4(1.f), window.size);
        renderer.getCamera().orthographic(window.size, {-100.f, 100.f});
        system.drawBoxes();
        system.drawCircles();
        system.drawSprite();
        renderer.endFrame();
    }
    void onEnd() override
    {
        system.endScript();
    }
};

CREATE_APPLICATION(MainApplication);
