#include "engine.hpp"
#include "renderer/camera.hpp"
#include "renderer/mesh.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "editor_layer.hpp"

using namespace glm;

class Circuit : public Application
{
    EditorLayer editorLayer;

  public:
    void onStart() override
    {
        layerStack.addLayer(&editorLayer);
    }
    void onUpdate(float dt) override
    {
        LOG("delta time: %f", dt);
        Renderer::newFrame(vec4(1), window->getProperties().size);
    }
    void onEnd() override
    {
    }
};

Application *createApplication()
{
    return new Circuit;
}
