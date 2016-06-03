#include <iostream>
#include <functional>
#include <PlusEngine/Error/EngineError.h>
#include <PlusEngine/CoreEngine.h>
#include <PlusEngine/Context.h>
#include <PlusEngine/Scene.h>

#include <PlusEngine/Math/Math.h>

#include <PlusEngine/Factories/EntityFactory.h>
#include <PlusEngine/Factories/UIFactory.h>
#include <PlusEngine/Entity/Entity.h>
#include <PlusEngine/Entity/Components/Render/TextureRender.h>
#include <PlusEngine/Entity/Components/Updaters/UpdateCmp.h>

// User Interface Classes
#include <PlusEngine/UI/ui.h>

#include <PlusEngine/Events/IHandler.h>
#include <PlusEngine/Events/EventArgs.h>
#include <PlusEngine/Events/EventKeyArgs.h>

//#include <PlusEngine/Controller/KeyController.h>
#include <PlusEngine/Input/IInput.h>
#include <PlusEngine/Input/SdlInput.h>
#include <PlusEngine/Input/KeyCodes.h>

#include <PlusEngine/Controller/IController.h>
#include <PlusEngine/Controller/KeyboardController.h>


#include <PlusEngine/Graphics/IGraphics.h>
#include <PlusEngine/Graphics/SdlGfx.h>
#include <PlusEngine/Graphics/GfxColor.h>

#include <PlusEngine/Objects/Cameras/Camera.h>

