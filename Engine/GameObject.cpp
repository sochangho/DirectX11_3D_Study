#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "MonoBehavior.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
//#include "Animator.h"




GameObject::GameObject()
{



}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if(component)component->Awake();
	}

	for (shared_ptr<MonoBehavior>& script : _scripts)
	{
		script->Awake();
	}

}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)component->Start();
	}

	for (shared_ptr<MonoBehavior>& script : _scripts)
	{
		script->Start();
	}

}

void GameObject::Update()
{

	for (shared_ptr<Component>& component : _components)
	{
		if (component)component->Update();
	}

	for (shared_ptr<MonoBehavior>& script : _scripts)
	{
		script->Update();
	}


}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)component->LateUpdate();
	}

	for (shared_ptr<MonoBehavior>& script : _scripts)
	{
		script->LateUpdate();
	}

}

void GameObject::FixedUpdate()
{

	for (shared_ptr<Component>& component : _components)
	{
		if (component)component->FixedUpdate();
	}

	for (shared_ptr<MonoBehavior>& script : _scripts)
	{
		script->FixedUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);

	assert(index < FIXED_COMPONENT_COUNT);

	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);

	return static_pointer_cast<Transform>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Camera);

	return static_pointer_cast<Camera>(component);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::MeshRenderer);

	return static_pointer_cast<MeshRenderer>(component);
}

//shared_ptr<Animator> GameObject::GetAnimator()
//{
//	shared_ptr<Component> component = GetFixedComponent(ComponentType::Animator);
//
//	return static_pointer_cast<Animator>(component);
//}

shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		shared_ptr<Transform> transform = make_shared<Transform>();
		AddComponent(transform);

	}

	return GetTransform();
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());

	if (index < FIXED_COMPONENT_COUNT) {
		_components[index] = component;
	}
	else {
		shared_ptr<MonoBehavior> script = dynamic_pointer_cast<MonoBehavior>(component);	
	    _scripts.push_back(script);
	}
}

