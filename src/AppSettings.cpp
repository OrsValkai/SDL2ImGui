#include "AppSettings.hpp"

#include <fstream>

namespace vo {
    
    AppSettings::AppSettings(const char* iniFilePath) {
        std::ifstream file(iniFilePath);

        if (file.is_open()) {
            std::string readStr = "Dummy string to preallocate";

            while (!file.eof()) {
                std::getline(file, readStr);

                if ('[' == readStr[0])
                    continue;

                if (std::string::npos != readStr.find("width")) {
                    wWidth = GetIntValue(readStr);
                }
                else if (std::string::npos != readStr.find("height")) {
                    wHeight = GetIntValue(readStr);
                }
                else if (std::string::npos != readStr.find("fullscreen")) {
                    isFullScreen = 0 != GetIntValue(readStr);
                }
                else if (std::string::npos != readStr.find("borderless")) {
                    isBorderless = 0 != GetIntValue(readStr);
                }
            }
        }
    }

    Uint32 AppSettings::ToWindowFlags() const {
        Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI;

        if (isFullScreen)
            flags |= SDL_WINDOW_FULLSCREEN;

        if (isBorderless)
            flags |= SDL_WINDOW_BORDERLESS;

        return flags;
    }

    int AppSettings::GetIntValue(const std::string& str) const {
        for (size_t i = str.size() - 1; i > 0; --i) {
            if (!isdigit(str[i])) {
                return atoi(str.substr(i + 1, str.size() - i).c_str());
            }
        }

        return 0;
    }

    double AppSettings::GetDoubleValue(const std::string& str) const {
        for (size_t i = str.size() - 1; i > 0; --i) {
            if (!isdigit(str[i]) && '.' != str[i]) {
                return atof(str.substr(i + 1, str.size() - i).c_str());
            }
        }

        return 0.f;
    }

};
