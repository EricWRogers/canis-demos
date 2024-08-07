#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/TransformComponent.hpp>

class Teleporting : public Canis::ScriptableEntity
{
public:
    Canis::Entity target;
    float time = 3.0f;

    void OnCreate() {}

    void OnReady() {}

    void OnDestroy() {}

    void OnUpdate(float _dt)
    {
        using namespace Canis;
        using namespace glm;

        time -= _dt;

        if ( time < 0.0f )
        {
            time = 3.0f;

            auto& transform = GetComponent<TransformComponent>();

            SetTransformPosition(transform, 
                vec3(
                    Canis::RandomFloat(-20.0f, 20.0f),
                    0.0f,
                    Canis::RandomFloat(-20.0f, 20.0f)
                )
            );
        }
    }
};