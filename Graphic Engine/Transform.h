#pragma once

#include <DirectXMath.h>

namespace GFX
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void SetPosition(float _x, float _y, float _z);
		DirectX::XMFLOAT3 GetPosition() const;
		//setrotation
		//getrotation
		//setscale
		//getscale
		//translate
		//rotateto
		void SetRotation(float _angleX, float _angleY, float _angleZ);
		void SetRotationX(float _angle);
		void SetRotationY(float _angle);
		void SetRotationZ(float _angle);
		DirectX::XMMATRIX GetWorldMatrix() const;

	private:
		DirectX::XMFLOAT3 m_vTranslation;
		DirectX::XMFLOAT3 m_vScale;
		float m_aRotX;
		float m_aRotY;
		float m_aRotZ;
	};
}