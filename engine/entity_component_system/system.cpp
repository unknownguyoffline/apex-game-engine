#include "system.hpp"
#include <glm/gtc/matrix_transform.hpp>
void SpriteSystem::initialize()
{
    uint32_t index[] = {0, 1, 2, 2, 3, 0};
    vbo = VertexBuffer::create(sizeof(Vertex) * 4, nullptr);

    vbo->addLayout(FLOAT3);
    vbo->addLayout(FLOAT2);
    vbo->addLayout(FLOAT3);

    ibo = IndexBuffer::create(sizeof(uint32_t) * 6, index);
}
void SpriteSystem::loadTexture(const char *path)
{
    if (fopen(path, "r") == NULL)
    {
        ERROR("file not found [%s]", path);
    }

    m_textureLibrary.loadTexture(path);
}
void SpriteSystem::loadScene(Scene *scene)
{
    m_scene = scene;
}
void SpriteSystem::draw(Shader *shader, glm::vec2 windowSize)
{
    std::vector<Entity> entities = m_scene->getList<Sprite>();
    for (Entity &entity : entities)
    {
        Sprite &sprite = entity.getComponent<Sprite>();
        Transform &transform = entity.getComponent<Transform>();

        Vertex vertices[4];
        vertices[0].position = glm::vec3(0.5, 0.5, 0.0);
        vertices[1].position = glm::vec3(0.5, -0.5, 0.0);
        vertices[2].position = glm::vec3(-0.5, -0.5, 0.0);
        vertices[3].position = glm::vec3(-0.5, 0.5, 0.0);

        glm::vec2 sizePerSprite = 1.f / glm::vec2(sprite.spriteCount);

        vertices[0].uv =
            glm::vec2(sizePerSprite.x * sprite.spriteIndex.x, sizePerSprite.y * (sprite.spriteIndex.y - 1));
        vertices[1].uv = glm::vec2(sizePerSprite.x * sprite.spriteIndex.x, sizePerSprite.y * sprite.spriteIndex.y);
        vertices[2].uv =
            glm::vec2(sizePerSprite.x * (sprite.spriteIndex.x - 1), sizePerSprite.y * sprite.spriteIndex.y);
        vertices[3].uv =
            glm::vec2(sizePerSprite.x * (sprite.spriteIndex.x - 1), sizePerSprite.y * (sprite.spriteIndex.y - 1));

        vbo->subData(sizeof(vertices), vertices, 0);

        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        glm::mat4 proj = glm::mat4(1);

        model = glm::translate(model, transform.position);
        model = glm::rotate(model, transform.rotation.x, glm::vec3(1, 0, 0));
        model = glm::rotate(model, transform.rotation.y, glm::vec3(0, 1, 0));
        model = glm::rotate(model, transform.rotation.z, glm::vec3(0, 0, 1));
        model = glm::scale(model, transform.scale);

        proj = glm::ortho(0.f, windowSize.x, 0.f, windowSize.y, 0.f, 100.f);

        Texture *texture = m_textureLibrary.getTexture(sprite.textureName);
        if (texture != nullptr)
            texture->select(0);

        shader->select();

        shader->sentMat4("model", model);
        shader->sentMat4("view", view);
        shader->sentMat4("proj", proj);

        Renderer::draw(vbo, ibo, 6);
    }
}
