/*
** EPITECH PROJECT, 2023
** Project
** File description:
** SDL2
*/

#include "Sdl2.hpp"
#include <iostream>

#define SDL_TILE_SIZE 64

extern "C"
{
    void *createDisplay() {
        Sdl2 *lib = new Sdl2();

        lib->init();
        return lib;
    }

    void deleteDisplay(void *display) {
        Sdl2 *lib = reinterpret_cast<Sdl2 *>(display);

        lib->exit();
        delete lib;
    }
}

Sdl2::Sdl2() = default;

Sdl2::~Sdl2() = default;

void Sdl2::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    if (TTF_Init() != 0)
        throw std::runtime_error("TTF_Init Error: " + std::string(TTF_GetError()));
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 600, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr)
        throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    _font = TTF_OpenFont("assets/fonts/sdl/menu_fonts.TTF", 24);
    if (_font == nullptr)
        throw std::runtime_error("TTF_OpenFont Error: " + std::string(TTF_GetError()));
}

void Sdl2::exit()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Sdl2::loadAssets(const std::string &path, const std::string &gameName)
{
    std::string fullPath = "assets/" + gameName + "/sdl/" + path;
    SDL_Surface *surface = IMG_Load(fullPath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

    if (surface == nullptr)
        throw std::runtime_error("IMG_Load Error: " + std::string(IMG_GetError()));
    if (texture == nullptr)
        throw std::runtime_error("SDL_CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
    _textures[path] = texture;
    SDL_FreeSurface(surface);
}

std::vector<Arcade::Key> Sdl2::getPressedKeys()
{
    std::vector<Arcade::Key> keys;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            keys.push_back(Arcade::Key(36));
        if (event.type == SDL_KEYDOWN)
            if (_keymap.find(event.key.keysym.sym) != _keymap.end())
                keys.push_back(Arcade::Key(_keymap[event.key.keysym.sym]));
    }
    return keys;
}

void Sdl2::DrawInformations(Arcade::IGameData &gameData, std::string gameName)
{
    std::map<std::string, int> scores = gameData.getScores();
    Arcade::ControlMap controls = gameData.getControls();
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};

    DrawTextAtPosition(gameName.c_str(), 800, 10, red);
    int x = 100;

    DrawTextAtPosition("scores:", 600, 50, white);

    for (auto &it : scores) {
        DrawTextAtPosition(it.first.c_str(), 620, x, white);
        int decalage = strlen(it.first.c_str()) * 15;
        DrawTextAtPosition(std::to_string(it.second).c_str(), 620 + decalage, x, white);
        x += 50;
    }

    x = 100;
    DrawTextAtPosition("Controls:", 900, 50, white);
    for (auto &it : controls) {
        DrawTextAtPosition(it.first.c_str(), 920, x, white);
        int decalage = strlen(it.first.c_str()) * 20;
        DrawTextAtPosition(it.second.c_str(), 920 + decalage, x, white);
        x += 50;
    }

    if (gameData.isGameOver())
        DrawTextAtPosition("GAME OVER", 800, 550, red);
}

void Sdl2::render(Arcade::IGameData &gameData)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    std::string gameName = gameData.getGameName();
    std::string texture;

    std::pair<int, int> mapSize = gameData.getMapSize();
    DrawInformations(gameData, gameName);
    for (auto &it : gameData.getEntities()) {
        texture = it->getTexture();
        if (_textures.find(texture) == _textures.end())
            loadAssets(it->getTexture(), gameData.getGameName());
        for (auto &it1 : it->getPosition()) {
            int _windowWidth;
            int _windowHeight;

            SDL_GetWindowSize(_window, &_windowWidth, &_windowHeight);
            _windowWidth /= 2;
            float ratioX = static_cast<float>(_windowWidth) / static_cast<float>(mapSize.first);
            float ratioY = static_cast<float>(_windowHeight) / static_cast<float>(mapSize.second);
            float x = it1.first * ratioX;
            float y = it1.second * ratioY;
            float w = SDL_TILE_SIZE / 3;
            float h = SDL_TILE_SIZE / 3;

            SDL_FRect rect = {x, y, w, h};
            SDL_RenderCopyExF(_renderer, _textures[texture], NULL, &rect, it->getRotation(), NULL, SDL_FLIP_NONE);
        }
    }
    SDL_RenderPresent(_renderer);
}


