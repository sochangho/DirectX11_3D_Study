#include "pch.h"
#include "Camera.h"
#include "MeshRenderer.h";
#include "GameObject.h";
#include "Texture.h";
#include "Mesh.h"
#include "Transform.h"
#include "RenderManager.h"
#include "CameraScript.h"
#include "Material.h"
#include "18. NormalMappingDemo.h";

#define RENDER      GET_SINGLE(RenderManager)

void NormalMappingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"14. NormalMapping.fx");
	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			auto texture = RESOURCES->Load<Texture>(L"Leather", L"..\\Resources\\Textures\\Leather.jpg");
			material->SetDiffuseMap(texture);
		}
		{
			auto texture = RESOURCES->Load<Texture>(L"Leather_Normal", L"..\\Resources\\Textures\\Leather_Normal.jpg");
			material->SetNormalMap(texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		desc.emissive = Vec4(1.f);
		RESOURCES->Add(L"Leather", material);
	}

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto material = RESOURCES->Get<Material>(L"Leather");
		_obj->GetMeshRenderer()->SetMaterial(material);
	}

	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{ 0.5f, 0.f, 2.f });
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto material = RESOURCES->Get<Material>(L"Leather")->Clone();
	 	MaterialDesc desc =  material->GetMaterialDesc();
		
		_obj2->GetMeshRenderer()->SetMaterial(material);
	}

	RENDER->Init(_shader);
}

void NormalMappingDemo::Update()
{
	_camera->Update();

	RENDER->Update();
	
	{

		Vec3  dirCamera = _camera->GetTransform()->GetLook();

		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		lightDesc.emissive = Vec4(1.f, 1.f, 0.f, 1.f);
		RENDER->PushLightData(lightDesc);
		
	}
    
	_obj->Update();
	_obj2->Update();
	
}

void NormalMappingDemo::Render()
{

}
