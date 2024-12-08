#pragma once

#include "renderer/frame_buffer.hpp"
#include "scene/system.hpp"
#include <engine.hpp>
#include <glad/glad.h>

class Editor : public Application
{
    Scene scene;
    Entity selectedEntity;
    ComponentSystem system;
    std::shared_ptr<FrameBuffer> sceneFrameBuffer;

    void onStart() override;
    void onUpdate(float dt) override;
    void onEnd() override;

    void startFrame();
    void endFrame();

    void testFileManager();

    void addComponentPopup(Scene &scene, Entity &entity);
    void createNewEntityPopup(Scene &scene);
    void fileMenuItem();
    void editMenuItem();
    void menuBar();
    void initialize();
    void entityHierchyWindow();
    void editorPropertyComponentController(Entity &entity);
    void transformComponentController(Entity &entity);
    void boxComponentController(Entity &entity);
    void circleComponentController(Entity &entity);
    void spriteComponentController(Entity &entity);
    void textComponentController(Entity &entity);
    void propertyWindow();
    void sceneWindow(float dt);
    void projectWindow();
    void loadRequiredTextures(Scene &scene);

    template <typename T> void addComponentButton(Entity &entity, const char *label);
};
