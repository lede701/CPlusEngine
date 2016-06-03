#include "IComponent.h"

namespace CPlusEngine{ namespace Entity
{

	IComponent::IComponent(ComponentType type)
	{
		_type = type;
		Id(_id);
	}


	IComponent::~IComponent()
	{
	}

	ComponentType IComponent::Type()
	{
		return _type;
	}

	void IComponent::Start()
	{

	}

	void IComponent::Update(double deltaTime)
	{

	}

	void IComponent::Draw(CPlusEngine::Context::SPtr context, iVector2D& dest)
	{
		// Nothing to really do here for the interface.  You need to implement this in your custom render class.
	}

	void IComponent::End()
	{

	}

	void IComponent::Event(CPlusEngine::Events::EventArgs::Ptr e)
	{

	}


	unsigned int IComponent::Id()
	{
		return _id;
	}

	unsigned int IComponent::Id(unsigned int id)
	{
		_id = id;
		return _id;
	}

} }// End namespace CPlusEngine::Entity

