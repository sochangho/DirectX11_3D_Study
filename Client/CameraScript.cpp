#include "pch.h"
#include "CameraScript.h"

#include "Camera.h";
#include "Transform.h";
#include "GameObject.h"

void CameraScript::Awake()
{
}

void CameraScript::Update()
{
	float dt = TIME->GetDeltaTime();

	Vec3  pos = GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::A)) {

		pos -= GetTransform()->GetRight() * dt *_speed;
		GetTransform()->SetPosition(pos);
	}
	else if (INPUT->GetButton(KEY_TYPE::D)) {

		pos += GetTransform()->GetRight() * dt * _speed;
		GetTransform()->SetPosition(pos);
	}
	else if (INPUT->GetButton(KEY_TYPE::S)) {

		pos -= GetTransform()->GetLook() * dt * _speed;
		GetTransform()->SetPosition(pos);
	}
	else if (INPUT->GetButton(KEY_TYPE::W)) {

		pos += GetTransform()->GetLook() * dt * _speed;
		GetTransform()->SetPosition(pos);
	}

	if (INPUT->GetButton(KEY_TYPE::E)) {

		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.x -= dt * 0.5f;
	}

	if (INPUT->GetButton(KEY_TYPE::Q)) {

		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.x += dt * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::E)) {

		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.x -= dt * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}


	if (INPUT->GetButton(KEY_TYPE::Z)) {

		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.y += dt * 0.5f;
		GetTransform()-> SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::C)) {

		Vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.y -= dt * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	

	
}
