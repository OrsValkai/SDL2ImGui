#ifndef VO_WINDOW_H
#define VO_WINDOW_H


#include <SDL.h>

class Window
{
	SDL_Renderer* m_pRenderer = nullptr;
	SDL_Window* m_pWindow = nullptr;

public:
	Window() = default;
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;

	SDL_Renderer* GetRenderer();
	bool Init(int width, int height, Uint32 flags, int imgFlags);
	~Window();
};

#endif // VO_WINDOW