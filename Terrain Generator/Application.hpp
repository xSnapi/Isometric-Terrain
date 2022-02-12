#pragma once

#include "ispch.h"

#include "world/Map.hpp"

class Application : public hv::Runtime {
public:
	Application();
	~Application();

private:
	Map* m_map = nullptr;

	sf::Cursor m_cursors[2];

	void UpdateCamera();
	void ResetCameraView();

	void UpdateCursor();
	void InitCursor();

	void InitAssets();

	void Update();
	void FixedUpdate();
	void Render();

	void InitWindow();
};