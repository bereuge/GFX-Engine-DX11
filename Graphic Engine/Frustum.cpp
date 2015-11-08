#include "Frustum.h"

using namespace DirectX;

Frustum::Frustum() { }

Frustum::~Frustum() { }

void Frustum::CreateFrustum(float _screenDepth, XMMATRIX& _projMatrix, const XMMATRIX& _viewMatrix)
{
	float zMin, r;
	XMMATRIX matrix;
	
	zMin = - XMVectorGetZ(_projMatrix.r[4]) / XMVectorGetZ(_projMatrix.r[3]);
	r = _screenDepth / (_screenDepth - zMin);

	XMVectorSetZ(_projMatrix.r[3], r);
	XMVectorSetZ(_projMatrix.r[4], -r * zMin);

	matrix = XMMatrixMultiply(_viewMatrix, _projMatrix);

	//Calculate frustum planes

	//Near plane
	XMVectorSetX(m_vPlanes[0], XMVectorGetW(matrix.r[0]) + XMVectorGetZ(matrix.r[0]));
	XMVectorSetY(m_vPlanes[0], XMVectorGetW(matrix.r[1]) + XMVectorGetZ(matrix.r[1]));
	XMVectorSetZ(m_vPlanes[0], XMVectorGetW(matrix.r[2]) + XMVectorGetZ(matrix.r[2]));
	XMVectorSetW(m_vPlanes[0], XMVectorGetW(matrix.r[3]) + XMVectorGetZ(matrix.r[3]));
	XMPlaneNormalize(m_vPlanes[0]);

	//Far plane
	XMVectorSetX(m_vPlanes[1], XMVectorGetW(matrix.r[0]) - XMVectorGetZ(matrix.r[0]));
	XMVectorSetY(m_vPlanes[1], XMVectorGetW(matrix.r[1]) - XMVectorGetZ(matrix.r[1]));
	XMVectorSetZ(m_vPlanes[1], XMVectorGetW(matrix.r[2]) - XMVectorGetZ(matrix.r[2]));
	XMVectorSetW(m_vPlanes[1], XMVectorGetW(matrix.r[3]) - XMVectorGetZ(matrix.r[3]));
	XMPlaneNormalize(m_vPlanes[1]);

	//Left plane
	XMVectorSetX(m_vPlanes[2], XMVectorGetW(matrix.r[0]) + XMVectorGetX(matrix.r[0]));
	XMVectorSetY(m_vPlanes[2], XMVectorGetW(matrix.r[1]) + XMVectorGetX(matrix.r[1]));
	XMVectorSetZ(m_vPlanes[2], XMVectorGetW(matrix.r[2]) + XMVectorGetX(matrix.r[2]));
	XMVectorSetW(m_vPlanes[2], XMVectorGetW(matrix.r[3]) + XMVectorGetX(matrix.r[3]));
	XMPlaneNormalize(m_vPlanes[2]);

	//Right plane
	XMVectorSetX(m_vPlanes[3], XMVectorGetW(matrix.r[0]) - XMVectorGetX(matrix.r[0]));
	XMVectorSetY(m_vPlanes[3], XMVectorGetW(matrix.r[1]) - XMVectorGetX(matrix.r[1]));
	XMVectorSetZ(m_vPlanes[3], XMVectorGetW(matrix.r[2]) - XMVectorGetX(matrix.r[2]));
	XMVectorSetW(m_vPlanes[3], XMVectorGetW(matrix.r[3]) - XMVectorGetX(matrix.r[3]));
	XMPlaneNormalize(m_vPlanes[3]);

	//Top plane
	XMVectorSetX(m_vPlanes[4], XMVectorGetW(matrix.r[0]) - XMVectorGetY(matrix.r[0]));
	XMVectorSetY(m_vPlanes[4], XMVectorGetW(matrix.r[1]) - XMVectorGetY(matrix.r[1]));
	XMVectorSetZ(m_vPlanes[4], XMVectorGetW(matrix.r[2]) - XMVectorGetY(matrix.r[2]));
	XMVectorSetW(m_vPlanes[4], XMVectorGetW(matrix.r[3]) - XMVectorGetY(matrix.r[3]));
	XMPlaneNormalize(m_vPlanes[4]);

	//Bottom plane
	XMVectorSetX(m_vPlanes[5], XMVectorGetW(matrix.r[0]) + XMVectorGetY(matrix.r[0]));
	XMVectorSetY(m_vPlanes[5], XMVectorGetW(matrix.r[1]) + XMVectorGetY(matrix.r[1]));
	XMVectorSetZ(m_vPlanes[5], XMVectorGetW(matrix.r[2]) + XMVectorGetY(matrix.r[2]));
	XMVectorSetW(m_vPlanes[5], XMVectorGetW(matrix.r[3]) + XMVectorGetY(matrix.r[3]));
	XMPlaneNormalize(m_vPlanes[5]);
}

bool Frustum::CheckCube(float _x, float _y, float _z, float _size)
{
	for (int i = 0; i < 6; ++i)
	{
		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x - _size, _y - _size, _z - _size)))) >= 0)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x + _size, _y - _size, _z - _size)))) >= 0)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x - _size, _y + _size, _z - _size)))) >= 0)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x + _size, _y + _size, _z - _size)))) >= 0)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x - _size, _y - _size, _z + _size)))) >= 0)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x + _size, _y - _size, _z + _size)))) >= 0)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x - _size, _y + _size, _z + _size)))) >= 0)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_vPlanes[i], XMLoadFloat3(&XMFLOAT3(_x + _size, _y + _size, _z + _size)))) >= 0)
		{
			continue;
		}

		return false;
	}

	return true;
}