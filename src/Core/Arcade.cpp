/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include <unistd.h>
#include <sstream>

ArcadeCore::ArcadeCore() : _DLLoader(std::make_unique<DLLoader>())
{
}

void ArcadeCore::check_libs_and_games()
{
    for (auto &lib : _libPaths) {
        if (access(lib.c_str(), F_OK) == -1) {
            _libPaths.erase(std::remove(_libPaths.begin(), _libPaths.end(), lib), _libPaths.end());
            if (_libPaths.empty())
                throw std::runtime_error("No graphical library found");
        }
    }
    for (auto &game : _gamePaths) {
        if (access(game.c_str(), F_OK) == -1) {
            _gamePaths.erase(std::remove(_gamePaths.begin(), _gamePaths.end(), game), _gamePaths.end());
            if (_gamePaths.empty())
                throw std::runtime_error("No graphical library found");
        }
    }
}

int ArcadeCore::HandleKeys(const std::vector<Arcade::Key> &keys, int &selectedGraphicalLib, int &selectedGame)
{
    check_libs_and_games();
    if (selectedGame >= _gamePaths.size())
        selectedGame = 0;
    if (selectedGraphicalLib >= _libPaths.size())
        selectedGraphicalLib = 0;
    for (auto &key : keys) {
        if (!_isRunning) {
            if (key >= Arcade::Key::A && key <= Arcade::Key::Z && _userName.size() <= 15)
                _userName += static_cast<char>(key + 65);
            if (key == Arcade::Key::Backspace && !_userName.empty())
                _userName = _userName.substr(0, _userName.size() - 1);
        }
        if (key == Arcade::Key::Escape) {
            _isRunning = false;
            _DLLoader->closeLibrary(_graphicalLib);
            _DLLoader->closeLibrary(_gameLib);
            throw std::runtime_error("Exit");
        }
        if (key == Arcade::Key::Enter) {
            _isRunning = true;
            launchArcade(selectedGame, selectedGraphicalLib);
        }
        if (key == Arcade::Key::Left)
            selectedGraphicalLib = (selectedGraphicalLib - 1) < 0 ? _libPaths.size() - 1 : selectedGraphicalLib - 1;
        if (key == Arcade::Key::Right)
            selectedGraphicalLib = (selectedGraphicalLib + 1) % _libPaths.size();
        if (key == Arcade::Key::Up)
            selectedGame = (selectedGame - 1)  < 0 ? _gamePaths.size() - 1 : selectedGame - 1;
        if (key == Arcade::Key::Down)
            selectedGame = (selectedGame + 1) % _gamePaths.size();
        if (key == Arcade::Key::Left || key == Arcade::Key::Right) {
            loadGraphicalLib(_libPaths[selectedGraphicalLib]);
        }
        if (key == Arcade::Key::Up || key == Arcade::Key::Down) {
            loadGame(_gamePaths[selectedGame]);
            loadBestScore();
        }
    }
    return 0;
}

void ArcadeCore::loadBestScore()
{
    std::ifstream file{"./scores/" + _gameLib->getGameData().getGameName() + ".score"};
    std::string line;

    if (file.is_open()) {
        if (getline(file, line)) {
            std::istringstream iss(line);
            iss >> _nameBestScore >> _bestScore;
        }
        file.close();
    } else {
        _bestScore = 0;
        _nameBestScore = "No score";
    }
}

void ArcadeCore::arcadeMenu(std::vector<std::string> &games, std::vector<std::string> &graphics, int selectedGame, int selectedGraphicalLib)
{
    // -- Get all the libs and games
    Arcade::ControlMap controls;
    controls["Left"] = "Previous graphical lib";
    controls["Right"] = "Next graphical lib";
    controls["Up"] = "Previous game";
    controls["Down"] = "Next game";
    controls["Enter"] = "Launch game";
    controls["Escape"] = "Exit";
    _libPaths = graphics;
    _gamePaths = games;
    _userName = "WINXS";

    loadGraphicalLib(_libPaths[selectedGraphicalLib]);
    loadGame(_gamePaths[selectedGame]);
    loadBestScore();

    while (true) {
        _graphicalLib->renderMenu(_gamePaths, _libPaths, selectedGame, selectedGraphicalLib, controls, _userName,
            _nameBestScore, _bestScore);
        std::vector<Arcade::Key> keys = _graphicalLib->getPressedKeys();
        HandleKeys(keys, selectedGraphicalLib, selectedGame);
    }
}

void ArcadeCore::launchArcade(int selectedGame, int selectedGraphicalLib)
{
    //TODO: repair this
    loadGame(_gamePaths[selectedGame]);
    arcadeLoop(selectedGame, selectedGraphicalLib);
    _isRunning = false;
    loadBestScore();
}

void ArcadeCore::loadGraphicalLib(std::string &lib)
{
    if (_graphicalLib) {
        _DLLoader->closeLibrary(_graphicalLib);
        _graphicalLib = nullptr;
    }
    _graphicalLib = _DLLoader->loadGraphicalLibrary(lib);
    if (!_graphicalLib) {
        std::cerr << "Cannot open library: \n" << dlerror() << std::endl;
        return;
    }
}

void ArcadeCore::loadGame(std::string &game)
{
    if (_gameLib) {
        _DLLoader->closeLibrary(_gameLib);
        _gameLib = nullptr;
    }
    _gameLib = _DLLoader->loadGameLibrary(game);
    if (!_gameLib) {
        std::cerr << "Cannot open game: \n" << dlerror() << std::endl;
        return;
    }
}

void ArcadeCore::LimitFPS(std::chrono::time_point<std::chrono::system_clock> &start)
{
    std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>::zero();
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    while (elapsed_seconds.count() < 0.016) {
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
    }
    start = std::chrono::system_clock::now();
}

void ArcadeCore::arcadeLoop(int selectedGame, int selectedGraphicalLib)
{
    std::vector<Arcade::Key> keys;
    std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();

    while (true) {
        LimitFPS(start);

        keys = _graphicalLib->getPressedKeys();
        Arcade::IGameData &data = _gameLib->getGameData();

        _gameLib->update(_userName);
        _graphicalLib->render(data);
        _gameLib->handleKeys(keys);

        for (auto &key : keys)
            if (key == Arcade::Key::Enter) return;
        HandleKeys(keys, selectedGraphicalLib, selectedGame);
    }
}