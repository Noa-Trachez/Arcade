/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Core
*/

#include "Core.hpp"
#include "Arcade.hpp"


const char *Core::Error::what() const noexcept
{
    return _message.c_str();
}

int Core::getTypeOfLib(const std::string &values)
{
    int type = 0;
    void *handle = dlopen(values.c_str(), RTLD_NOW | RTLD_NODELETE);
    void *sym = nullptr;

    if (!handle) return -1;
    dlerror();

    sym = dlsym(handle, "createDisplay");
    if (!sym) {
        type = 1;
        sym = dlsym(handle, "createGame");
        if (!sym) {
            dlclose(handle);
            return -1;
        }
    }

    if (type == 1)
        sym = dlsym(handle, "deleteGame");
    else
        sym = dlsym(handle, "deleteDisplay");

    if (!sym) {
        dlclose(handle);
        return -1;
    }

    dlclose(handle);
    return type;
}

void Core::AllLibs()
{
    DIR *dir = opendir("./lib");
    struct dirent *ent;
    int type;

    if (dir == nullptr)
        throw Core::Error("Error: opendir failed");

    while ((ent = readdir(dir)) != nullptr) {
        if (ent->d_name[0] != '.') {
            std::string path = "./lib/" + std::string(ent->d_name);
            type = getTypeOfLib(path);
            if (type == -1) continue;
            if (type == 0)
                _graphicLib.push_back(path);
            else
                _gameLib.push_back(path);
        }
    }
    closedir(dir);

    std::string newPath = "./" + _libPath;
    if ((std::find(_graphicLib.begin(), _graphicLib.end(), newPath) == _graphicLib.end()) && (std::find(_gameLib.begin(), _gameLib.end(), _libPath) == _gameLib.end())) {
        type = getTypeOfLib(_libPath);
        if (type == -1 || !type) throw Core::Error("Error: Invalid lib");
        _graphicLib.push_back(_libPath);
    }
}

int Core::ErrorEngine()
{
    try {
        AllLibs();
        if (_graphicLib.empty())
            throw Core::Error("Error: No graphic lib found");
        if (_gameLib.empty())
            throw Core::Error("Error: No game lib found");
    } catch (Core::Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

void Core::RunArcade()
{
    ArcadeCore *arcade = new ArcadeCore();
    int index_selected_lib = 0;

    std::string newPath = "./" + _libPath;
    auto it = std::find(_graphicLib.begin(), _graphicLib.end(), newPath);
    if (it != _graphicLib.end())
        index_selected_lib = it - _graphicLib.begin();
    else
        index_selected_lib = std::find(_graphicLib.begin(), _graphicLib.end(), _libPath) - _graphicLib.begin();

    try {
        arcade->arcadeMenu(_gameLib, _graphicLib, 0, index_selected_lib);
    } catch (std::exception &e) {
        if (e.what() != std::string("Exit"))
            std::cerr << "Error: " << e.what() << std::endl;
    }
    delete arcade;
}
