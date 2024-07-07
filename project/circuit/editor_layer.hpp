#pragma once
#include "core/application.hpp"
#include "core/layer.hpp"
#include "renderer/types.hpp"
#include "utility/macro.hpp"
#include <vendor/imgui/backends/imgui_impl_glfw.h>
#include <vendor/imgui/backends/imgui_impl_opengl3.h>
#include <vendor/imgui/imgui.h>

struct TransformControllerInformation
{
    std::string name;
    Transform *transform;
};
struct CheckboxInformation
{
    bool *value;
    std::string name;
};
class EditorLayer : public Layer
{
  public:
    void onAttach() override;
    void onUpdate() override;
    void onDetach() override;
    void addTransformController(const char *name, Transform &transform);
    void addCheckbox(const char *name, bool &value);

  private:
    GLFWwindow *window = nullptr;
    std::vector<TransformControllerInformation> transformControllers;
    std::vector<CheckboxInformation> checkboxes;
};