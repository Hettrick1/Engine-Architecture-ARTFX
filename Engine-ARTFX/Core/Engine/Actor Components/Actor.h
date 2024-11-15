#pragma once
#include "../../Scenes/Scene.h"
#include "ActorState.h"
#include "Transform2D.h"
#include "Component.h"
#include <vector>

class Transform;
class Component;
class Scene;

class Actor
{
public:
	Actor();
	~Actor();
	void Start();
	void Update();
	void Destroy();
	void AttachScene(Scene* scene);
	void AddComponent(Component* component);
	void RemoveComponent(int index);
	void SetActive(bool active);
	std::vector<Component*> GetComponents() const;
	ActorState GetState();
private:
	Scene* mScene;
	ActorState mState;
	Transform2D mTransformComponent;
	std::vector<Component*> mComponents;
};

