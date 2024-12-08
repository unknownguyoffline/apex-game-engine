#include "editor.hpp"
#include "entity_component_system/component.hpp"
#include "utility/macro.hpp"
#include <vendor/imgui/backends/imgui_impl_glfw.h>
#include <vendor/imgui/backends/imgui_impl_opengl3.h>
#include <vendor/imgui/imgui.h>

#define COMPONENT_ADD_BUTTON(component, entity)                                                                        \
    if (ImGui::Button(#component))                                                                                     \
    {                                                                                                                  \
        entity.addComponent<component>();                                                                              \
        addComponentPopup = false;                                                                                     \
    }

template <typename T> void componentGuiSet(Entity &entity);

template <> void componentGuiSet<Transform>(Entity &entity)
{
    if (entity.hasComponent<Transform>())
    {
        ImGui::SeparatorText("Transform");
        Transform &transform = entity.getComponent<Transform>();

        ImGui::DragFloat3("Position", &transform.position.x, 1);
        ImGui::DragFloat3("Rotation", &transform.rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform.scale.x, 1);
    }
}
template <> void componentGuiSet<Sprite>(Entity &entity)
{
    if (entity.hasComponent<Sprite>())
    {
        ImGui::SeparatorText("Sprite");
        Sprite &sprite = entity.getComponent<Sprite>();
        ImGui::DragInt("Sprite count X", &sprite.spriteCount.x, 0.1);
        ImGui::DragInt("Sprite count Y", &sprite.spriteCount.y, 0.1);
        ImGui::SliderInt("Sprite index X", &sprite.spriteIndex.x, 1, sprite.spriteCount.x);
        ImGui::SliderInt("Sprite index Y", &sprite.spriteIndex.y, 1, sprite.spriteCount.y);
        static char path[512];
        strcpy(path, sprite.textureName.c_str());
        ImGui::InputText("Path", path, 512);
        sprite.textureName = path;
    }
}

template <> void componentGuiSet<Box>(Entity &entity)
{
    ImGui::SeparatorText("Box");
    if (entity.hasComponent<Box>())
    {
        ImGui::ColorPicker4("Color", &entity.getComponent<Box>().color.r);
    }
}

void Editor::initialize(void *nativeWindow)
{
    if (nativeWindow == nullptr)
    {
        ERROR("Editor::init [nativeWindow == nullptr]");
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/CONSOLA.TTF", 12);

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)nativeWindow, true);
    ImGui_ImplOpenGL3_Init();
    name[0] = 0;
    path[0] = 0;
}

void Editor::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    std::vector<Entity> entities = m_scene->getList<EntityInfo>();

    ImGui::Begin("entities");
    if (ImGui::Button("Create New Entity") || entityCreationPopup)
    {
        entityCreationPopup = true;

        ImGui::Begin("Create new entity");
        ImGui::InputText("Name", name, 512);
        if (ImGui::Button("Create"))
        {
            m_scene->createEntity(name);
            entityCreationPopup = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            entityCreationPopup = false;
        }
        ImGui::End();
    }
    for (Entity entity : entities)
    {
        if (ImGui::Button(entity.getComponent<EntityInfo>().name.c_str()))
        {
            selectedEntity = entity;
        }
    }
    ImGui::End();

    ImGui::Begin("properties");
    if (selectedEntity.m_registry != nullptr)
    {

        componentGuiSet<Transform>(selectedEntity);
        componentGuiSet<Sprite>(selectedEntity);
        componentGuiSet<Box>(selectedEntity);

        if (ImGui::Button("Add Component") || addComponentPopup)
        {
            addComponentPopup = true;
            ImGui::Begin("Components");
            COMPONENT_ADD_BUTTON(Sprite, selectedEntity);
            COMPONENT_ADD_BUTTON(Box, selectedEntity);
            ImGui::End();
        }
        if (ImGui::Button("Delete"))
        {
            selectedEntity.Destroy();
        }
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
