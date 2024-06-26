#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "01. TriangleDemo.h"
#include "02. QuadDemo.h"
#include "03. ConstBuffer.h"
#include "04. CameraDemo.h"
#include "05. TextureDemo.h"
#include "06. SamplerDemo.h"
#include "07. HeightMapDemo.h"
#include "08. NormalDemo.h"
#include "09. MeshDemo.h"
#include "10. GlobalTestDemo.h"
#include "11. DepthStencilDemo.h"
#include "12. AmbientDemo.h"
#include "13. DiffuseDemo.h"
#include "14. SpecularDemo.h"
#include "15. EmissiveDemo.h"
#include "16. LightingDemo.h" 
#include "17. MaterialDemo.h"
#include "18. NormalMappingDemo.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.f, 0.f, 0.f, 0.f);
	desc.app = make_shared<NormalMappingDemo>();

	GAME->Run(desc);

	return 0;
}