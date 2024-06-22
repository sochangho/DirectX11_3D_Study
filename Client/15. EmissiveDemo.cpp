#include "pch.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h";
#include "GameObject.h";
#include "Texture.h";
#include "Mesh.h"
#include "Transform.h"
#include "RenderManager.h"
#include "15. EmissiveDemo.h";

#define RENDER      GET_SINGLE(RenderManager)

void EmissiveDemo::Init()
{

	RESOURCES->Init();

	_shader = make_shared<Shader>(L"12. Lighting_Emissive.fx");
	
	//Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->GetTransform()->SetPosition(Vec3{ 0.f,0.f,-10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	
    //Object;
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{		
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);	
	}
	{
		auto  _texture = RESOURCES->Load<Texture>(L"Grass",
			L"..\\Resources\\Textures\\Terrain\\grass.jpg");
		_obj->GetMeshRenderer()->SetTexture(_texture);
	}

	//
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3(0.5f,0.f,2.f));
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto  _texture = RESOURCES->Load<Texture>(L"Skeleton", 
			L"..\\Resources\\Textures\\Skeleton.jpg");
		_obj2->GetMeshRenderer()->SetTexture(_texture);
	}


	RENDER->Init(_shader);
}

void EmissiveDemo::Update()
{
	_camera->Update();

	RENDER->Update();
	


	{
		Vec4 materialEimissive( 1.f,0.f,0.f,1.f );
		_shader->GetVector("MaterialEmissive")
			->SetFloatVector((float*)&materialEimissive);
		_obj->Update();
	}
	{
		Vec4 materialEimissive(1.f,1.f,1.f,1.f);
		_shader->GetVector("MaterialEmissive")
			->SetFloatVector((float*)&materialEimissive);
		_obj2->Update();
	}
}

void EmissiveDemo::Render()
{

}
