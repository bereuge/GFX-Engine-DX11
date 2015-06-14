#include "GFXEngine.h"
#include <iostream>


int main(int argc, char** argv)
{
	GFXEngine Engine;
	Scene scene;

	Engine.Initialize("TODO", 800, 600, false, false, 1000.0f, 0.1f);
	Engine.GetSceneManager().AddSceneToList(&scene, "lol");
	Engine.GetSceneManager().Start();
	//Engine.GetSceneManager().ChangeScene("lol");

	Engine.Run();

	return 0;
}