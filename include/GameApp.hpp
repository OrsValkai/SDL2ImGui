// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef GAME_APP_H
#define GAME_APP_H

#include "Application.hpp"

class GameApp : public vo::Application {
public:
	GameApp(const vo::AppSettings& appSettings, int imgFlags);
	void MainLoop() const;
	~GameApp();
};

#endif // GAME_APP_H

