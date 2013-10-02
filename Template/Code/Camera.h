#pragma once

#include <D3DX10.h>

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void setPositionAndView(float x, float y, float z, float hDeg, float pDeg, float dt);
	void adjustHeadPitch( float hRad, float pRad );
	void setMovementToggle( int i, int v);

	void update(float dt);
	void setPerspectiveProjection(float _fov, float _aspectRatio, float _zNear, float _zFar);

	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();
	D3DXMATRIX getWorldMatrix();

public:
	float heading, pitch;
	//view vectors
	const D3DXVECTOR3 dV, dU;
	D3DXVECTOR3 up, eye, view;
	//movement
	D3DXVECTOR3 forward, strafeRight;
	int movementToggles[4];//fwrd, bck, strfLft, strfRght
	//matrices
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, rotationMatrix;

	void updateView(float dt);

};

