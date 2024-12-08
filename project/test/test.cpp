#include "editor.hpp"
#include "engine.hpp"
#include "utility/timer.hpp"
#include <unistd.h>

class Sandbox : public Application
{
    Editor editor;
    Scene *scene;
    SpriteRendererSystem spriteRendererSystem;
    BoxRendererSystem boxRendererSystem;
    SceneSerializer serializer;
    Shader *shader = nullptr;
    Timer timer;
    void onStart() override
    {
        editor.initialize(window->getNativeWindow());
        spriteRendererSystem.initialize();
        boxRendererSystem.initialize();

        scene = serializer.load("main.scene.json");

        editor.loadScene(scene);
        spriteRendererSystem.loadScene(scene);
        boxRendererSystem.loadScene(scene);

        spriteRendererSystem.loadTexture("res/texture.png");
        spriteRendererSystem.loadTexture("res/error.png");
        spriteRendererSystem.loadTexture("res/grass.png");

        shader = Shader::create(loadShaderSource("res/shader.vert", "res/shader.frag"));
    }
    void onUpdate() override
    {
        Renderer::newFrame(glm::vec4(0.258, 0.305, 0.419, 0), window->getProperties().size);
        spriteRendererSystem.draw(shader, window->getProperties().size);
        boxRendererSystem.draw(window->getProperties().size);
        editor.update();
    }
    void onEnd() override
    {
        LOG("app end");
        serializer.save(scene, "main.scene.json");
    }
};

Application *createApplication()
{
    return new Sandbox;
}
