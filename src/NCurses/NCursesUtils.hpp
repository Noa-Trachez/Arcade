/*
** EPITECH PROJECT, 2023
** Project
** File description:
** NCursesUtils
*/

#ifndef NCursesUtils_HPP
#define NCursesUtils_HPP

#include <ncurses.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <array>

class NCursesTexture {
    public:
        NCursesTexture() = default;
        ~NCursesTexture() = default;
        char character;
        std::string colors;
};

class NCursesUtils {
    public:
        static NCursesUtils getInstance() {
            static NCursesUtils instance;
            return instance;
        }
        ~NCursesUtils() = default;


        void drawBox(int x, int y, int width, int height, int color);
        void drawText(int x, int y, std::string text, int colorPair = 0);
        void loadTexture(std::string textureName, std::string gameName);
        void drawGameChar(int x, int y, std::string textureName, std::string gameName);
        void InitTexture(NCursesTexture &texture, std::string &textColor,
            std::string &backgroundColor, std::string &textureName);
        void _refreshNCurses();

private:
        NCursesUtils();
        const std::map<std::string, int> _colorMap = {
            {"black", COLOR_BLACK},
            {"red", COLOR_RED},
            {"green", COLOR_GREEN},
            {"yellow", COLOR_YELLOW},
            {"blue", COLOR_BLUE},
            {"magenta", COLOR_MAGENTA},
            {"cyan", COLOR_CYAN},
            {"white", COLOR_WHITE},
            {"none", COLOR_BLACK},
        };
        std::map<std::string, NCursesTexture> _textureMap;
        std::map<std::string, int> _pairList;
        std::array<std::regex, 3> _regexArray;
        std::smatch _match;

};


#endif /* !NCursesUtils_HPP */
