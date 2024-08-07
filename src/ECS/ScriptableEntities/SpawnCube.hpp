#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>

#include "Rotate.hpp"
#include "LookAtTarget.hpp"
#include "Teleporting.hpp"

class SpawnCube : public Canis::ScriptableEntity
{
public:
    void OnCreate()
    {
        
    }

    void OnReady()
    {
        Canis::TransformComponent t;
        t.registry = &(GetScene().entityRegistry);
        t.position.x += 5.f;

        Canis::Entity emptyParent = CreateEntity();
        
        emptyParent.AddComponent<Canis::TransformComponent>(t);
        emptyParent.AddScript<Rotate>();
        

        Canis::TransformComponent transform;
        transform.registry = &(GetScene().entityRegistry);
        transform.position.x += 1.5;

        Canis::MeshComponent mesh;
        mesh.modelHandle.id = Canis::AssetManager::LoadModel("assets/models/white_block.obj");
        mesh.material = Canis::AssetManager::LoadMaterial("assets/materials/box.material");

        Canis::SphereColliderComponent collider;

        Canis::Entity cube = CreateEntity();
        cube.AddComponent<Canis::TransformComponent>(transform);
        cube.AddComponent<Canis::ColorComponent>();
        cube.AddComponent<Canis::MeshComponent>(mesh);
        cube.AddComponent<Canis::SphereColliderComponent>(collider);        

        //cube.AddScript<Rotate>();

        cube.SetParent(emptyParent);

        Canis::Entity smallCube = CreateEntity();
        smallCube.AddComponent<Canis::TransformComponent>(transform);
        smallCube.AddComponent<Canis::ColorComponent>();
        smallCube.AddComponent<Canis::MeshComponent>(mesh);
        smallCube.AddComponent<Canis::SphereColliderComponent>(collider);

        smallCube.SetPosition(glm::vec3(0.5f));
        smallCube.SetScale(glm::vec3(0.5f));
        smallCube.SetParent(cube);

        Canis::Entity smallSmallCube = CreateEntity();
        smallSmallCube.AddComponent<Canis::TransformComponent>(transform);
        smallSmallCube.AddComponent<Canis::ColorComponent>();
        smallSmallCube.AddComponent<Canis::MeshComponent>(mesh);
        smallSmallCube.AddComponent<Canis::SphereColliderComponent>(collider);

        smallSmallCube.SetPosition(glm::vec3(0.5f));
        smallSmallCube.SetScale(glm::vec3(0.5f));
        smallSmallCube.SetParent(smallCube);

        Canis::Entity c = CreateEntity();

        {
            Canis::TransformComponent tr;
            tr.registry = &(GetScene().entityRegistry);    

            mesh.modelHandle.id = Canis::AssetManager::LoadModel("assets/models/monkey.obj");        

            
            c.AddComponent<Canis::TransformComponent>(tr);
            c.AddComponent<Canis::ColorComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            c.AddComponent<Canis::MeshComponent>(mesh);
            c.AddComponent<Canis::SphereColliderComponent>(collider);
            c.AddScript<Teleporting>();
        }

        {
            LookAtTarget& lookAtTarget = cube.AddScript<LookAtTarget>();
            
            lookAtTarget.target = c;
        }

        for (int i = 0; i < 5; i++)
        {
            Canis::Entity cc = CreateEntity();

            Canis::TransformComponent tr;
            tr.registry = &(GetScene().entityRegistry); 
            tr.position.x += Canis::RandomFloat(-20.0f, 20.0f);
            tr.position.z += Canis::RandomFloat(-20.0f, 20.0f);

            mesh.modelHandle.id = Canis::AssetManager::LoadModel("assets/models/monkey.obj");        

            
            cc.AddComponent<Canis::TransformComponent>(tr);
            cc.AddComponent<Canis::ColorComponent>();
            cc.AddComponent<Canis::MeshComponent>(mesh);
            cc.AddComponent<Canis::SphereColliderComponent>(collider);
            LookAtTarget& lookAtTarget = cc.AddScript<LookAtTarget>();
            
            lookAtTarget.target = c;
        
        }
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        
    }
};

bool DecodeSpawnCube(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "SpawnCube")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<SpawnCube>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}