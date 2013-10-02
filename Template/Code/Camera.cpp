#include "Camera.h"

#define TWO_PI 6.283185307179586476925286766559f
#define DEG_TO_RAD 0.01745329251994329576923690768489f

Camera::Camera(void)	: dV( D3DXVECTOR3(0,0,1)), dU(D3DXVECTOR3(0,1,0)), eye(D3DXVECTOR3(0,0,0)), view(D3DXVECTOR3(0,0,1)),
						up(D3DXVECTOR3(0,1,0)), forward(D3DXVECTOR3(0,0,1)), strafeRight(D3DXVECTOR3(1,0,0)), heading(0), pitch(0)
{
	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projectionMatrix);

	for (int i=0;i<4;i++)
	{
		movementToggles[i];
	}
}


Camera::~Camera(void)
{
}

void Camera::setPerspectiveProjection(float _fov, float _aspectRatio, float _zNear, float _zFar)
{
	_fov = _fov * DEG_TO_RAD;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, _fov, _aspectRatio, _zNear, _zFar);
}

void Camera::adjustHeadPitch(float _hRad, float _pRad)
{
	heading += _hRad;
	pitch += _pRad;

	if( heading > TWO_PI )
		heading -= TWO_PI;
	else if( heading < 0)
		heading = TWO_PI + heading;

	if(pitch > TWO_PI)
		pitch -= TWO_PI;
	else if(pitch < 0 )
		pitch = TWO_PI + pitch;
}

void Camera::updateView(float dt)
{
	//rotation
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, heading, pitch, 0);

	D3DXVec3TransformCoord(&view,&dV,&rotationMatrix);
	D3DXVec3TransformCoord(&up,&dU,&rotationMatrix);

	D3DXVec3Normalize(&forward,&view);
	D3DXVec3Cross(&strafeRight,&up,&view);
	D3DXVec3Normalize(&strafeRight,&strafeRight);

	view = eye + view;
	D3DXMatrixLookAtLH(&viewMatrix,&eye,&view,&up);
}

void Camera::setPositionAndView(float x, float y, float z, float hDeg, float pDeg, float dt)
{
	eye.x = x;
	eye.y = y;
	eye.z = z;

	heading = hDeg * DEG_TO_RAD;
	pitch	= pDeg * DEG_TO_RAD;

	updateView(dt);
}

void Camera::update(float _dt)
{
	float t = _dt;
	float mod = 1.5f;
	eye += t * (movementToggles[0] + movementToggles[1]) * mod * forward +
		t * (movementToggles[2] + movementToggles[3]) * mod * strafeRight;

	updateView(_dt);
}

void Camera::setMovementToggle(int i, int v)
{
	movementToggles[i] = v;
}

D3DXMATRIX Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

D3DXMATRIX Camera::getViewMatrix()
{
	return viewMatrix;
}

D3DXMATRIX Camera::getWorldMatrix()
{
	return worldMatrix;
}