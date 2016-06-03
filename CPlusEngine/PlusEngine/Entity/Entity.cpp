#include "Entity.h"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <exception>

namespace CPlusEngine{ namespace Entity
{

	Entity::Entity(unsigned int id, unsigned int layer/* = 10*/)
	{
		_id = id;
		_layer = layer;
		_parent = nullptr;
		_nextComponentId = 0;
		_maxComponentId = 32;
		_transform = CPlusEngine::Entity::Transform::SPtr(new CPlusEngine::Entity::Transform());
		_active = true;
	}


	Entity::~Entity()
	{
	}

	unsigned int Entity::Id()
	{
		return _id;
	}

	unsigned int Entity::Layer()
	{
		return _layer;
	}

	void Entity::Add(Ptr child)
	{
		child->_parent = this;
		_children.push_back(std::move(child));
	}

	Entity::Ptr Entity::Remove(Ptr child)
	{
		// Try and find object in list
		auto found = std::find_if(_children.begin(), _children.end(), [&](Ptr& p) -> bool {return p.get() == child.get(); });
		// Check if find was successful
		assert(found != _children.end());

		// Convert entity found to pointer
		Ptr entity = std::move(*found);
		// Unparent item from me
		entity->_parent = nullptr;
		// Remove entity from my list
		_children.erase(found);

		return entity;
	}

	Entity* Entity::Parent()
	{
		return _parent;
	}

	std::vector<Entity::Ptr>* Entity::Children()
	{
		return &_children;
	}

	void Entity::DebugChildren()
	{
		for (auto it = _children.begin(); it != _children.end(); ++it)
		{
			std::cerr << (*it)->Id() << ": " << (*it)->Position()->ToString() << std::endl;
		}

	}

	bool Entity::IsActive()
	{
		bool bRetVal = _active;
		// Check if parent is defined
		if (_parent != nullptr)
		{
			// Blend my active with parent
			bRetVal = _active && _parent->IsActive();
		}

		return _active;
	}

	void Entity::SetActive(bool active)
	{
		_active = active;
		if (_children.size() > 0)
		{
			for (auto e = _children.begin(); e != _children.end(); ++e)
			{
				(*e)->SetActive(active);
			}
		}
	}


#pragma region Location, location, location....

	CPlusEngine::Entity::Transform::SPtr Entity::Transform()
	{
		return _transform;
	}
	// Shortcuts to the tranform object
	fVector2DPtr Entity::Position()
	{
		fVector2DPtr pos(new fVector2D(Transform()->Position()->x, Transform()->Position()->y));

		// Check if object is parented to another object
		if (_parent != nullptr)
		{
			// Add their position to mine
			pos->x += _parent->Position()->x;
			pos->y += _parent->Position()->y;
		}

		return pos;
	}

	fVector2DPtr Entity::Rotation()
	{
		fVector2DPtr rot(new fVector2D(Transform()->Rotation()->x, Transform()->Rotation()->y));

		// Check if object is parented to another object
		if (_parent != nullptr)
		{
			// Add their position to mine
			rot->x += _parent->Rotation()->x;
			rot->y += _parent->Rotation()->y;
		}

		return rot;
	}

	fVector2DPtr Entity::Scale()
	{
		fVector2DPtr sca(new fVector2D(Transform()->Scale()->x, Transform()->Scale()->y));

		// Check if object is parented to another object
		if (_parent != nullptr)
		{
			// Add their position to mine
			sca->x += _parent->Scale()->x;
			sca->y += _parent->Scale()->y;
		}
		return Transform()->Scale();
	}

#pragma endregion

#pragma region Component Methods

	void Entity::Add(Component::Ptr component)
	{
		component->Id(NextComponentId());
		_component[component->Type()].push_back(std::move(component));
	}

	void Entity::Draw(CPlusEngine::Context::SPtr context)
	{
		if (IsActive())
		{
			// Check if there are drawing components
			if (_component[ComponentType::CT_RENDER].size() > 0)
			{
				for (auto it = _component[ComponentType::CT_RENDER].begin(); it != _component[ComponentType::CT_RENDER].end(); ++it)
				{
					try
					{
						// Need to calulate the new position of the texture
						(*it)->Draw(context, Position()->ToInt());
					}
					catch (std::exception& e)
					{
						std::cerr << e.what() << std::endl;
					}
				}// End for all render types
			}// Endif _component has render objects
			// Process children that need to be drawn
			if (_children.size() > 0)
			{
				for (auto child = _children.begin(); child != _children.end(); ++child)
				{
					(*child)->Draw(context);
				}
			}
		}// Endif entity is active
	}

	
	Entity::CmpData* Entity::Components()
	{
		return &_component;
	}
	
	void Entity::Update(double deltaTime)
	{
		if (IsActive())
		{
			if (_component[ComponentType::CT_UPDATE].size() > 0)
			{
				for (auto it = _component[ComponentType::CT_UPDATE].begin(); it != _component[ComponentType::CT_UPDATE].end(); ++it)
				{
					try
					{
						(*it)->Update(deltaTime);
					}
					catch (std::exception& e)
					{
						std::cerr << e.what() << std::endl;
					}
				}// End for all update components
			}// Endif are there update components
		}// Endif is entity active
	}

	unsigned int Entity::NextComponentId()
	{
		// Store the next id in temp variable
		unsigned int id = _nextComponentId;
		// Time to update next compnent id
		_nextComponentId = (_nextComponentId + 1) % _maxComponentId;
		return id;
	}

#pragma endregion

} }// End namespace CPlusEngine::Entity

