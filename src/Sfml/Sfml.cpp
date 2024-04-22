/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Sfml
*/

#include "Sfml.hpp"
#include "string.h"


#include <iostream>

#define SFML_TILE_SIZE 64

extern "C"
{
    void *createDisplay() {
        Sfml *lib = new Sfml();

        lib->init();
        return lib;
    }

    void deleteDisplay(void *display) {
        Sfml *lib = reinterpret_cast<Sfml *>(display);

        lib->exit();
        delete lib;
    }
}

Sfml::Sfml() = default;

Sfml::~Sfml() = default;

void Sfml::init()
{
    _window.create(sf::VideoMode(1200, 600), "Arcade");
    if (!_window.isOpen())
        throw std::runtime_error("Window not opened");
    _window.setFramerateLimit(500);
    _window.setKeyRepeatEnabled(true);
    _window.setMouseCursorVisible(false);
    _window.setActive(true);
    if (!_font.loadFromFile("assets/fonts/sfml/menu_fonts.TTF"))
        throw std::runtime_error("Font not found");
    _text.setFont(_font);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);
	_mapBorder.setPosition(0, 0);
	_mapBorder.setOutlineThickness(2);
	_mapBorder.setOutlineColor(sf::Color::White);
	_mapBorder.setFillColor(sf::Color::Transparent);
}

void Sfml::exit()
{
    _window.close();
    _sprites.clear();
    _texture.clear();
}

std::vector <Arcade::Key> Sfml::getPressedKeys()
{
    std::vector<Arcade::Key> keys;

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            keys.push_back(Arcade::Key(36));
        if (_event.type == sf::Event::KeyPressed) {
            if (_keymap.find(_event.key.code) != _keymap.end())
                keys.push_back(Arcade::Key(_keymap[_event.key.code]));
        }
    }
    return keys;
}

void Sfml::DrawInformations(Arcade::IGameData &gameData, std::string gameName)
{
    std::map<std::string, int> scores = gameData.getScores();
    Arcade::ControlMap controls = gameData.getControls();

    DrawTextAtPosition(gameName.c_str(), 800, 10, sf::Color::Red);
    int x = 100;

    DrawTextAtPosition("scores:", 650, 50, sf::Color::White);

    for (auto &it : scores) {
        DrawTextAtPosition(it.first.c_str(), 670, x, sf::Color::White);
		size_t offset = it.first.length() * 15;
        DrawTextAtPosition(std::to_string(it.second).c_str(), 670 + offset, x, sf::Color::White);
        x += 50;
    }

    x = 100;
    DrawTextAtPosition("Controls:", 900, 50, sf::Color::White);
    for (auto &it : controls) {
        DrawTextAtPosition(it.first.c_str(), 920, x, sf::Color::White);
		size_t offset = it.first.length() * 20;
        DrawTextAtPosition(it.second.c_str(), 920 + offset, x, sf::Color::White);
        x += 50;
    }

    if (gameData.isGameOver())
        DrawTextAtPosition("GAME OVER", 800, 550, sf::Color::Red);
}

void Sfml::render(Arcade::IGameData &gameData)
{
    std::string gameName = gameData.getGameName();
    std::string TotalPath = "assets/" + gameName + "/sfml/";
    _window.clear(sf::Color::Black);
    std::pair<int, int> mapSize = gameData.getMapSize();
    DrawInformations(gameData, gameName);
    float ratioX = static_cast<float>(600) / static_cast<float>(mapSize.first);
    float ratioY = static_cast<float>(600) / static_cast<float>(mapSize.second);
    for (auto &entitie : gameData.getEntities()) {
        if (_sprites.find(entitie->getTexture()) == _sprites.end()) {
            _texture[entitie->getTexture()].loadFromFile(TotalPath + entitie->getTexture());
            _sprites[entitie->getTexture()].setTexture(_texture[entitie->getTexture()]);
            _sprites[entitie->getTexture()].setTextureRect(sf::IntRect(0, 0, SFML_TILE_SIZE, SFML_TILE_SIZE));
            _sprites[entitie->getTexture()].setTextureRect(sf::IntRect(0, 0, _texture[entitie->getTexture()].getSize().x, _texture[entitie->getTexture()].getSize().y));
        }
        for (auto &it : entitie->getPosition()) {
            _sprites[entitie->getTexture()].setScale(1, 1);
            _sprites[entitie->getTexture()].scale(ratioX / _sprites[entitie->getTexture()].getLocalBounds().width * entitie->getSize().first, ratioY / _sprites[entitie->getTexture()].getLocalBounds().height * entitie->getSize().second);
            _sprites[entitie->getTexture()].setOrigin(_sprites[entitie->getTexture()].getLocalBounds().width / 2, _sprites[entitie->getTexture()].getLocalBounds().height / 2);
            _sprites[entitie->getTexture()].setPosition(it.first * ratioX, it.second * ratioY);
            _sprites[entitie->getTexture()].setRotation(entitie->getRotation());
            _window.draw(_sprites[entitie->getTexture()]);
        }
    }
    std::pair<int, int> size = gameData.getMapSize();
    _mapBorder.setSize(sf::Vector2f(size.first * ratioX, size.second * ratioY));
    _window.draw(_mapBorder); _window.display();
}

