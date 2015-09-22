#include "GFXEngine.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "CubeScene.h"

int main(int argc, char** argv)
{
	GFXEngine Engine;
	//AbstractScene* scene = new CubeScene();
	CubeScene scene;

	srand(time(NULL));
	
	Engine.Initialize("GFX Engine", 800, 600, false, false, 1000.0f, 0.1f);
	Engine.GetSceneManager().AddSceneToList(&scene, "lol");
	Engine.GetSceneManager().Start();
	//Engine.GetSceneManager().ChangeScene("lol");

	Engine.Run();

	return 0;
}