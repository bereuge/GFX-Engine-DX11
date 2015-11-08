#include "GFXEngine.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "CubeScene.h"

int main(int argc, char** argv)
{
	GFXEngine Engine;
	CubeScene scene;

	srand(time(NULL));
	
	Engine.Initialize("GFX Engine", 800, 600, false, false, 1000.0f, 0.1f);
	Engine.GetSceneManager().AddSceneToList(&scene, "CubeScene");
	Engine.GetSceneManager().Start();

	Engine.Run();

	return 0;
}