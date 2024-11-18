#ifndef VO_APPLICATION_H
#define VO_APPLICATION_H

#include "AppSettings.hpp"

#include <SDL.h>

namespace vo {

	class Application
	{
	public:
		Application(const vo::AppSettings& appSettings, int imgFlags);
		Application(const Application& other) = delete;
		Application& operator=(const Application& other) = delete;

		SDL_Window* GetWindow() const;
		SDL_Renderer* GetRenderer() const;
		unsigned short GetWindowWidth() const;
		unsigned short GetWindowHeight() const;

		void SetWindowName(const char* pName);
		~Application();

	private:
		SDL_Window* m_pWindow = nullptr;
		SDL_Renderer* m_pRenderer = nullptr;
		unsigned short m_wWidth = 0;
		unsigned short m_wHeight = 0;
	};

	// Implementation
	inline SDL_Window* Application::GetWindow() const { return m_pWindow; };
	inline SDL_Renderer* Application::GetRenderer() const { return m_pRenderer; };
	inline unsigned short Application::GetWindowWidth() const { return m_wWidth; };
	inline unsigned short Application::GetWindowHeight() const { return m_wHeight; };
}

#endif // VO_APPLICATION_H