void Sfml::DrawTextAtPosition(const char *string, int x, int y, sf::Color color)
{
    _text.setFillColor(color);
    _text.setString(string);
    _text.setPosition(x, y);
    _window.draw(_text);
}

void Sfml::DrawTextList(const std::vector<std::string> &lib, int selectedLib, int separator, int y, int factor)
{
    for (int i = 0; i < lib.size(); i++) {
        if (i == selectedLib)
            DrawTextAtPosition(lib[i].c_str(), separator, y, sf::Color::Red);
        else
            DrawTextAtPosition(lib[i].c_str(), separator, y, sf::Color::White);
        y += factor + 10;
    }
}

int Sfml::GetTextSize(const std::string &str)
{
    sf::Text text(str, _font);
    sf::FloatRect textRect = text.getLocalBounds();

    return textRect.width;
}

void Sfml::DrawBox(int x, int y, int width, int height)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setOutlineThickness(5.f);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setFillColor(sf::Color::Black);
    _window.draw(rectangle);
}

void Sfml::renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                      int selectedGame, int selectedDisplay, const Arcade::ControlMap &controls,
                      const std::string &username, const std::string &bestScoreUsername, int bestScore)
{
    _window.clear(sf::Color::Black);
    sf::FloatRect textRect = _text.getGlobalBounds();
    int factor = static_cast<int>(textRect.height);
    int height = ((games.size() < graphics.size() ? graphics.size() : games.size()) + 1);
    height = height * factor + height * 10;

    static int widthGame = [games, this](){
        int max = 0;
        for (auto &it: games)
            if (GetTextSize(it) > max) max = GetTextSize(it);
        return max + 50;
    }();
    static int widthGraphic = [graphics, this](){
        int max = 0;
        for (auto &it: graphics)
            if (GetTextSize(it) > max) max = GetTextSize(it);
        return max + 50;
    }();
    static int widthControls = [controls, this]() {
        int max = 0;
        for (auto &it: controls)
            if (GetTextSize(it.first) + GetTextSize(it.second) > max) max = GetTextSize(it.first) + GetTextSize(it.second);
        return max + 6;
    }();

    DrawBox(10, 10, widthGame, height);
    DrawBox(widthGame + 25, 10, widthGraphic, height);

    DrawTextAtPosition("Games:", 15, 10, sf::Color::White);
    DrawTextList(games, selectedGame, 25, factor + 15, factor);
    DrawTextAtPosition("Graphics:", widthGame + 30, 10, sf::Color::White);
    DrawTextList(graphics, selectedDisplay, widthGame + 40, factor + 15, factor);

    int heightControls = (controls.size() + 1) * factor + controls.size() * 10;
    int padding = 0;
    for (auto &it: controls) {
        if (it.first.size() > padding) padding = it.first.size();
    }
    padding = GetTextSize("  ") * padding;
    int i = 0;
    DrawBox(10, height + 25, widthControls + padding, heightControls);
    DrawTextAtPosition("Controls:", 15, height + 25, sf::Color::White);
    for (auto &it: controls) {
        DrawTextAtPosition(it.first.c_str(), 35, height + 45 + i * factor + i * 10, sf::Color::White);
        DrawTextAtPosition(it.second.c_str(), 35 + padding, height + 45 + i * factor + i * 10, sf::Color::White);
        i++;
    }

    int widthUsername = GetTextSize(username + "  ");
    if (GetTextSize("Username:  ") > widthUsername)
        widthUsername = GetTextSize("Username:  ");
    int heightUsername = 2 * factor;

    DrawBox(widthControls + padding + 25, height + 25, widthUsername, heightUsername + 10);
    DrawTextAtPosition("Username:", widthControls + padding + 35, height + heightUsername / 2 + 5, sf::Color::White);
    DrawTextAtPosition(username.c_str(), widthControls + padding + 45, height + heightUsername + 10, sf::Color::White);

    std::string score = std::to_string(bestScore);
    int widthBestScore = GetTextSize(bestScoreUsername) + GetTextSize("  ") + GetTextSize(score) + GetTextSize("  ");
    if (GetTextSize("Best Score:  ") > widthBestScore)
        widthBestScore = GetTextSize("Best Score:  ");
    int heightBestScore = 2 * factor + 15;
    DrawBox(widthControls + padding + 25, height + heightUsername + 50, widthBestScore, heightBestScore);
    DrawTextAtPosition("Best Score:", widthControls + padding + 30, height + heightUsername + 50, sf::Color::White);
    DrawTextAtPosition(bestScoreUsername.c_str(), widthControls + padding + 35, height + heightUsername + heightBestScore + 20, sf::Color::White);
    DrawTextAtPosition(std::to_string(bestScore).c_str(), widthControls + padding + 35 + GetTextSize((bestScoreUsername + "  ").c_str()), height + heightUsername + heightBestScore + 20, sf::Color::White);
    _window.display();
}
