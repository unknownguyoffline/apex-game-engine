#include "shader_source.hpp"
#include "utility/macro.hpp"
#include <fstream>

ShaderSource loadShaderSource(const char *vertexPath, const char *fragmentPath)
{
    ShaderSource shaderSource;
    std::ifstream input(vertexPath);
    if (!input.is_open())
    {
        ERROR("file not found [%s]", vertexPath);
    }
    while (!input.eof())
    {
        shaderSource.vertexCode += input.get();
    }
    shaderSource.vertexCode[shaderSource.vertexCode.size() - 1] = 0;
    input.close();
    input.open(fragmentPath);
    if (!input.is_open())
    {
        ERROR("file not found [%s]", fragmentPath);
    }
    while (!input.eof())
    {
        shaderSource.fragmentCode += input.get();
    }
    shaderSource.fragmentCode[shaderSource.fragmentCode.size() - 1] = 0;
    return shaderSource;
}
