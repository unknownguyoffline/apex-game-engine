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
    Transform transform;
    Transform cameraTransform;
    Transform boxTransform;
    bool drawCircle = false;

  public:
    void onStart() override
    {
        layerStack.addLayer(&editorLayer);
        editorLayer.addTransformController("player", transform);
        editorLayer.addTransformController("camera", cameraTransform);
        editorLayer.addTransformController("box", boxTransform);
        editorLayer.addCheckbox("name", drawCircle);
    }
    void onUpdate(float dt) override
    {
        Renderer::startFrame(vec4(0.1), window->getProperties().size);
        Renderer::getCamera().orthographicCamera(cameraTransform, {window->getAspectRation(), 1.f}, {-100.f, 100.f});
        Renderer::drawBox(boxTransform, vec4(0.06, 0.47, 0.69, 1));
        Renderer::drawBox({boxTransform.position + vec3(0.5), boxTransform.rotation, boxTransform.scale},
                          vec4(0.29, 0.30, 0.30, 1));
        Renderer::drawCircle(transform, vec4(0.8, 0.17, 0.18, 1));
        Renderer::drawCircle({transform.position + vec3(0.5), transform.rotation, transform.scale},
                             vec4(0.21, 0.56, 0.42, 1.0));
        Renderer::endFrame();
    }
    void onEnd() override
    {
    }
};

Application *createApplication()
{
    return new Circuit;
}
