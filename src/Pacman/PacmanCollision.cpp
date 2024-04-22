/*
** EPITECH PROJECT, 2023
** ARCADE_PACMANCOLLISION_CPP
** File description:
** PacmanCollision.cpp
*/

#include "Pacman.hpp"

float Pacman::CalculDistance(float xFirst, float xSecond, float yFirst, float ySecond)
{
    return static_cast<float>(sqrt(pow((xFirst - xSecond), 2) + pow((yFirst - ySecond), 2)));
}

bool Pacman::isAWall(std::pair<float, float> pos) {
    for (auto &entity: _data.myGetEntities()) {
        std::string name = entity->getName();
        if (name.find("wall") == std::string::npos) {
            for (auto &posWall: entity->getPos()) {
                float distance = CalculDistance(pos.first, posWall.first, pos.second, posWall.second);
                if (fabs(distance) <= 0.1) return true;
            }
        }
    }
    return false;
}

void Pacman::collisionCase(const std::shared_ptr<PacmanEntity> &it, std::pair<float, float> &pos, int i, std::pair<int, int> &newPos, float distance)
{
    if (fabs(distance) <= 0.5) {
        if (it->getName().find("pacgum") != std::string::npos) {
            _data.getScore()["SCORE"] += 10;
            newPos = pos;
            it->getPos().erase(it->getPos().begin() + i);
            _data.createEntity("space", newPos.first, newPos.second, "space");
        }
        if (it->getName().find("bigPacgum") != std::string::npos) {
            _data.getScore()["SCORE"] += 50;
            newPos = pos;
            it->getPos().erase(it->getPos().begin() + i);
            _data.createEntity("space", newPos.first, newPos.second, "space");
            makeEnnemyWeak();
        }
        if (it->getName().find("ennemy") != std::string::npos) {
            if (it->needWeakness()) {
                _data.getScore()["SCORE"] += 200;//  score+200 * 2^(nbennemy already eaten)
                it->setTexture("endead");
                it->_isDead = true;
            } else {
                _data.getScore()["LIFES"] -= 1;
                if (_data.getScores()["LIFES"] > 0)
                    _data.getRespawnVal() = true;
            }
        }
    }
}

void Pacman::handleColision(int x, int y, std::pair<float, float> myPacPos) {
    std::pair<int, int> newPos;
    int i = 0;

    if (CalculDistance(myPacPos.first, -1, 14, myPacPos.second) <= 1 && x == -1)
        _data.getTpVal() = 1;
    if (CalculDistance(myPacPos.first, 27, 14, myPacPos.second) <= 1 && x == 1)
        _data.getTpVal() = 2;

    bool NoPacgum = true;
    for (auto &it: _data.myGetEntities()) {
        if (it->getName() == "space" || it->getName() == "pacman")
            continue;
        if (it->getName().find("pacgum") != std::string::npos && !it->getPos().empty())
            NoPacgum = false;
        for (auto &pos: it->getPos()) {
            float distance = CalculDistance(myPacPos.first, pos.first, myPacPos.second, pos.second);
            collisionCase(it, pos, i, newPos, distance);
            i++;
        }
        i = 0;
    }

    if (NoPacgum)
        resetMap();
}
