#pragma once
#include "ActorState.h"
#include "TransformComponent.h"
#include <vector>

class Component;
class Scene;

class Actor
{
public:
	Actor(Vector3D position = 0, Vector3D size = 1, Quaternion rotation = Quaternion(0, 0));
	~Actor();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
	void AttachScene(Scene& scene);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	void SetActive(ActorState state);
	void SetPosition(Vector3D pPosition);
	std::vector<Component*> GetComponents() const;
	ActorState GetState();
	Scene& GetScene();
	TransformComponent& GetTransformComponent();

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
	void UpdateComponentsTransform();

protected:
	Scene& mScene;
	ActorState mState;
	TransformComponent mTransformComponent;
	bool mIsUpdatingComponents;
	std::vector<Component*> mComponents;
	std::vector<Component*> mPendingComponents;
};

