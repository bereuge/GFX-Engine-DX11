#include "Camera.h"

using GFX::Camera;

Camera::Camera()
{
	m_vPosition = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_vTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_vUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{

}

void Camera::SetPosition(DirectX::XMFLOAT3 _position)
{
	m_vPosition = DirectX::XMLoadFloat3(&_position);
}

DirectX::XMVECTOR Camera::GetPosition() const
{
	return m_vPosition;
}

void Camera::SetTarget(DirectX::XMFLOAT3 _target)
{
	m_vTarget = DirectX::XMLoadFloat3(&_target);
}
DirectX::XMVECTOR Camera::GetTarget() const
{
	return m_vTarget;
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	return DirectX::XMMatrixLookAtLH(m_vPosition, m_vTarget, m_vUp);
}

DirectX::XMMATRIX Camera::GetProjectionMatrix() const
{
	//hard coded
	return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 800.0f / 600.f, 1.0f, 1000.0f);
}