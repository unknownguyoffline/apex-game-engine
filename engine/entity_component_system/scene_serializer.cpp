#include "scene_serializer.hpp"
#include <fstream>
#include <vendor/json/include/nlohmann/json.hpp>

Scene *SceneSerializer::load(const char *path)
{
    Scene *scene = new Scene;
    std::ifstream input(path);
    if (!input.is_open())
        return scene;
    nlohmann::json json = nlohmann::json::parse(input);
    int count = json["entityCount"];
    for (int i = 0; i < count; i++)
    {
        std::string name = json["entity" + std::to_string(i)]["EntityInfo"]["name"];
        Entity entity = scene->createEntity(name);
        std::vector<float> position = json["entity" + std::to_string(i)]["Transform"]["position"];
        std::vector<float> rotation = json["entity" + std::to_string(i)]["Transform"]["rotation"];
        std::vector<float> scale = json["entity" + std::to_string(i)]["Transform"]["scale"];
        entity.getComponent<Transform>().position = {position[0], position[1], position[2]};
        entity.getComponent<Transform>().rotation = {rotation[0], rotation[1], rotation[2]};
        entity.getComponent<Transform>().scale = {scale[0], scale[1], scale[2]};
        if (!json["entity" + std::to_string(i)]["Sprite"].is_null())
        {
            std::vector<float> spriteCount = json["entity" + std::to_string(i)]["Sprite"]["spriteCount"];
            std::vector<float> spriteIndex = json["entity" + std::to_string(i)]["Sprite"]["spriteIndex"];
            std::string textureName = json["entity" + std::to_string(i)]["Sprite"]["textureName"];

            entity.addComponent<Sprite>();
            Sprite &sprite = entity.getComponent<Sprite>();
            sprite.spriteCount = {spriteCount[0], spriteCount[1]};
            sprite.spriteIndex = {spriteIndex[0], spriteIndex[1]};
            sprite.textureName = textureName;
        }
    }
    return scene;
}
void SceneSerializer::save(Scene *scene, const char *path)
{
    std::ofstream out(path);
    nlohmann::json json;
    std::vector<Entity> entities = scene->getList<EntityInfo>();
    json["entityCount"] = entities.size();
    for (int i = 0; i < entities.size(); i++)
    {
        Entity &entity = entities[i];
        if (entity.hasComponent<Transform>())
        {
            Transform &transform = entity.getComponent<Transform>();
            json["entity" + std::to_string(i)]["EntityInfo"]["name"] = entity.getComponent<EntityInfo>().name;
            json["entity" + std::to_string(i)]["Transform"]["position"] = {transform.position.x, transform.position.y,
                                                                           transform.position.z};
            json["entity" + std::to_string(i)]["Transform"]["rotation"] = {transform.rotation.x, transform.rotation.y,
                                                                           transform.rotation.z};
            json["entity" + std::to_string(i)]["Transform"]["scale"] = {transform.scale.x, transform.scale.y,
                                                                        transform.scale.z};
        }
        if (entity.hasComponent<Sprite>())
        {
            Sprite &sprite = entity.getComponent<Sprite>();
            json["entity" + std::to_string(i)]["Sprite"]["spriteCount"] = {sprite.spriteCount.x, sprite.spriteCount.y};
            json["entity" + std::to_string(i)]["Sprite"]["spriteIndex"] = {sprite.spriteIndex.x, sprite.spriteIndex.y};
            json["entity" + std::to_string(i)]["Sprite"]["textureName"] = sprite.textureName;
        }
    }
    out << json;
}
