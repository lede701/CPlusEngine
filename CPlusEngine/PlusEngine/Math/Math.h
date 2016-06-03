#include <memory>
#include "tupal.h"
#include "Rect2D.hpp"
#include "Vector2D.hpp"

typedef CPlusEngine::Math::Vector2D<float> fVector2D;
typedef CPlusEngine::Math::Vector2D<int> iVector2D;
typedef std::shared_ptr<fVector2D> fVector2DPtr;
typedef std::shared_ptr<iVector2D> iVector2DPtr;
typedef fVector2D* fVector2DRealPtr;
typedef iVector2D* iVector2DRealPtr;

typedef CPlusEngine::Math::Rect2D<float> fRect2D;
typedef CPlusEngine::Math::Rect2D<int> iRect2D;
typedef fRect2D::Ptr fRect2DPtr;
typedef iRect2D::Ptr iRect2DPtr;

typedef CPlusEngine::Math::tupal<float> fTupal;
typedef CPlusEngine::Math::Vector2D<fTupal> ftVector2D;