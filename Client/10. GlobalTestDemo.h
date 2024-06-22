#pragma once
#include "IExecute.h"
#include "Geometry.h"
#include "CameraScript.h"

class GameObject;

class GlobalTestDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;


	shared_ptr<Shader> _shader;
	//Object
	shared_ptr<GameObject> _obj;
	//Camera
	shared_ptr<GameObject> _camera;


};

