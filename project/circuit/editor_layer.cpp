#include "editor_layer.hpp"

void EditorLayer::onAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/CascadiaCode_VTT.ttf", 24);

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)Application::get()->window->getNativeWindow(), true);
    ImGui_ImplOpenGL3_Init();
}

void EditorLayer::onUpdate()
{
    LOG("update");
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("window");
    ImGui::Text("window text");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorLayer::onDetach()
{
}
