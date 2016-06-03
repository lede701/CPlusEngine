#ifndef H_ENTITY
#define H_ENTITY

#include <memory>
#include <vector>
#include <map>

#include "IComponent.h"
#include "Transform.h"
#include "../Context.h"

namespace CPlusEngine{ namespace Entity
{

	class Entity
	{
	public:
		typedef std::unique_ptr<Entity> Ptr;
		typedef std::shared_ptr<Entity> SPtr;

		typedef IComponent Component;
		typedef std::map<ComponentType, std::vector<Component::Ptr>> CmpData;

	private:

		std::vector<Ptr> _children;
		CmpData _component;

		unsigned int _id;
		unsigned int _layer;
		unsigned int _nextComponentId;
		unsigned int _maxComponentId;
		bool _active;

		Entity* _parent;

		Transform::SPtr _transform;

	public:
#pragma region Ctors for class

		Entity(unsigned int id, unsigned int layer = 10);
		virtual ~Entity();

#pragma endregion

#pragma region Identifier Methods

		unsigned int Id();
		unsigned int Layer();

#pragma endregion

#pragma region Child Management (Like that can happen!)

		virtual void Add(Ptr child);
		virtual Ptr Remove(Ptr child);

		virtual Entity* Parent();

		std::vector<Ptr>* Children();

		void DebugChildren();

		virtual bool IsActive();
		virtual void SetActive(bool active);

#pragma endregion

#pragma region Component Methods

		virtual void Add(Component::Ptr component);
		virtual unsigned int NextComponentId();

		CmpData* Components();

		virtual void Draw(CPlusEngine::Context::SPtr context);
		virtual void Update(double deltaTime);

#pragma endregion

#pragma region Location, location, location....
		
		virtual Transform::SPtr Transform();
		// Shortcuts to the tranform object
		virtual fVector2DPtr Position();
		virtual fVector2DPtr Rotation();
		virtual fVector2DPtr Scale();

#pragma endregion

	};

} }// End namespace CPlusEngine::Entity



#endif