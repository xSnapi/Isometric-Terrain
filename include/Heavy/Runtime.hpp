#pragma once

/*
	Main class used by Heavy to run application

	~How to use~
	1. Create class inheriting runtime
	2. Create m_window in it's constructor
	3. Create functions FixedUpdate, Update, Render
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Window/Event.hpp>

#include <box2d/b2_world.h>

#include <mutex>
#include <thread>

#include "Heavy Times.hpp"
#include "Asset Loader.hpp"
#include "Heavy Renderer.hpp"
#include "Light Renderer.hpp"

#define USE_MULTITHREAD 1

namespace hv {
	class Runtime {
	public:
		Runtime();
		virtual ~Runtime();

		void Run();
		void Close();

		static Runtime* GetInstance();

	protected:
		virtual void FixedUpdate()	= 0;
		virtual void Update()	    = 0;
		virtual void Render()	    = 0;

		sf::RenderWindow m_window;
		sf::Event m_event;

		Renderer  m_renderer;

		double m_physicsStep = 0.01;
		double m_pet		 = 0.0; // physics elapsed time

		void SetFrameLimit(uint32_t limit);

	private:
		sf::Clock m_dtClock;
		sf::Clock m_fdtClock;

		uint32_t m_frameLimit = 0;

		LightRenderer m_lightRenderer;

		bool m_focus = true;

		static Runtime* s_instance;

		#if USE_MULTITHREAD
			std::mutex	 m_mutex;
			std::thread* m_rendererThread = nullptr;
			bool		 m_isRunning	  = true;
		#endif

		void FrameFixedUpdate();
		void FrameUpdate();
		void RendererDraw();
		void HandleEvents();
		void InitRenderer();
		void Delay();
		void GLInit(); // Initializes openGL states
	};
}