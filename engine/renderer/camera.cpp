#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Camera::orthographicCamera(const Transform &transform, glm::vec2 size, glm::vec2 nearFar)
{
    view = glm::mat4(1.f);
    proj = glm::mat4(1.f);

    view = glm::translate(view, transform.position);
    view = glm::rotate(view, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
    view = glm::rotate(view, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
    view = glm::rotate(view, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
    view = glm::scale(view, transform.scale);

    proj = glm::ortho(0.f, size.x, 0.f, size.y, nearFar.x, nearFar.y);
}
