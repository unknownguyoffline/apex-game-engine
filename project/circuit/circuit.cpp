#include "GLFW/glfw3.h"
#include "engine.hpp"
#include "renderer/camera.hpp"
#include "renderer/mesh.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <ostream>
#include <string>

#include "editor_layer.hpp"

using namespace glm;

class Circuit : public Application
{
    EditorLayer editor;
    Transform transform;
    Transform cameraTransform;
    Transform boxTransform;
    Sprite sprite;

  public:
    void onStart() override
    {
        layerStack.addLayer(&editor);
        editor.renderUiCallback = std::bind(&Circuit::onEditorUi, this);

        Image image = loadImage("res/texture.png");
        sprite.texture.reset(Texture::create(image));

        cameraTransform.scale = vec3(0.1, 0.1, 1);
    }
    void onEditorUi()
    {
        editor.transformController("camera", cameraTransform);
        editor.transformController("circle", transform);
        editor.transformController("box", boxTransform);

        editor.drag("sprite count x", sprite.count.x);
        editor.drag("sprite count y", sprite.count.y);

        editor.slider("sprite index x", sprite.index.x, 0, sprite.count.x - 1);
        editor.slider("sprite index y", sprite.index.y, 0, sprite.count.y - 1);
    }
    void onRender()
    {

        renderer2D.drawBox(boxTransform, vec4(0.06, 0.47, 0.69, 1));
        renderer2D.drawBox({boxTransform.position + vec3(0.5), boxTransform.rotation, boxTransform.scale},
                           vec4(0.29, 0.30, 0.30, 1));
        renderer2D.drawCircle(transform, vec4(0.8, 0.17, 0.18, 1));
        renderer2D.drawCircle({transform.position + vec3(0.5), transform.rotation, transform.scale},
                              vec4(0.21, 0.56, 0.42, 1.0));

        renderer2D.drawSprite({boxTransform.position - vec3(0.5), boxTransform.rotation, boxTransform.scale}, sprite);
    }
    void onUpdate(float dt) override
    {
        renderer2D.startFrame(vec4(0.1), window->getProperties().size);
        renderer2D.getCamera().orthographicCamera(cameraTransform, {window->getAspectRation(), 1.f}, {-100.f, 100.f});
        onRender();
        renderer2D.endFrame();
    }
    void onEnd() override
    {
    }
};

Application *createApplication()
{
    return new Circuit;
}
