#include "editor.hpp"
#include "entity_component_system/component.hpp"
#include "utility/macro.hpp"
#include <vendor/imgui/backends/imgui_impl_glfw.h>
#include <vendor/imgui/backends/imgui_impl_opengl3.h>
#include <vendor/imgui/imgui.h>

void Editor::initialize(void *nativeWindow)
{
    if (nativeWindow == nullptr)
    {
        ERROR("Editor::init [nativeWindow == nullptr]");
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/CONSOLA.TTF", 24);

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

        if (selectedEntity.hasComponent<Transform>())
        {
            Transform &transform = selectedEntity.getComponent<Transform>();

            ImGui::Separator();
            ImGui::Text("Transform");
            ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
            ImGui::DragFloat3("Rotation", &transform.rotation.x, 0.1f);
            ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
        }
        if (selectedEntity.hasComponent<Sprite>())
        {
            Sprite &sprite = selectedEntity.getComponent<Sprite>();
            ImGui::Separator();
            ImGui::Text("Sprite");
            ImGui::DragInt("horizontal sprite count", &sprite.spriteCount.x);
            ImGui::DragInt("vertical sprite count", &sprite.spriteCount.y);
            ImGui::SliderInt("horizontal sprite index", &sprite.spriteIndex.x, 1, sprite.spriteCount.x);
            ImGui::SliderInt("vertical sprite index", &sprite.spriteIndex.y, 1, sprite.spriteCount.y);
            strcpy(path, sprite.textureName.c_str());
            ImGui::InputText("Path", path, 512);
            sprite.textureName = path;
        }
        if (ImGui::Button("Add Component") || addComponentPopup)
        {
            addComponentPopup = true;
            ImGui::Begin("Components");
            if (ImGui::Button("Sprite"))
            {
                selectedEntity.addComponent<Sprite>();
                addComponentPopup = false;
            }
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
