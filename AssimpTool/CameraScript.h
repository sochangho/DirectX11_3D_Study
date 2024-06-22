#pragma once
#include "Camera.h"
#include "MonoBehavior.h"


class CameraScript :public MonoBehavior
{
public:


	

	virtual void Awake() override;
	virtual void Update() override;

	float _speed = 10.f;

	
};

