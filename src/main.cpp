#ifdef _WIN32
#include <windows.h>
#endif

#include <Canis/App.hpp>
#include <Canis/ECS/Decode.hpp>
#include <Canis/Canis.hpp>
#include <Canis/SceneManager.hpp>
#include <Canis/ECS/Systems/RenderHUDSystem.hpp>
#include <Canis/ECS/Systems/RenderTextSystem.hpp>
#include <Canis/ECS/Systems/SpriteRenderer2DSystem.hpp>
#include <Canis/ECS/Systems/SpriteAnimationSystem.hpp>
#include <Canis/ECS/Systems/CollisionSystem2D.hpp>
#include <Canis/ECS/Systems/ButtonSystem.hpp>
#include <Canis/ECS/Systems/RenderMeshSystem.hpp>

#include "ECS/ScriptableEntities/DebugCamera2D.hpp"
#include "ECS/ScriptableEntities/BeachBall.hpp"
#include "ECS/ScriptableEntities/GameOfLifeLoader.hpp"
#include "ECS/ScriptableEntities/SpawnCube.hpp"
#include "ECS/ScriptableEntities/FlyCam.hpp"
#include "ECS/ScriptableEntities/FPSCounter.hpp"

#include "ECS/Systems/GameOfLifeSystem.hpp"

int main(int argc, char* argv[])
{
    Canis::App app("SuperPupStudio", "CanisDemo");

    // decode system
    app.AddDecodeSystem(Canis::DecodeButtonSystem);
    app.AddDecodeSystem(Canis::DecodeCollisionSystem2D);
	app.AddDecodeSystem(Canis::DecodeSpriteAnimationSystem);
    app.AddDecodeSystem(DecodeGameOfLifeSystem);

    // decode render system
    app.AddDecodeRenderSystem(Canis::DecodeRenderHUDSystem);
    app.AddDecodeRenderSystem(Canis::DecodeRenderTextSystem);
    app.AddDecodeRenderSystem(Canis::DecodeSpriteRenderer2DSystem);
    app.AddDecodeRenderSystem(Canis::DecodeRenderMeshSystem);

    // decode scriptable entities
    REGISTER_SCRIPTABLE_COMPONENT(app, DebugCamera2D);
    REGISTER_SCRIPTABLE_COMPONENT(app, BeachBall);
    REGISTER_SCRIPTABLE_COMPONENT(app, GameOfLifeLoader);
    REGISTER_SCRIPTABLE_COMPONENT(app, SpawnCube);
    REGISTER_SCRIPTABLE_COMPONENT(app, FlyCam);
    REGISTER_SCRIPTABLE_COMPONENT(app, FPSCounter);

    // encode / decode component
    REGISTER_COMPONENT(app, Canis::TransformComponent);
    REGISTER_COMPONENT(app, Canis::DirectionalLightComponent);

    REGISTER_COMPONENT_EDITOR(Canis::TagComponent);
    REGISTER_COMPONENT_EDITOR(Canis::TransformComponent);
    REGISTER_COMPONENT_EDITOR(Canis::RectTransformComponent);

    app.Run("Canis Demos");

    return 0;
}