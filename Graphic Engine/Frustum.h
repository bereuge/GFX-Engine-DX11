#include <d3d11.h>
#include <DirectXMath.h>

class Frustum
{
public:
	Frustum();
	~Frustum();

	void CreateFrustum(float _screenDepth, DirectX::XMMATRIX& _projMatrix, const DirectX::XMMATRIX& _viewMatrix);

	bool CheckCube(float _x, float _y, float _z, float _size);

private:
	DirectX::XMVECTOR m_vPlanes[6];
};