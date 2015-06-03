#include "GFXEngine.h"
#include <iostream>


int main(int argc, char** argv)
{
	GFXEngine Engine;

	Engine.Initialize("TODO", 800, 600, false, false, 1000.0f, 0.1f);

	Engine.Run();

	return 0;
}