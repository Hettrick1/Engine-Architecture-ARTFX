#pragma once
#include "ActorState.h"
#include "Transform2D.h"
#include <vector>

class Component;
class Scene;

class Actor
{
public:
	Actor(Vector2D position = 0, Vector2D size = 1, float rotation = 0);
	~Actor();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
	void AttachScene(Scene& scene);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	void SetActive(ActorState state);
	void SetPosition(Vector2D pPosition);
	std::vector<Component*> GetComponents() const;
	ActorState GetState();
	Scene& GetScene();
	Transform2D& GetTransformComponent();

	template<typename  C>
	C* GetComponentOfType() const
	{
		C* result = nullptr;
		for (Component* component : mComponents)
		{
			result = dynamic_cast<C*>(component);
			if (result != nullptr) return result;
		}
		return nullptr;
	}

private:
	Scene& mScene;
	ActorState mState;
	Transform2D mTransformComponent;
	bool mIsUpdatingComponents;
	std::vector<Component*> mComponents;
	std::vector<Component*> mPendingComponents;
};

