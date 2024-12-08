#include "editor.hpp"
#include "core/application.hpp"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"
#include "player.hpp"
#include "scene/component.hpp"
#include "scene/scene_serializer.hpp"
#include "scene/script.hpp"
#include <vector>

void Editor::loadRequiredTextures(Scene &scene)
{
    std::vector<std::string> requiredTextures = scene.getRequiredTextures();
    for (std::string &string : requiredTextures)
    {
        renderer.loadTexture(string.c_str());
    }
}

Entity getEntityByName(Scene &scene, const char *name)
{
    auto view = scene.getView<EditorPropertyComponent>();
    for (entt::entity e : view)
    {
        Entity entity = scene.getEntity(e);
        if (entity.getComponent<EditorPropertyComponent>().name == name)
        {
            return entity;
        }
    }
    WARN("no such entity [%s]", name);
    return {};
}

void Editor::onStart()
{
    testFileManager();

    initialize();
    scene = SceneSerializer::loadScene("test.scene");

    loadRequiredTextures(scene);

    Entity entity = getEntityByName(scene, "player");
    entity.addComponent<NativeScriptComponent>().script.reset(new PlayerScript);
    entity.getComponent<NativeScriptComponent>().script->getEntity() = entity;

    system.initialize();
    system.selectScene(scene);

    auto view = scene.getView<NativeScriptComponent>();
    for (entt::entity e : view)
    {
        Entity entity = scene.getEntity(e);
        entity.getComponent<NativeScriptComponent>().script->onStart();
    }
}

void Editor::onUpdate(float dt)
{

    startFrame();
    menuBar();
    entityHierchyWindow();
    propertyWindow();
    sceneWindow(dt);
    projectWindow();
    endFrame();
}

void Editor::endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    renderer.endFrame();
}

void Editor::testFileManager()
{
}

void Editor::onEnd()
{
    LOG("end of program");
    SceneSerializer::saveScene("test.scene", scene);
}

void Editor::startFrame()
{
    Application::get()->renderer.startFrame(glm::vec4(glm::vec3(0.2), 0.f), Application::get()->window.size);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport();
}

