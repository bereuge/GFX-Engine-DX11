#pragma once

#include "AbstractScene.h"

class CubeScene : public AbstractScene
{
public:
	CubeScene();
	~CubeScene();

	virtual void SetupScene(DXRenderer* _renderer) override;
	virtual void CleanResources() override;

	virtual void Update(float deltaTime) override;

	virtual void PreRender() override;
	virtual void Render(DXRenderer* _renderer) override;
	virtual void PostRender() override;

private:

	static const int maxCubes = 2000;

	GFX::Camera m_oMainCamera;
	Object objArray[maxCubes];
	float x;
	float offset;
	int sign = 1;

};