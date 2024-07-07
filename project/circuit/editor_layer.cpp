#include "editor_layer.hpp"
#include "GLFW/glfw3.h"

void EditorLayer::onAttach()
{

    window = glfwCreateWindow(800, 600, "editor", nullptr, nullptr);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/CascadiaCode_VTT.ttf", 24);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void EditorLayer::onUpdate()
{
    glfwMakeContextCurrent(window);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glm::ivec2 windowSize;
    glfwGetWindowSize(window, &windowSize.x, &windowSize.y);
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({float(windowSize.x), float(windowSize.y)});
    ImGui::Begin("window");
    for (int i = 0; i < transformControllers.size(); i++)
    {
        ImGui::PushID(i);
        ImGui::SeparatorText(transformControllers[i].name.c_str());
        ImGui::DragFloat3("Position", &transformControllers[i].transform->position.x, 0.05f);
        ImGui::DragFloat3("Rotation", &transformControllers[i].transform->rotation.x, 0.05f);
        ImGui::DragFloat3("Scale", &transformControllers[i].transform->scale.x, 0.05f);
        ImGui::PopID();
    }
    for (int i = 0; i < checkboxes.size(); i++)
    {
        ImGui::Checkbox(checkboxes[i].name.c_str(), checkboxes[i].value);
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
    if (glfwWindowShouldClose(window))
    {
        glfwDestroyWindow(window);
        disable();
    }
    glfwMakeContextCurrent((GLFWwindow *)Application::get()->window->getNativeWindow());
}

void EditorLayer::onDetach()
{
    glfwDestroyWindow(window);
}

void EditorLayer::addTransformController(const char *name, Transform &transform)
{
    transformControllers.push_back({name, &transform});
}

void EditorLayer::addCheckbox(const char *name, bool &value)
{
    CheckboxInformation info;
    info.name = name;
    info.value = &value;
    checkboxes.push_back(info);
}
