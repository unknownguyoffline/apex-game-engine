#include "assets/shader_source.hpp"
#include "core/application.hpp"
#include "entity_component_system/component.hpp"
#include "entity_component_system/entity.hpp"
#include "entity_component_system/scene.hpp"
#include "entity_component_system/scene_serializer.hpp"
#include "entity_component_system/system.hpp"
#include "renderer/camera.hpp"
#include "renderer/index_buffer.hpp"
#include "renderer/renderer.hpp"
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"
#include "renderer/texture_library.hpp"
#include "renderer/vertex_buffer.hpp"
#include "utility/macro.hpp"
#include <fstream>
#include <iostream>
#include <vendor/entt/entt.hpp>
#include <vendor/json/single_include/nlohmann/json.hpp>
