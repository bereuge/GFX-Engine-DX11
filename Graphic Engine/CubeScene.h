#pragma once

#include "AbstractScene.h"

class CubeScene : public AbstractScene
{
public:
	CubeScene();
	~CubeScene();

	virtual void SetupScene() override;
	virtual void CleanResources() override;

	virtual void Update(float deltaTime);

	virtual void Render();

private:
	Object objArray[3500];
	float x;
	float offset;
	int sign = 1;
};