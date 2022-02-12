#include "ispch.h"
#include "Application.hpp"

#include <SFML/Graphics.hpp>

Application::Application() 
{
	InitWindow();
	InitAssets();

	InitCursor();

	m_map = new Map(m_renderer);
}

Application::~Application() {

}

void Application::UpdateCamera() {
	float movementSpeed = hv::Input::Keyboard::KeyCheck(sf::Keyboard::LShift, true) ? 850.0f : 450.0f;

	sf::Vector2f velocity;

	if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::W, true))
		velocity.y = -1.0f;
	if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::S, true))
		velocity.y = 1.0f;
	if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::A, true))
		velocity.x = -1.0f;
	if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::D, true))
		velocity.x = 1.0f;

	hv::Camera::Get().Move(velocity * movementSpeed * hv::dt);

	static sf::Vector2f mousePoint;
	static bool blockMouse = false;

	if (hv::Input::Mouse::KeyCheck(sf::Mouse::Left, true) && !blockMouse) {
		mousePoint = hv::Input::Mouse::GetRelativeCoords();

		blockMouse = true;
	}

	if (hv::Input::Mouse::KeyCheck(sf::Mouse::Left, true)) {
		sf::Vector2f diff(mousePoint - hv::Input::Mouse::GetRelativeCoords());

		sf::Vector2f offset(hv::Camera::Get().GetCenter() + diff);


		hv::Camera::Get().SetPosition(offset);
	}
	else
		blockMouse = false;

	if (hv::EventDispatcher::CheckFor(sf::Event::MouseWheelScrolled)) {
		float delta = hv::EventDispatcher::GetEvent(sf::Event::MouseWheelScrolled).mouseWheelScroll.delta;

		hv::Camera::Get().Zoom(delta > 0.0f ? 0.9f : 1.1f);
	}

	ResetCameraView();
}

void Application::ResetCameraView() {
	static bool reset = false;

	if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::Space))
		reset = true;

	if (!reset)
		return;

	float zoom = hv::Camera::Get().GetZoom();

	if (zoom > 1.0f) {
		hv::Camera::Get().Zoom(0.9f);

		zoom = hv::Camera::Get().GetZoom();

		if (zoom < 1.0f) {
			hv::Camera::Get().Zoom(1.0f / zoom);
			reset = false;
		}
	}
	else {
		hv::Camera::Get().Zoom(1.1f);

		zoom = hv::Camera::Get().GetZoom();

		if (zoom > 1.0f) {
			hv::Camera::Get().Zoom(1.0f / zoom);
			reset = false;
		}
	}
}

void Application::UpdateCursor() {
	m_window.setMouseCursor(m_cursors[hv::Input::Mouse::KeyCheck(sf::Mouse::Left, true)]);
}

void Application::InitCursor() {
	auto& img0 = hv::TextureLibrary::Get().Res("cursor").copyToImage();
	auto& img1 = hv::TextureLibrary::Get().Res("cursor1").copyToImage();

	m_cursors[0].loadFromPixels(img0.getPixelsPtr(), sf::Vector2u(23, 28), sf::Vector2u(12, 14));
	m_cursors[1].loadFromPixels(img1.getPixelsPtr(), sf::Vector2u(23, 28), sf::Vector2u(12, 14));
}

void Application::InitAssets() {
	{
		hv::AssetLoader::Get().AddResource("block_atlas", "res/block_atlas.png", hv::AssetType::Texture);
		hv::AssetLoader::Get().AddResource("cursor", "res/cursor.png", hv::AssetType::Texture);
		hv::AssetLoader::Get().AddResource("cursor1", "res/cursor1.png", hv::AssetType::Texture);
	}

	hv::AssetLoader::Get().Sync();
}

void Application::Update() {
	m_map->Update();
	UpdateCamera();
	UpdateCursor();
}

void Application::FixedUpdate() {

}

void Application::Render() {
	m_map->Render();
}

void Application::InitWindow() {
	sf::VideoMode mode;

	mode.width  = WINDOW_WIDTH;
	mode.height = WINDOW_HEIGHT;

	sf::ContextSettings settings;

	m_window.create(mode, "Isometric Terrain Generator", sf::Style::Close, settings);
	SetFrameLimit(144);

}
