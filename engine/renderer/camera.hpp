#pragma once
#include "entity_component_system/component.hpp"
#include <glm/glm.hpp>

class PerspectiveCamera
{
  public:
  private:
    glm::mat4 m_view = glm::mat4(1.0);
    glm::mat4 m_projection = glm::mat4(1.0);
};

struct OrthographicCameraProperties
{
    glm::vec2 bottomLeft = glm::vec2(0);
    glm::vec2 topRight = glm::vec2(0);
    glm::vec2 nearFar = glm::vec2(0);
};

class OrthographicCamera
{
  public:
    OrthographicCameraProperties &getProperties() { return m_properties; }
    Transform &getTransform() { return m_transform; }

    glm::mat4 &getViewMatrix() { return m_view; }
    glm::mat4 &getProjectionMatrix() { return m_projection; }
    void update();

  private:
    OrthographicCameraProperties m_properties;
    Transform m_transform;
    glm::mat4 m_view = glm::mat4(1.0);
    glm::mat4 m_projection = glm::mat4(1.0);
};
