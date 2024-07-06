#pragma once
#include "core/application.hpp"
#include "core/layer.hpp"
#include "utility/macro.hpp"
#include <vendor/imgui/backends/imgui_impl_glfw.h>
#include <vendor/imgui/backends/imgui_impl_opengl3.h>
#include <vendor/imgui/imgui.h>

class EditorLayer : public Layer
{
    void onAttach() override;
    void onUpdate() override;
    void onDetach() override;
};