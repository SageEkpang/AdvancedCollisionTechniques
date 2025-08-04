#ifndef GAME_OBJECT_ENTITY_H
#define GAME_OBJECT_ENTITY_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"
#include "ComponentEntity.h"
#include <concepts>

#include <unordered_map>
#include <bitset>
#include <typeindex>
#include <typeinfo>

// COMPONENT INCLUDE(s)
#include "Transform.h"
//#include "Render.h"
//#include "PhysicsObject.h"
//#include "RigidbodyObject.h"
//#include "Collider.h"


#include <queue>
#include <list>

// COMPONENT INCLUDE(s)
using namespace DirectX;

unsigned int constexpr MAX_COMPONENTS = 8u;

class GameObjectEntity
{
private:

	// COMPONENT VARIABLE(s)
	unsigned int m_ComponentIndex = 0u;
	std::bitset<MAX_COMPONENTS> m_ComponentBitMask;

	// COMPONENT ARRAY(s)
	std::unordered_map<std::type_index, ComponentEntity*> m_Components;

public:

	Transform m_Transform;

public:

	// CLASS FUNCTION(s)
	GameObjectEntity();
	~GameObjectEntity();

	// BASE FUNCTION(s)
	void Update(float deltaTime);
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);


	// PARENT & CHILDREN FUNCTION(s)

	// PARENT FUNCTION(s)

	// CHILD FUNCTION(s)


	// HELPER FUNCTION(s)
	template<std::derived_from<ComponentEntity> T>
	T* AddComponent();

	template<std::derived_from<ComponentEntity> T>
	void RemoveComponent();

	template<typename T>
	T* FindChildComponent();

	template<typename t>
	std::type_index FindChildComponentID();

	template<std::derived_from<ComponentEntity> T>
	T* GetComponent();

	template<std::derived_from<ComponentEntity> T>
	bool HasComponent();


	
};

/// <summary>
/// Add the component to the component map, if it is derived from the component entity
/// </summary>
/// <typeparam name="T"></typeparam>
template<std::derived_from<ComponentEntity> T>
inline T* GameObjectEntity::AddComponent()
{
	try
	{
		++m_ComponentIndex;
		if (m_ComponentIndex > MAX_COMPONENTS)
		{
			m_ComponentIndex = MAX_COMPONENTS;
			throw;
		}
	}
	catch (...)
	{
		printf("Max Component count has been reached");
		return nullptr;
	}

	m_Components[std::type_index(typeid(T))] = new T();

	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	t_Index->second->m_Owner = this;
	// t_Index->second->m_ID;

	return t_Index == m_Components.end() ? nullptr : static_cast<T*>(t_Index->second);
}

/// <summary>
/// Remove the component from the component list
/// </summary>
/// <typeparam name="T"></typeparam>
template<std::derived_from<ComponentEntity> T>
inline void GameObjectEntity::RemoveComponent()
{
	try
	{
		--m_ComponentIndex;
		if (m_ComponentIndex < 0u)
		{
			m_ComponentIndex = 0u;
			throw;
		}
	}
	catch (...)
	{
		printf("No Component is on this Game Object");
		return;
	}

	m_Components.erase(std::type_index(typeid(T)));
}

/// <summary>
/// Find the Component from Parent Class
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
inline T* GameObjectEntity::FindChildComponent()
{
	T* t_Result = nullptr;
	for (auto& [ComponentId, ComponentType] : m_Components)
	{
		t_Result = dynamic_cast<T*>(ComponentType);
		if (t_Result) { break; }
	}

	return t_Result;
}

/// <summary>
/// Find the ID from Parent Id
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
inline std::type_index GameObjectEntity::FindChildComponentID()
{
	T* t_Result = nullptr;
	for (auto& [ComponentId, ComponentType] : m_Components)
	{
		t_Result = dynamic_cast<T*>(ComponentType);
		if (t_Result)
		{
			return ComponentId;
		}
	}

	return std::type_index(typeid(0));
}

/// <summary>
/// Get the Component currently in the Components map
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<std::derived_from<ComponentEntity> T>
inline T* GameObjectEntity::GetComponent()
{
	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	return t_Index == m_Components.end() ? nullptr : static_cast<T*>(t_Index->second);
}

/// <summary>
/// Check if the game object has said component
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<std::derived_from<ComponentEntity> T>
inline bool GameObjectEntity::HasComponent()
{
	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	return t_Index == m_Components.end() ? false : true;
}

#endif