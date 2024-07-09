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

    renderUiCallback = std::bind(&EditorLayer::defaultRenderUi, this);
}
void EditorLayer::defaultRenderUi()
{
    ImGui::Text("no render up callback set");
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
    renderUiCallback();
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

void EditorLayer::transformController(const char *name, Transform &transform)
{
    ImGui::PushID(name);
    ImGui::SeparatorText(name);
    ImGui::DragFloat3("Position", &transform.position.x);
    ImGui::DragFloat3("Rotation", &transform.rotation.x);
    ImGui::DragFloat3("Scale", &transform.scale.x);
    ImGui::PopID();
}

void EditorLayer::checkBox(const char *name, bool &value)
{
    ImGui::Checkbox(name, &value);
}
void EditorLayer::drag(const char *name, int &value)
{
    ImGui::DragInt(name, &value);
}

void EditorLayer::drag(const char *name, glm::ivec2 &value)
{
    ImGui::DragInt2(name, &value.x);
}

void EditorLayer::slider(const char *name, int &value, int min, int max)
{
    ImGui::SliderInt(name, &value, min, max);
}
