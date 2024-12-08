#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Camera::orthographic(const glm::vec2 &size, const glm::vec2 &nearFar)
{
    proj = glm::mat4(1.f);
    proj = glm::ortho(0.f, size.x, 0.f, size.y, nearFar.x, nearFar.y);
}

void Camera::perspective(float fov, const glm::vec2 &viewSize, const glm::vec2 &nearFar)
{
    proj = glm::mat4(1.f);
    proj = glm::perspective(glm::radians(fov), viewSize.x / viewSize.y, nearFar.x, nearFar.y);
}

void Camera::lookAt(const glm::vec3 &position, const glm::vec3 &lookAt, const glm::vec3 &up)
{
    view = glm::mat4(1.f);
    view = glm::lookAt(position, lookAt, up);
}

void Camera::lookTowards(const glm::vec3 &position, const glm::vec3 &towards, const glm::vec3 &up)
{
    view = glm::mat4(1.f);
    view = glm::lookAt(position, position + towards, up);
}
void Camera::setViewTransform(const Transform &transform)
{
    view = glm::mat4(1.f);
    view = getTransformMatrix(transform);
}
