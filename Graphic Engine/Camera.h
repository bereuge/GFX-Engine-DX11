/*
To-do
Aspect ratio get/set
Ortographic camera?
Clip distance, camera o frustum?
*/
#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

namespace GFX
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		//Chiediamo una const reference?
		void SetPosition(DirectX::XMFLOAT3 _position);
		DirectX::XMVECTOR GetPosition() const;
		void SetTarget(DirectX::XMFLOAT3 _target);
		DirectX::XMVECTOR GetTarget() const;

		DirectX::XMMATRIX GetViewMatrix() const;
		DirectX::XMMATRIX GetProjectionMatrix() const;

	private:
		DirectX::XMVECTOR m_vPosition;
		DirectX::XMVECTOR m_vTarget;
		DirectX::XMVECTOR m_vUp;
	};
}