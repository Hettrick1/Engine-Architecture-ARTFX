#pragma once
#include "ActorState.h"
#include "Transform2DComponent.h"
#include <vector>

class Component;
class Scene;

class Actor
{
public:
	Actor(Vector2D position = 0, Vector2D size = 1, float rotation = 0);
	~Actor();
	void Start();
	void Update();
	void Destroy();
	void AttachScene(Scene& scene);
	void AddComponent(Component* component);
	void RemoveComponent(int index);
	void SetActive(bool active);
	std::vector<Component*> GetComponents() const;
	ActorState GetState();
	Scene& GetScene();
	Transform2DComponent& GetTransformComponent();
private:
	Scene& mScene;
	ActorState mState;
	Transform2DComponent mTransformComponent;
	std::vector<Component*> mComponents;
};