void Sdl2::DrawTextAtPosition(const char *string, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(_font, string, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Sdl2::DrawBox(int x, int y, int width, int height, SDL_Color color)
{
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(_renderer, &rect);
}

void Sdl2::DisplayTextList(const std::vector<std::string> &tab, int xStart, int yStart, int selected)
{
    int actual = 0;
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color textSelected = {255, 0, 0, 255};

    for (auto &it : tab) {
        DrawTextAtPosition(it.c_str(), xStart, yStart, (actual == selected) ? textSelected : textColor);
        yStart += 30;
        actual++;
    }
}

int Sdl2::GetTextSize(const std::string &text)
{
    int width = 0;
    int height = 0;

    TTF_SizeText(_font, text.c_str(), &width, &height);
    return width;
}

void Sdl2::renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                      int selectedGame, int selectedDisplay, const Arcade::ControlMap &controls,
                      const std::string &username, const std::string &bestScoreUsername, int bestScore)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    int factor = 100;
    TTF_SizeText(_font, "Games:", NULL, &factor);
    int height = ((games.size() < graphics.size() ? graphics.size() : games.size()) + 1);
    height = height * factor + height * 5;

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

    DrawBox(5, 5, widthGame, height, {255, 255, 255, 255});
    DrawBox(widthGame + 10, 5, widthGraphic, height, {255, 255, 255, 255});

    DrawTextAtPosition("Games:", 10, 5, {255, 255, 255, 255});
    DisplayTextList(games, 30, 30, selectedGame);
    DrawTextAtPosition("Graphics:", widthGame + 15, 5, {255, 255, 255, 255});
    DisplayTextList(graphics, widthGame + 40, 30, selectedDisplay);

    static int heightControls = (controls.size() + 1) * factor;
    int padding = 0;
    for (auto &it: controls) {
        if (it.first.size() > padding) padding = it.first.size();
    }
    padding = GetTextSize("  ") * padding;
    int i = 0;
    DrawBox(5, height + 10, widthControls + padding, heightControls, {255, 255, 255, 255});
    DrawTextAtPosition("Controls:", 10, height + 10, {255, 255, 255, 255});
    for (auto &it: controls) {
        DrawTextAtPosition(it.first.c_str(), 30, height + 30 + i * factor, {255, 255, 255, 255});
        DrawTextAtPosition(it.second.c_str(), 30 + padding, height + 30 + i * factor, {255, 255, 255, 255});
        i++;
    }

    int widthUsername = GetTextSize(username + "  ");
    if (GetTextSize("Username:  ") > widthUsername)
        widthUsername = GetTextSize("Username:  ");
    static int heightUsername = 2 * factor;

    DrawBox(widthControls + padding + 10, height + 10, widthUsername, heightUsername + 10, {255, 255, 255, 255});
    DrawTextAtPosition("Username:", widthControls + padding + 15, height + heightUsername / 2 - 10, {255, 255, 255, 255});
    DrawTextAtPosition(username.c_str(), widthControls + padding + 20, height + heightUsername - 10, {255, 255, 255, 255});


    std::string score = std::to_string(bestScore);
    int widthBestScore = GetTextSize(bestScoreUsername) + GetTextSize("  ") + GetTextSize(score) + GetTextSize("  ");
    if (GetTextSize("Best Score:  ") > widthBestScore)
        widthBestScore = GetTextSize("Best Score:  ");
    static int heightBestScore = 2 * factor;
    DrawBox(widthControls + padding + 10, height + heightUsername + 25, widthBestScore, heightBestScore, {255, 255, 255, 255});
    DrawTextAtPosition("Best Score:", widthControls + padding + 15, height + heightUsername + 25, {255, 255, 255, 255});
    DrawTextAtPosition(bestScoreUsername.c_str(), widthControls + padding + 15, height + heightUsername + heightBestScore, {255, 255, 255, 255});
    DrawTextAtPosition(std::to_string(bestScore).c_str(), widthControls + padding + 15 + GetTextSize((bestScoreUsername + "  ").c_str()), height + heightUsername + heightBestScore, {255, 255, 255, 255});
    SDL_RenderPresent(_renderer);
}
