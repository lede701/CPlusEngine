#ifndef H_ICOMPONENT
#define H_ICOMPONENT

#include "../Events/EventArgs.h"
#include "../Context.h"
#include "../Math/Math.h"

namespace CPlusEngine{ namespace Entity
{
	enum class ComponentType
	{
		CT_RENDER,
		CT_UPDATE,
		CT_COLLIDER,
		CT_SCRIPT,
		CT_NONE
	};

	class IComponent
	{
	public:
		typedef std::unique_ptr<IComponent> Ptr;
		typedef std::shared_ptr<IComponent> SPtr;

	private:
		ComponentType _type;
		unsigned int _id;

	public:
		IComponent(ComponentType type);
		virtual ~IComponent();

		ComponentType Type();
		virtual unsigned int Id();
		virtual unsigned int Id(unsigned int id);

		virtual void Init() = 0;

		virtual void Start();
		virtual void Update(double deltaTime);
		virtual void Draw(CPlusEngine::Context::SPtr context, iVector2D& dest);
		virtual void End();
		virtual void Event(CPlusEngine::Events::EventArgs::Ptr e);

	};

} }// End namespace CPlusEngine::Entity



#endif