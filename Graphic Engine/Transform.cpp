#include "Transform.h"

using GFX::Transform;

Transform::Transform()
{
	m_vTranslation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vScale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{

}

void Transform::SetPosition(float _x, float _y, float _z)
{
	m_vTranslation.x = _x;
	m_vTranslation.y = _y;
	m_vTranslation.z = _z;
}

DirectX::XMFLOAT3 Transform::GetPosition() const
{
	return m_vTranslation;
}

void Transform::SetRotation(float _angleX, float _angleY, float _angleZ)
{
	m_aRotX = _angleX;
	m_aRotY = _angleY;
	m_aRotZ = _angleZ;
}

void Transform::SetRotationX(float _angle)
{
	m_aRotX = _angle;
}

void Transform::SetRotationY(float _angle)
{
	m_aRotY = _angle;
}

void Transform::SetRotationZ(float _angle)
{
	m_aRotZ = _angle;
}

//Is this okay? It is working...
DirectX::XMMATRIX Transform::GetWorldMatrix() const
{
	DirectX::XMMATRIX _translate = DirectX::XMMatrixTranslation(m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	DirectX::XMMATRIX _scale = DirectX::XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z);
	DirectX::XMMATRIX _rotate = DirectX::XMMatrixRotationX(m_aRotX) * DirectX::XMMatrixRotationY(m_aRotY) * DirectX::XMMatrixRotationZ(m_aRotZ);
	//return DirectX::XMMatrixMultiply(_scale, _translate);
	return _scale * _rotate * _translate;
}