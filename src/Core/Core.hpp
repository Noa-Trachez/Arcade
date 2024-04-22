/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Core
*/

#ifndef Core_HPP
#define Core_HPP

#include <string>
#include <iostream>
#include <utility>
#include <dirent.h>

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

class Core {
    public:
        explicit Core(std::string libPath) : _libPath(std::move(libPath)) {};
        ~Core() = default;

        int ErrorEngine();
        void RunArcade();
        int getTypeOfLib(const std::string &values);
        void AllLibs();

        class Error : std::exception {
            public:
                explicit Error(std::string string) : _message(std::move(string)) {};
                ~Error() override = default;
                [[nodiscard]] const char *what() const noexcept override;
            private:
                std::string _message;
        };
    private:
        const std::string _libPath;
        std::vector<std::string> _graphicLib;
        std::vector<std::string> _gameLib;
};


#endif /* !Core_HPP */
