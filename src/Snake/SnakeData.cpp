/*
** EPITECH PROJECT, 2023
** ARCADE_SNAKEDATA_CPP
** File description:
** SnakeData.cpp
*/

#include "Snake.hpp"

void SnakeData::resetGame()
{
    _entities.clear();
    _entities_a.clear();
    _gameOver = false;
    _isPaused = true;
    _scores["Size"] = 4;
    createEntity("food", 0, 0, "food");
    createEntity("food", 3, 4, "food");
    createEntity("food", 24, 24, "food");

    createEntity("snakeHead", 14, 11, "head");

    createEntity("snakeBody", 13, 11, "body");
    createEntity("snakeBody", 12, 11, "body");
    createEntity("snakeBody", 11, 11, "body");
    for (int i = 0; i < _mapSize.first; i++)
        for (int j = 0; j < _mapSize.second; j++)
            if (i == 0 || j == 0 || i == _mapSize.first - 1 || j == _mapSize.second - 1)
                createEntity("mur", i, j, "mur");
}

SnakeData::SnakeData()
{
    _controls["Z"] = "GO_UP";
    _controls["S"] = "GO_DOWN";
    _controls["Q"] = "GO_LEFT";
    _controls["D"] = "GO_RIGHT";
    _controls["R"] = "Restart_Game";
    _controls["Enter"] = "Leave_Game";
    _mapSize = std::make_pair(26, 26);
    _gameName = "SNAKE";
    _scores = std::map<std::string, int>();
    resetGame();
}

std::map<std::string, int> SnakeData::getScores() const {
    return _scores;
}

std::string SnakeData::getGameName() const {
    return _gameName;
}

std::vector<std::shared_ptr<Arcade::IEntity>> &SnakeData::getEntities()
{
    return _entities_a;
}

std::vector<std::shared_ptr<SnakeEntity>> &SnakeData::getGameEntities()
{
    return _entities;
}

std::pair<int, int> SnakeData::getMapSize() const {
    return _mapSize;
}

bool SnakeData::isGameOver() const
{
    return _gameOver;
}

const Arcade::ControlMap &SnakeData::getControls() const {
    return _controls;
}

void SnakeData::growSize(void)
{
    _scores["Size"] += 1;
}

void SnakeData::setGameOver(bool gameOver)
{
    _gameOver = gameOver;
}

void SnakeData::createEntity(const std::string& name, int pos_x, int pos_y, std::string texture)
{
    for (auto &entity : _entities) {
        if (entity->getName() == name) {
            entity->getPos().emplace_back(pos_x, pos_y);
            return;
        }
    }

    std::shared_ptr<SnakeEntity> entity = std::make_shared<SnakeEntity>(name, pos_x, pos_y, std::move(texture));
    _entities.push_back(entity);
    _entities_a.push_back(entity);
}

bool &SnakeData::getPaused(void)
{
    return _isPaused;
}
