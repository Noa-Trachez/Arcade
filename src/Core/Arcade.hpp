/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Arcade
*/

#ifndef Arcade_HPP
#define Arcade_HPP

#include <memory>
#include <string>
#include <chrono>

#include "IDisplayModule.hpp"
#include "DlLoader.hpp"

class ArcadeCore {
    public:
        ArcadeCore();
        ~ArcadeCore() = default;

        void arcadeLoop(int selectedGraphicalLib, int selectedGame);
        void arcadeMenu(std::vector<std::string> &games, std::vector<std::string> &graphics, int selectedGame, int selectedGraphicalLib);

        void launchArcade(int selectedGame, int selectedGraphicalLib);
        void loadGraphicalLib(std::string &lib);
        void loadGame(std::string &game);
        int HandleKeys(const std::vector<Arcade::Key> &keys, int &selectedGraphicalLib, int &selectedGame);
        void LimitFPS(std::chrono::time_point<std::chrono::system_clock> &start);
        void check_libs_and_games();
        void loadBestScore();
private:
        Arcade::IDisplay *_graphicalLib {};
        Arcade::IGame *_gameLib {};

        std::vector<std::string> _libPaths;
        std::vector<std::string> _gamePaths;
        int _bestScore = 0;
        std::string _nameBestScore{};

        std::unique_ptr<DLLoader> _DLLoader {};
        std::string _userName = "";
        bool _isRunning = false;
};


#endif /* !Arcade_HPP */
