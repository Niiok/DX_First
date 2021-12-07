#include "Framework.h"
#include "Export.h"
#include "Assimp/Loader.h"
#include "Viewer/FreeCam.h"
#include "Environment/Terrain.h"


void Export::Initialize()
{
	Loader* loader = new Loader();
	loader->ReadFile(L"Tank/tank.fbx");

	int breakpoint = 999;

	SafeDelete(loader);

}