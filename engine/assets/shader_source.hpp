#pragma once
#include <string>

struct ShaderSource
{
    std::string vertexCode;
    std::string fragmentCode;
};

ShaderSource loadShaderSource(const char *vertexPath, const char *fragmentPath);
