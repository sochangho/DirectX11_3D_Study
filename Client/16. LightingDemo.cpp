#include "pch.h"
#include "Camera.h"
#include "MeshRenderer.h";
#include "GameObject.h";
#include "Texture.h";
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"
#include "RenderManager.h"
#include "CameraScript.h"

#include "16. LightingDemo.h";

#define RENDER      GET_SINGLE(RenderManager)

void LightingDemo::Init()
{

	RESOURCES->Init();

	_shader = make_shared<Shader>(L"13. Lighting.fx");
	
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
			L"..\\Resources\\Textures\\veigar.jpg");
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

void LightingDemo::Update()
{
	_camera->Update();

	RENDER->Update();
	
	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		lightDesc.padding0 = 0;
		RENDER->PushLightData(lightDesc);
		
	}
	//{
	//	MaterialDesc desc;
	//	desc.ambient = Vec4(1.f, 1.f, 1.f, 1.f);
	//	desc.diffuse = Vec4(0.7f);
	//	desc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
	//	//desc.emissive = Color(0.3f, 0.f, 0.f, 0.5f);

	//	RENDER->PushMaterialData(desc);
	//	_obj->Update();
	//} 
	//{
	//	MaterialDesc desc;
	//	desc.ambient = Vec4(0.5f);
	//	desc.diffuse = Vec4(1.f);
	//	desc.specular = Color(0.5f, 0.5f, 0.5f, 1.f);
	//	desc.emissive = Color(0.f, 1.f, 1.f, 1.f);

	//	RENDER->PushMaterialData(desc);
	//	_obj2->Update();

	//}

	
}

void LightingDemo::Render()
{

}
