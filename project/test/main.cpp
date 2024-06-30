#include "editor.hpp"
#include "engine.hpp"
#include "renderer/camera.hpp"
#include "renderer/texture_library.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <vector>
#include <vendor/entt/entt.hpp>

class Sandbox : public Application
{
    Editor editor;
    Scene scene;

    void onStart() override
    {
        editor.init(window->getNativeWindow());
        editor.loadScene(scene);
    }
    void onUpdate() override
    {
        Renderer::newFrame(glm::vec4(0.258, 0.305, 0.419, 0), window->getProperties().size);
        editor.update();
    }
    void onEnd() override
    {
    }
};

Application *createApplication()
{
    return new Sandbox;
}
