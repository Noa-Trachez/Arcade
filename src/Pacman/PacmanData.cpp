/*
** EPITECH PROJECT, 2023
** ARCADE_PACMANDATA_CPP
** File description:
** PacmanData.cpp
*/

#include "Pacman.hpp"

PacmanEntity *PacmanData::myGetPacmanEntity() const {
    return (_pacman_entity);
}

PacmanData::PacmanData() {
    _controls["Z"] = "GoUp";
    _controls["S"] = "GoDown";
    _controls["Q"] = "GoLeft";
    _controls["D"] = "GoRight";
    _controls["R"] = "Restart";
    _controls["Enter"] = "Leave_Game";
    _mapSize = std::make_pair(27, 31);
    _gameName = "PACMAN";
    _scores["LIFES"] = 3;
    _scores["SCORE"] = 0;
    _respawn = false;
    _gameOver = false;
    _isPaused = true;
    _tp = 0;
    _direction = std::make_pair(0, 0);
    _nextDirection = std::make_pair(0, 0);
    _mapContent = {
            "/=========================\\",
            "|............|............|",
            "|./==\\./===\\.|./===\\./==\\.|",
            "|o|  |.|   |.|.|   |.|  |o|",
            "|.\\==/.\\===/.|.\\===/.\\==/.|",
            "|.........................|",
            "|./==\\./\\./=====\\./\\./==\\.|",
            "|.\\==/.||.\\=====/.||.\\==/.|",
            "|......||....|....||......|",
            "\\====\\.|\\==\\.|./==/|./====/",
            "     |.|/==/.|.\\==\\|.|     ",
            "     |.||.........||.|     ",
            "     |.||./==-==\\.||.|     ",
            "=====/.\\/.|     |.\\/.\\=====",
            "..........|     |..........",
            "=====\\./\\.|     |./\\./=====",
            "     |.||.\\=====/.||.|     ",
            "     |.||.........||.|     ",
            "     |.||./=====\\.||.|     ",
            "/====/.\\/.\\=====/.\\/.\\====\\",
            "|............|............|",
            "|./==\\./===\\.|./===\\./==\\.|",
            "|.\\=\\|.\\===/.|.\\===/.|/=/.|",
            "|o..||....... .......||..o|",
            "\\=\\.||./\\./=====\\./\\.||./=/",
            "/=/.\\/.||.\\=====/.||.\\/.\\=\\",
            "|......||....|....||......|",
            "|./====/\\==\\.|./==/\\====\\.|",
            "|.\\========/.|.\\========/.|",
            "|.........................|",
            "\\=========================/"
    };

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

    std::string name;
    for (int y = 0; y < _mapContent.size(); y++) {
        for (int x = 0; x < _mapContent[y].size(); x++) {
            char c = _mapContent[y][x];
            createEntity(val[c], x, y, val[c]);
        }
    }

    createEntity("pacman", 13, 23, "player");
    createEntity("ennemy1", 13, 14, "en1");
    createEntity("ennemy2", 11, 14, "en2");
    createEntity("ennemy3", 15, 14, "en3");
    createEntity("ennemy4", 13, 11, "en4");
}

int &PacmanData::getTpVal() {
    return (_tp);
}

int PacmanData::needTp() const {
    return (_tp);
}

bool PacmanData::isGameOver() const {
    return _gameOver;
}

bool &PacmanData::getGameOverVal() {
    return _gameOver;
}

Arcade::IGameData &Pacman::getGameData() const {
    return (Arcade::IGameData &) _data;
}

std::map<std::string, int> PacmanData::getScores() const {
    return _scores;
}

std::map<std::string, int> &PacmanData::getScore() {
    return _scores;
}

std::string PacmanData::getGameName() const {
    return _gameName;
}

std::vector<std::shared_ptr<Arcade::IEntity>> &PacmanData::getEntities() {
    return _entities_a;
}

std::vector<std::shared_ptr<PacmanEntity>> &PacmanData::myGetEntities() {
    return _entities;
}

std::pair<int, int> PacmanData::getMapSize() const {
    return _mapSize;
}

std::array<std::string, 31> PacmanData::getMapContent() const {
    return _mapContent;
}

const Arcade::ControlMap &PacmanData::getControls() const {
    return _controls;
}

void PacmanData::createEntity(std::string name, int pos_x, int pos_y, std::string texture) {
    for (auto &ent: _entities) {
        if (ent->getName() == name) {
            ent->getPos().push_back(std::make_pair(pos_x, pos_y));
            return;
        }
    }
    std::shared_ptr<PacmanEntity> entity = std::make_shared<PacmanEntity>(name, pos_x, pos_y, texture);
    _entities.push_back(entity);
    _entities_a.push_back(entity);
    if (name == "pacman") {
        _pacman_entity = entity.get();
    }
}

bool &PacmanData::getIsPaused(void)
{
    return (_isPaused);
}

bool &PacmanData::getRespawnVal() {
    return (_respawn);
}

bool PacmanData::needRespawn() const {
    return (_respawn);
}
