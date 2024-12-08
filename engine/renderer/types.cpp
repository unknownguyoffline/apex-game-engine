#include "types.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 getTransformMatrix(const Transform &transform)
{
    glm::mat4 matrix = glm::mat4(1);

    matrix = glm::translate(matrix, transform.position);
    matrix = glm::rotate(matrix, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, transform.scale);

    return matrix;
}
