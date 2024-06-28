#include "opengl_shader.hpp"
#include "utility/macro.hpp"
#include <GLES3/gl3.h>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>

Shader *Shader::create(std::string vertexCode, std::string fragmentCode)
{
    return new OpenglShader(vertexCode, fragmentCode);
}
Shader *Shader::create(const ShaderSource &source) { return new OpenglShader(source.vertexCode, source.fragmentCode); }
OpenglShader::OpenglShader(const std::string &vertexCode, const std::string &fragmentCode)
{
    const char *vertexShaderSource = vertexCode.c_str();
    const char *fragmentShaderSource = fragmentCode.c_str();

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    int success = 0;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        ERROR("vertex error: %s", infoLog);
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        ERROR("fragment error: %s", infoLog);
    }
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        ERROR("program error: %s", infoLog);
        assert(0);
    }
}
int OpenglShader::getLocation(const char *name)
{
    glUseProgram(m_id);
    int loc = glGetUniformLocation(m_id, name);
    if (loc == -1)
    {
        ERROR("uniform not found [%s]", name);
    }
    return loc;
}

void OpenglShader::select() { glUseProgram(m_id); }
void OpenglShader::deselect() { glUseProgram(0); }

void OpenglShader::sentInt(const char *name, int value) { glUniform1i(getLocation(name), value); }
void OpenglShader::sentInt2(const char *name, const glm::ivec2 &value)
{
    glUniform2i(getLocation(name), value.x, value.y);
}
void OpenglShader::sentInt3(const char *name, const glm::ivec3 &value)
{
    glUniform3i(getLocation(name), value.x, value.y, value.z);
}
void OpenglShader::sentInt4(const char *name, const glm::ivec4 &value)
{
    glUniform4i(getLocation(name), value.x, value.y, value.z, value.w);
}

void OpenglShader::sentFloat(const char *name, float value) { glUniform1f(getLocation(name), value); }
void OpenglShader::sentFloat2(const char *name, const glm::vec2 &value)
{

    glUniform2f(getLocation(name), value.x, value.y);
}
void OpenglShader::sentFloat3(const char *name, const glm::vec3 &value)
{

    glUniform3f(getLocation(name), value.x, value.y, value.z);
}
void OpenglShader::sentFloat4(const char *name, const glm::vec4 &value)
{

    glUniform4f(getLocation(name), value.x, value.y, value.z, value.w);
}

void OpenglShader::sentMat4(const char *name, const glm::mat4 &value)
{
    glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
