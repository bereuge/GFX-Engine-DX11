#include "Camera.h"

using GFX::Camera;

Camera::Camera()
{
	m_vTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_vUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	m_fFovAngle = 45.0f;
	m_fNear = 1.0f;
	m_fFar = 1000.0f;
}

Camera::~Camera()
{

}

GFX::Transform* Camera::GetTransform()
{
	return &m_oTransform;
}

void Camera::SetTarget(DirectX::XMFLOAT3 _target)
{
	m_vTarget = DirectX::XMLoadFloat3(&_target);
}
DirectX::XMVECTOR Camera::GetTarget() const
{
	return m_vTarget;
}

void Camera::SetFovAngle(float _fov)
{
	m_fFovAngle = _fov;
}

float Camera::GetFovAngle() const
{
	return m_fFovAngle;
}

void Camera::SetNear(float _near)
{
	m_fNear = _near;
}

float Camera::GetNear() const
{
	return m_fNear;
}

void Camera::SetFar(float _far)
{
	m_fFar = _far;
}

float Camera::GetFar() const
{
	return m_fFar;
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	return DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&m_oTransform.GetPosition()), m_vTarget, m_vUp);
}

DirectX::XMMATRIX Camera::GetProjectionMatrix() const
{
	return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_fFovAngle), 800.0f / 600.f, m_fNear, m_fFar);
}