/*
** EPITECH PROJECT, 2023
** Project
** File description:
** NCurses
*/

#include "NCurses.hpp"
#include "NCursesUtils.hpp"
#include <sstream>
#include <cmath>

#define PAIR_BW 1
#define BRIGHT_WHITE 15
#define DEFAULT_COLORS 0

extern "C"
{
    void *createDisplay() {
        NCurses *lib = new NCurses();

        lib->init();
        return lib;
    }

    void deleteDisplay(void *display) {
        NCurses *lib = reinterpret_cast<NCurses *>(display);

        lib->exit();
        delete lib;
    }
}

NCurses::NCurses() = default;

NCurses::~NCurses() = default;

void NCurses::init() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    refresh();
    curs_set(0);

    if (has_colors() == FALSE) {
        std::cerr << "Your terminal does not support color" << std::endl;
        return;
    }
    start_color();
    use_default_colors();
    if (can_change_color() && COLORS >= 16)
        init_color(BRIGHT_WHITE, 1000, 1000, 1000);

    init_pair(DEFAULT_COLORS, COLOR_WHITE, COLOR_BLACK);
    init_pair(PAIR_BW, COLOR_BLACK, COLOR_WHITE);

    if (can_change_color() && COLORS >= 16) {
        init_color(COLOR_BLACK, 0, 0, 0);
        init_color(COLOR_RED, 1000, 0, 0);
        init_color(COLOR_GREEN, 0, 1000, 0);
        init_color(COLOR_YELLOW, 1000, 1000, 0);
        init_color(COLOR_BLUE, 0, 0, 1000);
        init_color(COLOR_MAGENTA, 1000, 0, 1000);
        init_color(COLOR_CYAN, 0, 1000, 1000);
        init_color(COLOR_WHITE, 1000, 1000, 1000);
    }
}

void NCurses::exit() {
    endwin();
}

std::vector<Arcade::Key> NCurses::getPressedKeys() {
    std::vector<Arcade::Key> keys;

    timeout(0);
    int c = getch();
    if (c < 0) return keys;

    if (_keymap.find(c) != _keymap.end())
        keys.push_back(Arcade::Key(_keymap[c]));
    return keys;
}

void NCurses::DrawInformations(Arcade::IGameData &gameData, const std::pair<int, int> &mapSize)
{
    std::map<std::string, int> scores = gameData.getScores();
    Arcade::ControlMap controls = gameData.getControls();
    std::string gameName = gameData.getGameName();

    attron(COLOR_PAIR(PAIR_BW));
    for (int i = 0; i < mapSize.second; i++) {
        mvprintw(i, mapSize.first, " ");
    }
    attroff(COLOR_PAIR(PAIR_BW));

    mvprintw(1, mapSize.first * 2, gameName.c_str());
    int x = 4;

    mvprintw(3, mapSize.first + 2, "scores:");
    for (auto &it : scores) {
        mvprintw(x, mapSize.first + 3, it.first.c_str());
        int decalage = it.first.size() + 3;
        mvprintw(x, mapSize.first + 3 + decalage, std::to_string(it.second).c_str());
        x += 1;
    }

    x = 4;
    mvprintw(3, mapSize.first * 2 + 5, "Controls:");
    for (auto &it : controls) {
        mvprintw(x, mapSize.first * 2 + 6, it.first.c_str());
        int decalage = it.first.size() + 3;
        mvprintw(x, mapSize.first * 2 + 6 + decalage, it.second.c_str());
        x += 1;
    }
}

void NCurses::render(Arcade::IGameData &gameData) {
    _._refreshNCurses();
    std::pair<int, int> mapSize = gameData.getMapSize();

    if (LINES < mapSize.second || COLS < mapSize.first * 3) {
        mvprintw(LINES / 2 - 1, COLS / 2 - 5, "TERMINAL TOO SMALL");
        refresh();
        return;
    }

    DrawInformations(gameData, mapSize);
    if (gameData.isGameOver()) {
        mvprintw(LINES/ 2 - 1, COLS / 2 - 5, "GAME OVER");
        refresh();
        return;
    }
    std::vector<std::shared_ptr<Arcade::IEntity>> entities = gameData.getEntities();
    std::map<std::string, int> scores = gameData.getScores();

    if (!entities.empty()) {
        for (auto &ent: entities) {
            std::vector<std::pair<float, float>> position = ent->getPosition();

            for (auto &pos: position) {
                int x = (int)(round(pos.second));
                int y = (int)(round(pos.first));
                _.drawGameChar(x, y, ent->getTexture(), gameData.getGameName());
            }
        }
    }
    refresh();
}

void NCurses::renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                         int selectedGame, int selectedDisplay, const Arcade::ControlMap &controls,
                         const std::string &username, const std::string &bestScoreUsername, int bestScore) {
    _._refreshNCurses();
    static int height = (games.size() < graphics.size() ? graphics.size() : games.size()) + 1;

    //draw Game Box
    static int widthGame = [games](){
        int max = 0;
        for (auto &it: games)
            if (it.size() > max) max = it.size();
        return max + 6;
    }();
    static int widthGraphics = [graphics]() {
        int max = 0;
        for (auto &it: graphics)
            if (it.size() > max) max = it.size();
        return max + 6;
    }();

    _.drawBox(0, 0, widthGame, height, 0);

    _.drawBox(widthGame + 1, 0, widthGraphics, height, 0);

    _.drawText(2, 0, "Games", 0);
    _.drawText(widthGame + 3, 0, "Graphics", 0);

    for (int i = 0; i < games.size(); i++) {
        _.drawText(2, i + 1, i == selectedGame ? "-> " + games[i] : games[i], i == selectedGame ? 1 : 0);
    }
    for (int i = 0; i < graphics.size(); i++) {
        _.drawText(widthGame + 2, i + 1, i == selectedDisplay ? "-> " + graphics[i] : graphics[i], i == selectedDisplay ? 1 : 0);
    }

    //draw Controls Box
    static int widthControls = [controls]() {
        int max = 0;
        for (auto &it: controls)
            if (it.first.size() + it.second.size() > max) max = it.first.size() + it.second.size();
        return max + 6;
    }();
    static int heightControls = controls.size() + 1;
    int padding = 0;
    for (auto &it: controls) {
        if (it.first.size() > padding) padding = it.first.size();
    }

    _.drawBox(0, height + 1, widthControls + padding, heightControls, 0);
    _.drawText(2, height + 1, "Controls", 0);
    int i = 0;
    for (auto &it: controls) {
        _.drawText(2, height + 2 + i, it.first, 0);
        _.drawText(2 + padding + 3, height + 2 + i, it.second, 0);
        i++;
    }

    //draw Username Box
    int widthUsername = username.size();
    static int heightUsername = 2;
    _.drawBox(widthControls + padding + 1, height + 1, widthUsername + 5, heightUsername, 0);
    _.drawText(widthControls + padding + 3, height + 1, "Username", 0);
    _.drawText(widthControls + padding + 4, height + 2, username, 0);

    //draw Best Score Box
    std::string score = std::to_string(bestScore);
    int widthBestScore = bestScoreUsername.size() + score.size();
    static int heightBestScore = 2;
    _.drawBox(widthControls + padding + 1, height + heightUsername + 2, widthBestScore + 5, heightBestScore, 0);
    _.drawText(widthControls + padding + 3, height + heightUsername + 2, "Best Score", 0);
    _.drawText(widthControls + padding + 4, height + heightUsername + 3, bestScoreUsername, 0);
    _.drawText(widthControls + padding + 4 + bestScoreUsername.size() + 1, height + heightUsername + 3, score, 0);

    refresh();
}
