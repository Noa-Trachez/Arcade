/*
** EPITECH PROJECT, 2023
** Project
** File description:
** DLLoader
*/

#include "DlLoader.hpp"
#include <iostream>

DLLoader::DLLoader()
{

}

DLLoader::~DLLoader()
{

}

Arcade::IDisplay *DLLoader::loadGraphicalLibrary(std::string &libName)
{
    std::string entryPointName = "createDisplay";
    std::string exitPointName = "deleteDisplay";
    return loadLibrary<Arcade::IDisplay>(libName, entryPointName, exitPointName);
}

Arcade::IGame *DLLoader::loadGameLibrary(std::string &libName)
{
    std::string entryPointName = "createGame";
    std::string exitPointName = "deleteGame";
    return loadLibrary<Arcade::IGame>(libName, entryPointName, exitPointName);
}

void DLLoader::closeLibrary(void *lib)
{
    if (!lib) return;
    if (_handles.find(lib) == _handles.end()) return;

    _handles[lib].second(lib);
    dlclose(_handles[lib].first);

    _handles.erase(lib);
}


