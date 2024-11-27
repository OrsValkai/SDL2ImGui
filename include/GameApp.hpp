// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef GAME_APP_H
#define GAME_APP_H

#include "Application.hpp"

class GameApp : public vo::Application {
public:
	GameApp(const vo::AppSettings& appSettings, int imgFlags);
	void DrawUI();
	void MainLoop();
	~GameApp();

private:
	bool m_bOptionsOpen{false};
	bool m_shouldExit{false};
	bool m_isPaused{true};
};

#endif // GAME_APP_H

