#ifndef VO_APPLICATION_H
#define VO_APPLICATION_H

#include <SDL.h>

namespace vo {

	class Application
	{
		SDL_Window* m_pWindow = nullptr;
		SDL_Renderer* m_pRenderer = nullptr;
		unsigned short m_wWidth = 0;
		unsigned short m_wHeight = 0;

	public:
		Application() = default;
		Application(const Application& other) = delete;
		Application& operator=(const Application& other) = delete;

		SDL_Renderer* GetRenderer() const;
		unsigned short GetWindowWidth() const;
		unsigned short GetWindowHeight() const;

		bool Init(int windowWidth, int windowHeight, Uint32 flags, int imgFlags);
		void SetWindowName(const char* pName);
		~Application();
	};

	// Implementations
	inline SDL_Renderer* Application::GetRenderer() const { return m_pRenderer; };
	inline unsigned short Application::GetWindowWidth() const { return m_wWidth; };
	inline unsigned short Application::GetWindowHeight() const { return m_wHeight; };
}

#endif // VO_APPLICATION_H