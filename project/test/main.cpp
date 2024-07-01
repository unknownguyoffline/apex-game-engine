#include "editor.hpp"
#include "engine.hpp"

class Sandbox : public Application
{
    Editor editor;
    Scene *scene;
    SpriteSystem spriteSystem;
    SceneSerializer serializer;
    Shader *shader = nullptr;

    void onStart() override
    {
        editor.initialize(window->getNativeWindow());
        spriteSystem.initialize();

        scene = serializer.load("main.scene.json");

        editor.loadScene(scene);
        spriteSystem.loadScene(scene);
        spriteSystem.loadTexture("res/texture.png");
        spriteSystem.loadTexture("res/error.png");
        spriteSystem.loadTexture("res/grass.png");
        shader = Shader::create(loadShaderSource("res/shader.vert", "res/shader.frag"));
    }
    void onUpdate() override
    {
        Renderer::newFrame(glm::vec4(0.258, 0.305, 0.419, 0), window->getProperties().size);
        spriteSystem.draw(shader, window->getProperties().size);
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
