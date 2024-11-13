#pragma once
#include "../../Scenes/Scene.h"
#include "ActorState.h"
#include "Transform2D.h"
#include "Component.h"
#include <vector>
class Actor
{
public:
	Actor();
	~Actor();
	void Start();
	void AttachScene(Scene* scene);
	void AddComponent(Component* component);
	void RemoveComponent(int index);
	void SetActive(bool active);
	void Update();
private:
	Scene* mScene;
	ActorState mState;
	Transform2D mTransformComponent;
	std::vector<Component*> mComponent;
};

