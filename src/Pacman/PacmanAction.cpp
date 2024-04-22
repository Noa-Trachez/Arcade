/*
** EPITECH PROJECT, 2023
** ARCADE_PACMANACTION_CPP
** File description:
** PacmanAction.cpp
*/

#include "Pacman.hpp"

void Pacman::handleKeys(const std::vector<Arcade::Key> &pressedKeys) {
    int x = -5;
    int y = -5;
    std::pair<float, float> &myPacPos = _data.myGetPacmanEntity()->getPos()[0];

    for (auto &it: pressedKeys) {
        _data.getIsPaused() = false;
        if (it == Arcade::Key::Q) {
            x = -1;
            y = 0;
            _rotation = 180;
        } else if (it == Arcade::Key::D) {
            x = 1;
            y = 0;
            _rotation = 0;
        } else if (it == Arcade::Key::Z) {
            y = -1;
            x = 0;
            _rotation = -90;
        } else if (it == Arcade::Key::S) {
            y = 1;
            x = 0;
            _rotation = 90;
        } else if (it == Arcade::Key::R) {
            resetMap(1);
            return;
        }
        if (x != -5 && y != -5)
            _nextDirection = std::make_pair(x, y);
    }
}

void Pacman::movePacPac(std::chrono::duration<double> elapsed_seconds, std::pair<float, float> &myPacPos, PacmanEntity *myPac)
{
    float velocity = static_cast<float>(elapsed_seconds.count()) * _speed;
    float vector_x = _destination.first - myPacPos.first;
    float vector_y = _destination.second - myPacPos.second;
    double angle = atan2f(vector_y, vector_x);
    float mx = (velocity > 0.16f ? 0.16f : velocity) * (float) cos(angle);
    float my = (velocity > 0.16f ? 0.16f : velocity) * (float) sin(angle);

    if (vector_x == 0 && vector_y == 0) {
        _direction = _nextDirection;
        mx = my = 0;
    }

    myPacPos.first += mx;
    myPacPos.second += my;
    float distance = CalculDistance(myPacPos.first, _destination.first, myPacPos.second, _destination.second);

    if (fabs(distance) <= (float) 0.1) {
        myPacPos = _destination;
        std::pair<float, float> destination = {myPacPos.first + _direction.first, myPacPos.second + _direction.second};
        std::pair<float, float> nextDestination = {myPacPos.first + _direction.first + _nextDirection.first, myPacPos.second + _direction.second + _nextDirection.second};
        _destination = (isAWall(destination)) ? destination : _destination;
        if (isAWall(nextDestination)) {
            _direction = _nextDirection;
            myPac->setRotation(_rotation);
        }
    }
}

void Pacman::handleAction(const std::string &username, std::pair<float, float> &myPacPos)
{
    std::pair<float, float> tmp;

    if (_data.getScore()["LIFES"] <= 0) {
        SaveScore(username);
        _data.getGameOverVal() = true;
        return;
    }
    if (_data.needRespawn()) {
        myPacPos = std::make_pair(13, 23);
        _destination = {13, 23};
        _direction = std::make_pair(0, 0);
        _nextDirection = std::make_pair(0, 0);
        _data.getRespawnVal() = false;
        return;
    }
    if (_data.needTp() == 1)
        tmp = std::make_pair(26, 14);
    if (_data.needTp() == 2)
        tmp = std::make_pair(0, 14);
    if (_data.needTp() != 0) {
        myPacPos = tmp;
        _destination = tmp;
        _data.getTpVal() = 0;
    }
}
