#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

void OrthographicCamera::update() {
  m_view = glm::mat4(1.f);
  m_projection = glm::mat4(1.f);
  m_view = glm::translate(m_view, m_transform.position);
  m_view = glm::rotate(m_view, m_transform.rotation.x, glm::vec3(1, 0, 0));
  m_view = glm::rotate(m_view, m_transform.rotation.y, glm::vec3(0, 1, 0));
  m_view = glm::rotate(m_view, m_transform.rotation.z, glm::vec3(0, 0, 1));
  m_view = glm::scale(m_view, m_transform.scale);
  m_projection = glm::ortho(m_properties.bottomLeft.x, m_properties.topRight.x,
                            m_properties.bottomLeft.y, m_properties.topRight.y,
                            m_properties.nearFar.x, m_properties.nearFar.y);
}
