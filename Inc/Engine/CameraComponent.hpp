#pragma once

#include "Component.hpp"

namespace Verge3D {


enum class ProjectionType : uint8_t {
		Perspective,
		Ortho
};

struct CameraParams
{
		ProjectionType projectionType;
		float zNear, zFar;
		CameraParams() : zNear(0.25f), zFar(10000.0f) {}
};


class CameraComponent : public Component {
public:

};

}
