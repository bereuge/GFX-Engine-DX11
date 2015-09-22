/*
To-do
Aspect ratio get/set
Clip distance, camera o frustum?
*/
#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "Transform.h"

namespace GFX
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		GFX::Transform* GetTransform();

		void SetTarget(DirectX::XMFLOAT3 _target);
		DirectX::XMVECTOR GetTarget() const;
		void SetFovAngle(float _fov);
		float GetFovAngle() const;
		void SetNear(float _near);
		float GetNear() const;
		void SetFar(float _far);
		float GetFar() const;

		DirectX::XMMATRIX GetViewMatrix() const;
		DirectX::XMMATRIX GetProjectionMatrix() const;

	private:
		GFX::Transform m_oTransform;
		//DirectX::XMVECTOR m_vPosition;
		DirectX::XMVECTOR m_vTarget;
		DirectX::XMVECTOR m_vUp;

		float m_fFovAngle;
		float m_fNear;
		float m_fFar;
	};
}