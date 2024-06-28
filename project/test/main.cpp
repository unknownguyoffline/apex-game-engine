#include "engine.hpp"
#include "renderer/camera.hpp"
#include "renderer/texture_library.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <vector>
#include <vendor/entt/entt.hpp>

void spriteSystem(const std::vector<Entity> &entities, VertexBuffer *vbo, IndexBuffer *ibo, Shader *shader,
                  const glm::mat4 &view, const glm::mat4 &proj)
{
    for (Entity entity : entities)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0);

        Sprite sprite = entity.getComponent<Sprite>();
        Transform transform = entity.getComponent<Transform>();

        modelMatrix = glm::translate(modelMatrix, transform.position);
        modelMatrix = glm::rotate(modelMatrix, transform.rotation.x, glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, transform.rotation.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, transform.rotation.z, glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, transform.scale);

        Vertex vertex[4];
        vertex[0].position = glm::vec3(0.5, 0.5, 0);
        vertex[1].position = glm::vec3(0.5, -0.5, 0);
        vertex[2].position = glm::vec3(-0.5, -0.5, 0);
        vertex[3].position = glm::vec3(-0.5, 0.5, 0);

        vertex[0].uv = glm::vec2(float(1.0 / sprite.spriteCount.x) * sprite.selectedSprite.x,
                                 float(1.0 / sprite.spriteCount.y) * float(sprite.selectedSprite.y - 1));
        vertex[1].uv = glm::vec2(float(1.0 / sprite.spriteCount.x) * sprite.selectedSprite.x,
                                 float(1.0 / sprite.spriteCount.y) * sprite.selectedSprite.y);
        vertex[2].uv = glm::vec2(float(1.0 / sprite.spriteCount.x) * float(sprite.selectedSprite.x - 1),
                                 float(1.0 / sprite.spriteCount.y) * sprite.selectedSprite.y);
        vertex[3].uv = glm::vec2(float(1.0 / sprite.spriteCount.x) * float(sprite.selectedSprite.x - 1),
                                 float(1.0 / sprite.spriteCount.y) * float(sprite.selectedSprite.y - 1));

        vbo->select();
        vbo->subData(sizeof(vertex), vertex, 0);
        ibo->select();
        shader->select();
        shader->sentMat4("model", modelMatrix);
        shader->sentMat4("view", view);
        shader->sentMat4("proj", proj);
        Renderer::draw(vbo, ibo, 6);
    }
}

class Editor
{
  public:
    void init(void *nativeWindow);
    void loadScene(Scene &scene) { m_scene = &scene; }
    void update();

  private:
    Scene *m_scene = nullptr;
};

void Editor::init(void *nativeWindow)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)nativeWindow, true);
    ImGui_ImplOpenGL3_Init();
}

void Editor::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("entities");
    ImGui::End();

    ImGui::Begin("properties");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

class Sandbox : public Application
{
    Editor editor;
    VertexBuffer *vbo;
    IndexBuffer *ibo;
    Shader *shader;

    TextureLibrary textureLibrary;
    OrthographicCamera camera;

    bool newEntityPopup = false;

    Scene scene;
    void onStart() override
    {
        editor.init(window->getNativeWindow());

        uint32_t index[] = {0, 1, 2, 2, 3, 0};

        Entity entity = scene.createEntity("main entity");

        entity.addComponent<Sprite>();
        Sprite &sprite = entity.getComponent<Sprite>();
        Transform &transform = entity.getComponent<Transform>();

        sprite.spriteCount = glm::ivec2(32, 32);
        sprite.selectedSprite = glm::ivec2(1);
        sprite.texture = Texture::create(loadImage("res/texture.png"));
        transform.position = glm::vec3(100, 100, 0);
        transform.scale = glm::vec3(100, 100, 0);

        vbo = VertexBuffer::create(sizeof(Vertex) * 4, nullptr);
        vbo->addLayout(FLOAT3);
        vbo->addLayout(FLOAT2);
        vbo->addLayout(FLOAT3);
        ibo = IndexBuffer::create(sizeof(index), index);
        shader = Shader::create(loadShaderSource("res/shader.vert", "res/shader.frag"));
    }
    void onUpdate() override
    {
        Renderer::newFrame(glm::vec4(0.1), window->getProperties().size);

        glm::mat4 viewMatrix = glm::mat4(1.0);
        glm::mat4 projMatrix = glm::mat4(1.0);
        projMatrix = glm::ortho(0.f, (float)window->getProperties().size.x, 0.f, (float)window->getProperties().size.y,
                                0.f, 100.f);

        spriteSystem(scene.getList<Sprite>(), vbo, ibo, shader, viewMatrix, projMatrix);

        camera.update();
        editor.update();
    }
    void onEnd() override {}
};

Application *createApplication() { return new Sandbox; }
