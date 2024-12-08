#pragma once
#include "types.hpp"
#include <glm/glm.hpp>

class Camera
{
  public:
    void orthographic(const glm::vec2 &size, const glm::vec2 &nearFar);
    void perspective(float fov, const glm::vec2 &viewSize, const glm::vec2 &nearFar);
    void lookAt(const glm::vec3 &position, const glm::vec3 &lookAt, const glm::vec3 &up = glm::vec3(0, 1, 0));
    void lookTowards(const glm::vec3 &position, const glm::vec3 &towards, const glm::vec3 &up = glm::vec3(0, 1, 0));
    void setViewTransform(const Transform &transform);

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
