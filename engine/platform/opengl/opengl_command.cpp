#include "opengl_command.hpp"
#include <glad/glad.h>

RenderCommand *RenderCommand::create()
{
    return new OpenglRenderCommand;
}

void OpenglRenderCommand::init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_CULL_FACE);
}
void OpenglRenderCommand::clearScreen(const glm::vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.b);
    glClear(GL_COLOR_BUFFER_BIT);
}
void OpenglRenderCommand::drawArray(int count)
{
    glDrawArrays(GL_TRIANGLES, 0, count);
}
void OpenglRenderCommand::drawIndexed(int count)
{
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
void OpenglRenderCommand::drawInstancedIndex(int count, int instanceCount)
{
    glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0, instanceCount);
}
void OpenglRenderCommand::setViewport(glm::ivec2 pos, glm::ivec2 size)
{
    glViewport(pos.x, pos.y, size.x, size.y);
}
void OpenglRenderCommand::clearDepthbuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}
