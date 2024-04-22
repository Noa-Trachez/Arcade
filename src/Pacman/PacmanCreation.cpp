/*
** EPITECH PROJECT, 2023
** ARCADE_MAINPACMAN_CPP
** File description:
** MainPacMan.cpp
*/

#include "Pacman.hpp"

extern "C"
{
    Arcade::IGame *createGame() {
        return new Pacman();
    }

    void deleteGame(Arcade::IGame *display) {
        delete dynamic_cast<Pacman *>(display);
    }
}

std::vector<std::pair<int, int>> Pacman::getMapFinder() {
    std::vector<std::pair<int, int>> map;

    for (auto &it: _data.myGetEntities()) {
        if (it->getName() == "little_wall")
            continue;
        if (it->getName().find("wall") != std::string::npos) {
            for (auto &pos: it->getPos()) {
                map.push_back(pos);
            }
        }
    }
    return map;
}

Pacman::Pacman() : _data(), _pathfinderBase(27, 31), _pathfinderPac(27, 31) {
    std::vector<std::pair<int, int>> wallList = getMapFinder();
    _pathfinderPac.addObstacle(wallList);
    _pathfinderBase.addObstacle(wallList);
	std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
	_statingTimer = time;
}

Pacman::~Pacman() {}

void Pacman::resetMap(int not_win)
{
    _data.getIsPaused() = true;
	_data.myGetEntities().clear();
    _data.getEntities().clear();
	std::map<char, std::string> val = {
		{'=',  "wall"},
		{'.',  "pacgum"},
		{'o',  "bigPacgum"},
		{'\\', "cornerDiagonalLeft_wall"},
		{'/',  "cornerDiagonalRight_wall"},
		{'-',  "little_wall"},
		{'|',  "vertical_wall"},
		{' ',  "space"}
	};

	std::array<std::string, 31> mapContent = _data.getMapContent();
	for (int y = 0; y < mapContent.size(); y++) {
		for (int x = 0; x < mapContent[y].size(); x++) {
			char c = mapContent[y][x];
			_data.createEntity(val[c], x, y, val[c]);
		}
	}

	_destination = {13, 23};
	_nextDirection = {0, 0};
	_direction = {0, 0};

    if (not_win == 1) {
        _data.getScore()["SCORE"] = 0;
        _data.getScore()["LIFES"] = 3;
        _data.getGameOverVal() = false;
    } else {
        _speed += 500;
    }

	_data.createEntity("pacman", 13, 23, "player");
	_data.createEntity("ennemy1", 13, 14, "en1");
	_data.createEntity("ennemy2", 11, 14, "en2");
	_data.createEntity("ennemy3", 15, 14, "en3");
	_data.createEntity("ennemy4", 13, 11, "en4");
}
