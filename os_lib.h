//
// Created by verifiedfemboy on 06.04.24.
//

#ifndef ASTOLFO_DOWNLOADER_OS_LIB_H
#define ASTOLFO_DOWNLOADER_OS_LIB_H

#endif //ASTOLFO_DOWNLOADER_OS_LIB_H

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#elif defined(__unix__) || defined(__APPLE__)
    #define CLEAR_COMMAND "clear"
#else
    #error "Nieobsługiwany system operacyjny"
#endif

#include <iostream>
#include <cstdlib>
#include <pwd.h>

void clearScreen() {
    system(CLEAR_COMMAND);
}

std::string getLinuxHome() {
    const char *homeDir = getenv("HOME");
    if (homeDir != nullptr)
        return std::string(homeDir);
    else {
        return "";
    }
}

std::string getWinHome() {
    //TODO: HUH!? HOW CAN I MAKE THE FUCKING CROSSPLATFORM!? FUCK WINDOWS!
}

std::string getHomeDirectory() {
    return getLinuxHome();
}
