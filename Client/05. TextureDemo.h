#pragma once
#include "IExecute.h"
#include "Geometry.h"
#include "CameraScript.h"

class GameObject;

class TextureDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	//Object
	shared_ptr<Shader> _shader;
	
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	Vec3 _translation = Vec3(0, 0, 0);
	Matrix _world = Matrix::Identity;

	Vec3 cameraPos;

	//Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<Texture> _texture;
};

