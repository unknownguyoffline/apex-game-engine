#include "scene_serializer.hpp"
#include "nlohmann/json.hpp"
#include "scene/component.hpp"
#include "utility/macro.hpp"
#include <fstream>

void storeEditorPropertyComponent(Entity &entity, std::string id, nlohmann::json &json)
{
    if (entity.hasComponent<EditorPropertyComponent>())
    {
        json[id]["EditorPropertyComponent"]["name"] = entity.getComponent<EditorPropertyComponent>().name;
    }
}
void storeTransformComponent(Entity &entity, std::string id, nlohmann::json &json)
{
    if (entity.hasComponent<TransformComponent>())
    {
        Transform transform = entity.getComponent<TransformComponent>().transform;
        json[id]["TransformComponent"]["position"] = {transform.position.x, transform.position.y, transform.position.z};
        json[id]["TransformComponent"]["rotation"] = {transform.rotation.x, transform.rotation.y, transform.rotation.z};
        json[id]["TransformComponent"]["scale"] = {transform.scale.x, transform.scale.y, transform.scale.z};
    }
}
void storeBoxComponent(Entity &entity, std::string id, nlohmann::json &json)
{
    if (entity.hasComponent<BoxComponent>())
    {
        BoxComponent &component = entity.getComponent<BoxComponent>();
        json[id]["BoxComponent"]["color"] = {component.color.x, component.color.y, component.color.z, component.color.w};
    }
}
void storeCircleComponent(Entity &entity, std::string id, nlohmann::json &json)
{
    if (entity.hasComponent<CircleComponent>())
    {
        CircleComponent &component = entity.getComponent<CircleComponent>();
        json[id]["CircleComponent"]["color"] = {component.color.x, component.color.y, component.color.z, component.color.w};
    }
}
void storeSpriteComponent(Entity &entity, std::string id, nlohmann::json &json)
{
    if (entity.hasComponent<SpriteComponent>())
    {
        SpriteComponent &component = entity.getComponent<SpriteComponent>();
        json[id]["SpriteComponent"]["texturePath"] = component.texturePath;
        json[id]["SpriteComponent"]["count"] = {component.spriteCount.x, component.spriteCount.y};
        json[id]["SpriteComponent"]["index"] = {component.spriteIndex.x, component.spriteIndex.y};
    }
}
void storeTextComponent(Entity &entity, std::string id, nlohmann::json &json)
{
    if (entity.hasComponent<TextComponent>())
    {
        TextComponent &component = entity.getComponent<TextComponent>();
        json[id]["TextComponent"]["fontName"] = component.fontName;
        json[id]["TextComponent"]["color"] = {component.color.x, component.color.y, component.color.z, component.color.w};
        json[id]["TextComponent"]["text"] = component.text;
    }
}

std::string SceneSerializer::serialize(Scene &scene)
{
    nlohmann::json json;
    auto view = scene.getView<EditorPropertyComponent>();
    int i = 0;
    for (entt::entity e : view)
    {
        Entity entity = scene.getEntity(e);
        std::string entityId = "entity" + std::to_string(i);

        storeEditorPropertyComponent(entity, entityId, json);
        storeTransformComponent(entity, entityId, json);
        storeBoxComponent(entity, entityId, json);
        storeCircleComponent(entity, entityId, json);
        storeTextComponent(entity, entityId, json);
        storeSpriteComponent(entity, entityId, json);

        i++;
    }
    return json.dump(4);
}
void extractEditorPropertyComponent(Entity &entity, const std::string id, nlohmann::json &json)
{
    if (!json[id]["EditorPropertyComponent"].is_null())
    {
        EditorPropertyComponent &component = entity.addComponent<EditorPropertyComponent>();
        component.name = json[id]["EditorPropertyComponent"]["name"];
    }
}
void extractTransformComponent(Entity &entity, const std::string id, nlohmann::json &json)
{
    if (!json[id]["TransformComponent"].is_null())
    {
        TransformComponent &component = entity.addComponent<TransformComponent>();
        std::vector<float> position = json[id]["TransformComponent"]["position"];
        std::vector<float> rotation = json[id]["TransformComponent"]["rotation"];
        std::vector<float> scale = json[id]["TransformComponent"]["scale"];
        component.transform.position = {position[0], position[1], position[2]};
        component.transform.rotation = {rotation[0], rotation[1], rotation[2]};
        component.transform.scale = {scale[0], scale[1], scale[2]};
    }
}
void extractBoxComponent(Entity &entity, const std::string id, nlohmann::json &json)
{

    if (!json[id]["BoxComponent"].is_null())
    {
        BoxComponent &component = entity.addComponent<BoxComponent>();
        std::vector<float> color = json[id]["BoxComponent"]["color"];
        component.color = {color[0], color[1], color[2], color[3]};
    }
}
void extractCircleComponent(Entity &entity, const std::string id, nlohmann::json &json)
{
    if (!json[id]["CircleComponent"].is_null())
    {
        CircleComponent &component = entity.addComponent<CircleComponent>();
        std::vector<float> color = json[id]["CircleComponent"]["color"];
        component.color = {color[0], color[1], color[2], color[3]};
    }
}
void extractSpriteComponent(Entity &entity, const std::string id, nlohmann::json &json)
{

    if (!json[id]["SpriteComponent"].is_null())
    {
        SpriteComponent &component = entity.addComponent<SpriteComponent>();
        component.texturePath = json[id]["SpriteComponent"]["texturePath"];
        std::vector<int> count = json[id]["SpriteComponent"]["count"];
        std::vector<int> index = json[id]["SpriteComponent"]["index"];
        component.spriteIndex = {index[0], index[1]};
        component.spriteCount = {count[0], count[1]};
    }
}
void extractTextComponent(Entity &entity, const std::string id, nlohmann::json &json)
{
    if (!json[id]["TextComponent"].is_null())
    {
        TextComponent &component = entity.addComponent<TextComponent>();
        component.fontName = json[id]["TextComponent"]["fontName"];
        std::vector<float> color = json[id]["TextComponent"]["color"];
        component.text = json[id]["TextComponent"]["text"];
        component.color = {color[0], color[1], color[2], color[3]};
    }
}

Scene SceneSerializer::deserialize(const std::string &data)
{
    nlohmann::json json;
    json = nlohmann::json::parse(data);
    Scene scene;

    for (int i = 0; !json["entity" + std::to_string(i)].is_null(); i++)
    {
        std::string id = "entity" + std::to_string(i);
        Entity entity = scene.createEntity();

        extractEditorPropertyComponent(entity, id, json);
        extractTransformComponent(entity, id, json);
        extractBoxComponent(entity, id, json);
        extractCircleComponent(entity, id, json);
        extractSpriteComponent(entity, id, json);
        extractTextComponent(entity, id, json);
    }
    return scene;
}
void SceneSerializer::saveScene(const char *path, Scene &scene)
{
    std::ofstream out(path);
    std::string data = SceneSerializer::serialize(scene);
    out.write(data.data(), data.size());
    out.close();
}
Scene SceneSerializer::loadScene(const char *path)
{
    ARG_CHECK(fopen(path, "r") == NULL, Scene());
    std::string data;

    std::ifstream input(path);
    if (input.is_open())
    {
        while (!input.eof())
        {
            std::string line;
            input >> line;
            line += '\n';
            data += line;
        }
    }
    return SceneSerializer::deserialize(data);
}
