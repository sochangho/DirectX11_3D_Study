#include "pch.h"
#include "GeometryHelper.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "05. TextureDemo.h"
#include "CameraScript.h"
#include "Texture.h"

void TextureDemo::Init()
{
	_shader = make_shared<Shader>(L"04. Texture.fx");

	_geometry = make_shared<Geometry<VertexTextureData>>();

	 //GeometryHelper::CreateCube(_geometry);
	 //GeometryHelper::CreateSphere(_geometry);
	GeometryHelper::CreateGrid(_geometry, 256, 256);
	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create( _geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	//Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	
	_texture = RESOURCES->Load<Texture>(L"Skeleton", L"..\\Resources\\Textures\\Skeleton.jpg");
}

void TextureDemo::Update()
{
	_camera->Update();

	//_world = Matrix::CreateTranslation(_translation);

}

void TextureDemo::Render()
{

	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	//_buffer->GetCount()
	_shader->DrawIndexed(0, 0,_indexBuffer->GetCount(),0,0);
}
