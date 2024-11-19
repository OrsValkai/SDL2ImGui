// Copyright(c) 2024 Valkai-Németh Béla-Örs
#ifndef VO_APP_SETTINGS_H
#define VO_APP_SETTINGS_H

#include <SDL.h>

#include <string>

namespace vo {

    class AppSettings
    {
    public:
        int m_wWidth = 800;
        int m_wHeight = 600;
        bool m_isFullScreen = false;
        bool m_isBorderless = false;

        explicit AppSettings(const char* iniFilePath);
        Uint32 ToWindowFlags() const;

    private:
        int GetIntValue(const std::string& str) const;
        double GetDoubleValue(const std::string& str) const;
    };

}

#endif // VO_APP_SETTINGS_H


