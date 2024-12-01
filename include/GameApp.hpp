// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef GAME_APP_H
#define GAME_APP_H

#include "Application.hpp"

#include <array>

class GameApp : public vo::Application {
public:
	GameApp(const vo::AppSettings& appSettings, int imgFlags);
	void DrawResultsUI();
	void DrawOptionUI();
	void DrawUI();
	void MainLoop();
	~GameApp();

private:
	std::array<const char*, 4> m_optionTabs{ {"Controls", "Settings", "Upgrades", ""} };
	int m_nrPlayers{2};
	int m_nrMatches{1};
	bool m_bOptionsOpen{false};
	bool m_bResultsOpen{false};
	bool m_shouldExit{false};
	bool m_isPaused{true};
	bool m_letAiPlay{false};
};

#endif // GAME_APP_H

