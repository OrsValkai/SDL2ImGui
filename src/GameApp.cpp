// Copyright(c) 2024 Valkai-Németh Béla-Örs

#include "GameApp.hpp"

#include "Player.hpp"
#include "PlayGround.hpp"
#include "TimerHR.hpp"
#include "KeyboardControl.hpp"
#include "AIControl.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

GameApp::GameApp(const vo::AppSettings& appSettings, int imgFlags)
: Application(appSettings, imgFlags) {
    auto pRenderer = GetRenderer();
    if (!pRenderer)
        return;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoKeyboard;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(GetWindow(), pRenderer);
    ImGui_ImplSDLRenderer2_Init(pRenderer);

    // Load font
    io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 44);
}

void GameApp::DrawUI() {
    ImVec2 buttonSize(200.f, 50.f);
    int wHeight = GetWindowHeight();
    int wWidth = GetWindowWidth();

    //ImGui::ShowDemoWindow();

    // FPS counter
    ImGui::SetNextWindowPos(ImVec2(0, 0), 1);
    ImGui::SetNextWindowCollapsed(true, 2);

    if (!ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove) || ImGui::GetCurrentWindow()->BeginCount > 1)
    {
        ImGui::End();
    }
    else {
        auto fFPS = ImGui::GetIO().Framerate;
        ImGui::Text("%.1f FPS (%.3f ms)", fFPS, 1000.0f / fFPS);

        ImGui::End();
    }

    // Main menu
    if (m_isPaused) {
        ImGui::SetNextWindowPos(ImVec2((float)(wWidth >> 1) - buttonSize.x * 0.5f, (float)(wHeight >> 1) - buttonSize.y * 3.f/2.f), 1);
        if (!ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove) || ImGui::GetCurrentWindow()->BeginCount > 1)
        {
            ImGui::End();
        }
        else {
            if (ImGui::Button("Start", buttonSize)) {
                m_isPaused = false;
            }

            if (ImGui::Button("Options", buttonSize)) {
                m_bOptionsOpen = true;
            }

            if (ImGui::Button("Exit", buttonSize)) {
                m_shouldExit = true;
            }

            ImGui::End();
        }
    }

    // Options menu
    if (m_bOptionsOpen) {
        ImVec2 owSize(400.f, 300.f);

        ImGui::SetNextWindowSize(owSize, ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2((float)(wWidth >> 1) - owSize.x * 0.5f, (float)(wHeight >> 1) - owSize.y * 0.5f));
        if (!ImGui::Begin("Options Menu", &m_bOptionsOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse) || ImGui::GetCurrentWindow()->BeginCount > 1)
        {
            ImGui::End();
        }
        else {
            ImGui::TextWrapped("Arrow keys to move, ctrl to lay bomb!");

            ImGui::End();
        }
    }

    ImGui::Render();
}

void GameApp::MainLoop() {
    auto pRenderer = GetRenderer();
    auto pPlayGround = std::make_unique<PlayGround>(GetWindowWidth(), GetWindowHeight(), std::make_shared<vo::TextureAtlasU>(pRenderer, "Atlas64.png", 64, 64, 64));
    auto upBG = vo::SDL_MakeTexturePtr(pRenderer, "BG.jpg");
    const auto& posOffset = pPlayGround->GetPosOffset();
    SDL_Rect bgDst{ 0, 0, GetWindowWidth(), GetWindowHeight() };
    SDL_Rect bgSrc{posOffset.x, posOffset.y+8, bgDst.w, bgDst.h};
    vo::TimerHR timerHR;
    std::vector<Player> players;

    players.reserve(4);
    timerHR.Start();
    players.emplace_back(std::make_shared<vo::TextureAtlasU>(pRenderer, "Player64.png", 64, 102, 160), *pPlayGround);
    std::cout << "Make texture took: " << timerHR.MarkUS() << "us\n";
        
    players.push_back(players.back());
    players.push_back(players.back());

    players.at(0).SetControl(std::make_shared<KeyboardControl>(*pPlayGround, static_cast<unsigned short>(0)));
    players.at(1).SetControl(std::make_shared<KeyboardControl>(*pPlayGround, pPlayGround->GetNrOfTiles() - 1));
    players.at(2).SetControl(std::make_shared<AIControl>(*pPlayGround, pPlayGround->GetTileId(pPlayGround->GetWidth() - 1, 0)));

    players[1].SetTintColor(245, 210, 160);
    players[2].SetTintColor(255, 180, 180);

    if (auto pCtrl = dynamic_cast<KeyboardControl*>(players[1].GetCtrl());  nullptr != pCtrl) {
        pCtrl->RemapKey(0, SDLK_a);
        pCtrl->RemapKey(1, SDLK_d);
        pCtrl->RemapKey(2, SDLK_w);
        pCtrl->RemapKey(3, SDLK_s);
        pCtrl->RemapKey(4, SDLK_TAB);
    }

    timerHR.Start(); // start to clear time spent before
    timerHR.Mark();
    while (false == m_shouldExit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) {
                m_shouldExit = true;
            } else {
                ImGui_ImplSDL2_ProcessEvent(&event);

                for (auto& player : players)
                    player.GetCtrl()->OnEvent(&event);
            }
        }

        float deltaTime = timerHR.MS(); // read time spent in loop and restart
        float deltaTimePaused = m_isPaused ? 0.f : deltaTime;
        timerHR.Start();

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        int nrPlayersAlive = 0;
        for (auto& player : players) {
            player.Update(deltaTimePaused);

            if (player.IsAlive())
                nrPlayersAlive++;
        }

        if (nrPlayersAlive <= 1) {
            pPlayGround->Reset();

            for (auto& player : players)
                player.Reset();

            m_isPaused = true;
            continue;
        }

        SDL_RenderCopy(pRenderer, upBG.get(), &bgSrc, &bgDst);

        pPlayGround->Draw(deltaTime);

        DrawUI();
        
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), pRenderer);

        SDL_RenderPresent(pRenderer);
        timerHR.Mark();
    }
}

GameApp::~GameApp() {
    if (nullptr != ImGui::GetCurrentContext()) {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
}
