#include "editor_layer.hpp"
#include "engine.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Circuit : public Application
{
    Transform transform;
    Transform cameraTransform;
    EditorLayer *editor = new EditorLayer;
    void onStart() override
    {
        layerStack.addLayer((Layer *)editor);
        editor->renderUiCallback = std::bind(&Circuit::onRenderUi, this);
        renderer.getFont() = loadFontFromTTF("Assets/Fonts/CascadiaCode.ttf");
    }
    void onRenderUi()
    {
        editor->transformController("camera", cameraTransform);
        editor->transformController("box", transform);
    }
    void onUpdate(float dt) override
    {
        LOG("window size: %f %f", window.size.x, window.size.y);
        static float time = 0;
        time += dt;
        renderer.startFrame(glm::vec4(0.1), window.size);

        // renderer.getCamera().orthographic(window->getProperties().size, {-100.f, 100.f});

        glm::vec3 direction = glm::vec3(sin(cameraTransform.rotation.x), 0.f, cos(cameraTransform.rotation.x));
        renderer.getCamera().perspective(90.f, window.size, {0.01f, 100.f});
        renderer.getCamera().lookTowards(cameraTransform.position, direction);

        renderer.drawBox(transform, glm::vec4(1.f));

        renderer.endFrame();
    }
    void onEnd() override
    {
    }
};

Application *createApplication()
{
    return new Circuit;
}