template <typename T> void Editor::addComponentButton(Entity &entity, const char *label)
{
    if (ImGui::Button(label) && !entity.hasComponent<T>())
    {
        entity.addComponent<T>();
        ImGui::ClosePopupsExceptModals();
    }
}
void Editor::addComponentPopup(Scene &scene, Entity &entity)
{
    if (ImGui::BeginPopup("AddComponentPopup"))
    {
        addComponentButton<TransformComponent>(entity, "Transform component");
        addComponentButton<BoxComponent>(entity, "Box component");
        addComponentButton<CircleComponent>(entity, "Circle component");
        addComponentButton<SpriteComponent>(entity, "Sprite component");
        addComponentButton<TextComponent>(entity, "Text component");
        ImGui::EndPopup();
    }
}
void Editor::createNewEntityPopup(Scene &scene)
{
    if (ImGui::BeginPopup("CreateNewEntityPopup"))
    {
        static std::string temporaryName;
        ImGui::InputText("Name", &temporaryName);
        if (ImGui::Button("Create"))
        {
            Entity entity = scene.createEntity();
            entity.addComponent<EditorPropertyComponent>().name = temporaryName;
            entity.addComponent<TransformComponent>();

            ImGui::ClosePopupsExceptModals();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::ClosePopupsExceptModals();
        }
        ImGui::EndPopup();
    }
}
void Editor::fileMenuItem()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::BeginMenu("Open"))
        {
            if (ImGui::MenuItem("Project"))
            {
            }
            if (ImGui::MenuItem("Scene"))
            {
            }
            ImGui::EndMenu();
        }
        ImGui::MenuItem("Save scene");
        ImGui::EndMenu();
    }
}
void Editor::editMenuItem()
{
    if (ImGui::BeginMenu("Edit"))
    {
        ImGui::EndMenu();
    }
}
void Editor::menuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        fileMenuItem();
        editMenuItem();
        ImGui::EndMainMenuBar();
    }
}
void Editor::initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().Fonts->AddFontFromFileTTF("Assets/Fonts/Roboto-Regular.ttf", 16);

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)getWindow()->getNativeWindow(), true);
    ImGui_ImplOpenGL3_Init();

    sceneFrameBuffer.reset(FrameBuffer::create({800, 600}));
}
void Editor::entityHierchyWindow()
{
    ImGui::Begin("Entities");
    if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
    {
        ImGui::OpenPopup("CreateNewEntityPopup");
    }
    createNewEntityPopup(scene);
    auto view = scene.getView<EditorPropertyComponent>();
    for (entt::entity e : view)
    {
        Entity entity = scene.getEntity(e);
        if (ImGui::Selectable(entity.getComponent<EditorPropertyComponent>().name.c_str(), selectedEntity == entity))
        {
            selectedEntity = entity;
        }
    }
    ImGui::End();
}
void Editor::editorPropertyComponentController(Entity &entity)
{
    if (entity.hasComponent<EditorPropertyComponent>())
    {
        EditorPropertyComponent &property = entity.getComponent<EditorPropertyComponent>();
        ImGui::InputText("Name", &property.name);
    }
}
void Editor::transformComponentController(Entity &entity)
{
    if (entity.hasComponent<TransformComponent>())
    {
        TransformComponent &transform = entity.getComponent<TransformComponent>();
        ImGui::SeparatorText("Transform");
        ImGui::DragFloat3("Position", &transform.transform.position.x);
        ImGui::DragFloat3("Rotation", &transform.transform.rotation.x);
        ImGui::DragFloat3("Scale", &transform.transform.scale.x);
    }
}
void Editor::boxComponentController(Entity &entity)
{
    if (entity.hasComponent<BoxComponent>())
    {
        BoxComponent &box = entity.getComponent<BoxComponent>();
        ImGui::SeparatorText("Box");
        ImGui::ColorPicker4("Color", &box.color.x);
    }
}
void Editor::circleComponentController(Entity &entity)
{
    if (entity.hasComponent<CircleComponent>())
    {
        CircleComponent &circle = entity.getComponent<CircleComponent>();
        ImGui::SeparatorText("Circle");
        ImGui::ColorPicker4("Color", &circle.color.x);
    }
}
void Editor::spriteComponentController(Entity &entity)
{
    if (entity.hasComponent<SpriteComponent>())
    {
        SpriteComponent &sprite = entity.getComponent<SpriteComponent>();
        ImGui::SeparatorText("Sprite");
        ImGui::InputText("Path", &sprite.texturePath);
        ImGui::DragInt2("count", &sprite.spriteCount.x);
        ImGui::DragInt2("index", &sprite.spriteIndex.x);
        if (!renderer.hasTexture(sprite.texturePath.c_str()))
        {
            renderer.loadTexture(sprite.texturePath.c_str());
        }
    }
}
void Editor::textComponentController(Entity &entity)
{
    if (entity.hasComponent<TextComponent>())
    {
        TextComponent &text = entity.getComponent<TextComponent>();
        ImGui::InputTextMultiline("Text", &text.text);
        ImGui::ColorPicker4("Color", &text.color.x);
        ImGui::InputText("Font name", &text.fontName);
    }
}
void Editor::propertyWindow()
{
    ImGui::Begin("Properties");
    if (selectedEntity.isCreated())
    {
        transformComponentController(selectedEntity);
        boxComponentController(selectedEntity);
        circleComponentController(selectedEntity);
        spriteComponentController(selectedEntity);
        textComponentController(selectedEntity);
    }

    if (ImGui::Button("Add component"))
    {
        ImGui::OpenPopup("AddComponentPopup");
    }
    if (ImGui::Button("Delete entity"))
    {
        scene.destroyEntity(selectedEntity);
    }
    addComponentPopup(scene, selectedEntity);
    ImGui::End();
}
void Editor::sceneWindow(float dt)
{

    auto view = scene.getView<NativeScriptComponent>();
    for (entt::entity e : view)
    {
        Entity entity = scene.getEntity(e);
        entity.getComponent<NativeScriptComponent>().script->onUpdate(dt);
    }

    ImGui::Begin("Scene");

    glm::vec2 size = {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y};
    sceneFrameBuffer->resizeIfNecessary(size);
    sceneFrameBuffer->select();
    renderer.startFrame(glm::vec4(0.2, 0.2, 0.2, 1.0), size);
    renderer.getCamera().orthographic(size, {-100.f, 100.f});
    system.drawBoxes();
    system.drawCircles();
    system.drawSprite();
    renderer.endFrame();
    sceneFrameBuffer->deselect();

    ImGui::Image(ImTextureID(sceneFrameBuffer->getTextureId()), {size.x, size.y});

    ImGui::End();
}
void Editor::projectWindow()
{
    ImGui::Begin("Project");
    ImGui::End();
}

Application *createApplication()
{
    return new Editor;
};
