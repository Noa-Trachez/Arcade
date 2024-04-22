/*
** EPITECH PROJECT, 2023
** Project
** File description:
** NCursesUtils
*/

#include "NCursesUtils.hpp"

NCursesUtils::NCursesUtils()
{
    _regexArray[0] = std::regex("^text:\\s(.*)");
    _regexArray[1] = std::regex("^bg-color:\\s(.*)");
    _regexArray[2] = std::regex("^text-color:\\s(.*)");
};

void NCursesUtils::_refreshNCurses()
{
    for (int i = 0; i <= LINES; i++) {
        for (int j = 0; j <= COLS; j++) {
            mvaddch(i, j, ' ');
        }
    }
}

void NCursesUtils::InitTexture(NCursesTexture &texture, std::string &textColor,
std::string &backgroundColor, std::string &textureName)
{
    texture.colors = textColor + backgroundColor;
    _textureMap[textureName] = texture;

    if (_pairList.find(texture.colors) == _pairList.end()) {
        init_pair(_pairList.size() + 2, _colorMap.at(textColor), _colorMap.at(backgroundColor));
        _pairList[texture.colors] = _pairList.size() + 2;
    }
}

void NCursesUtils::loadTexture(std::string textureName, std::string gameName)
{
    NCursesTexture texture;
    std::string textColor;
    std::string backgroundColor;
    std::string line;
    std::ifstream file;

    file.open("assets/" + gameName + "/ncurses/" + textureName);
    if (!file.is_open()) {
        texture.character = ' ';
        textColor = "black";
        backgroundColor = "magenta";
        InitTexture(texture, textColor, backgroundColor, textureName);
        return;
    }

    texture.character = ' ';

    while (std::getline(file, line)) {
        for (int i = 0; i < 3; i++) {
            if (std::regex_match(line, _match, _regexArray[i])) {
                if (i == 0) {
                    texture.character = _match[1].str().empty() ? ' ' : _match[1].str()[0];
                } else if (i == 1) {
                    backgroundColor = _match[1].str();
                } else if (i == 2) {
                    textColor = _match[1].str();
                }
            }
        }
    }

    if (_colorMap.find(textColor) == _colorMap.end()) {
        textColor = "black";
    }
    if (_colorMap.find(backgroundColor) == _colorMap.end()) {
        backgroundColor = "magenta";
    }

    InitTexture(texture, textColor, backgroundColor, textureName);

    file.close();
}

void NCursesUtils::drawGameChar(int x, int y, std::string textureName, std::string gameName)
{
    if (_textureMap.find(textureName) == _textureMap.end()) {
        loadTexture(textureName, gameName);
    }

    NCursesTexture texture = _textureMap[textureName];

    attron(COLOR_PAIR(_pairList[texture.colors]));
    mvaddch(x, y, texture.character);
    attroff(COLOR_PAIR(_pairList[texture.colors]));
}

void NCursesUtils::drawBox(int x, int y, int width, int height, int color)
{
    attron(COLOR_PAIR(color));
    for (int i = 0; i < height; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + width, ACS_VLINE);
    }
    for (int i = 0; i < width; i++) {
        mvaddch(y, x + i, ACS_HLINE);
        mvaddch(y + height, x + i, ACS_HLINE);
    }
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + width, ACS_URCORNER);
    mvaddch(y + height, x, ACS_LLCORNER);
    mvaddch(y + height, x + width, ACS_LRCORNER);
    attroff(COLOR_PAIR(color));
}

void NCursesUtils::drawText(int x, int y, std::string text, int colorPair)
{
    attron(COLOR_PAIR(colorPair));
    mvprintw(y, x, "%s", text.c_str());
    attroff(COLOR_PAIR(colorPair));
}
