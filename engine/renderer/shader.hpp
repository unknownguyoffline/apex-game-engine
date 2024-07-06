#pragma once
#include "assets/shader_source.hpp"
#include <glm/glm.hpp>
#include <string>

class Shader
{
  public:
    virtual void select() = 0;
    virtual void deselect() = 0;

    virtual void sentInt(const char *name, int value) = 0;
    virtual void sentInt2(const char *name, const glm::ivec2 &value) = 0;
    virtual void sentInt3(const char *name, const glm::ivec3 &value) = 0;
    virtual void sentInt4(const char *name, const glm::ivec4 &value) = 0;

    virtual void sentFloat(const char *name, float value) = 0;
    virtual void sentFloat2(const char *name, const glm::vec2 &value) = 0;
    virtual void sentFloat3(const char *name, const glm::vec3 &value) = 0;
    virtual void sentFloat4(const char *name, const glm::vec4 &value) = 0;

    virtual void sentMat4(const char *name, const glm::mat4 &value) = 0;

    virtual ~Shader()
    {
    }

    static Shader *create(std::string vertexCode, std::string fragmentCode);
    static Shader *create(const ShaderSource &source);
};
