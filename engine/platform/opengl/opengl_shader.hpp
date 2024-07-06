#include "renderer/shader.hpp"

class OpenglShader : public Shader
{
  public:
    OpenglShader(const std::string &vertexACode, const std::string &fragmentCode);
    ~OpenglShader() override;
    void select() override;
    void deselect() override;

    void sentInt(const char *name, int value) override;
    void sentInt2(const char *name, const glm::ivec2 &value) override;
    void sentInt3(const char *name, const glm::ivec3 &value) override;
    void sentInt4(const char *name, const glm::ivec4 &value) override;

    void sentFloat(const char *name, float value) override;
    void sentFloat2(const char *name, const glm::vec2 &value) override;
    void sentFloat3(const char *name, const glm::vec3 &value) override;
    void sentFloat4(const char *name, const glm::vec4 &value) override;

    void sentMat4(const char *name, const glm::mat4 &value) override;

  private:
    int getLocation(const char *name);
    uint32_t m_id = 0;
};
