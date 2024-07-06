#pragma once
#include "types.hpp"

class Camera
{
  public:
    void orthographicCamera(const Transform &transform, glm::vec2 size, glm::vec2 nearFar);
    void perspectiveCamera(const Transform &transform, float fov, glm::vec2 nearFar);

    glm::mat4 &getView()
    {
        return view;
    }
    glm::mat4 &getProj()
    {
        return proj;
    }

  private:
    glm::mat4 view = glm::mat4(1.f);
    glm::mat4 proj = glm::mat4(1.f);
};
