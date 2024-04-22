/*
** EPITECH PROJECT, 2023
** Project
** File description:
** DLLoader
*/

#ifndef DLLoader_HPP
#define DLLoader_HPP

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <dlfcn.h>

#include <iostream>

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"


// Map <lib, <handle, exitPoint>>
using TypeHandle = std::map<void *, std::pair<void *, void (*)(void *)>>;

typedef void *(*EntryPoint)();
typedef void (*ExitPoint)(void *);

class DLLoader {
    public:
        DLLoader();
        ~DLLoader();

        Arcade::IDisplay *loadGraphicalLibrary(std::string &lib);
        Arcade::IGame *loadGameLibrary(std::string &lib);

        void closeLibrary(void *lib);

        template<typename T>
        T getSymbol(void *handle, std::string &symbol) {
            return reinterpret_cast<T>(dlsym(handle, symbol.c_str()));
        };

        template<typename T>
        T *loadLibrary(std::string &path, std::string &entryPointName, std::string &exitPointName) {
            std::string fullPath = path;
            void *handle = dlopen(fullPath.c_str(), RTLD_NOW | RTLD_NODELETE);
            EntryPoint entryPoint;
            ExitPoint exitPoint;

            if (!handle ||
            !(entryPoint = getSymbol<EntryPoint>(handle, entryPointName)) ||
            !(exitPoint = getSymbol<ExitPoint>(handle, exitPointName)))
                throw std::runtime_error("Invalid Lib");

            void *lib = entryPoint();
            _handles[lib] = std::make_pair(handle, exitPoint);

            return static_cast<T *>(lib);
        };

    private:
        TypeHandle _handles;
};


#endif /* !DLLoader_HPP */
