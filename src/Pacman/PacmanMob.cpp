/*
** EPITECH PROJECT, 2023
** ARCADE_PACMANMOB_CPP
** File description:
** PacmanMob.cpp
*/

#include "Pacman.hpp"


void Pacman::moveWeakEnemy(const std::chrono::time_point<std::chrono::system_clock> &time)
{
    std::chrono::duration<double> elapsed_seconds_weak = time - _lastUpdateWeak;

    if (elapsed_seconds_weak.count() > 10) {
        for (auto &it: _data.myGetEntities()) {
            if (it->getName().find("ennemy") != std::string::npos) {
                makeEnnemyStrong(it.get());
                it->_isDead = false;
            }
        }
        _weak = false;
    }
}

void Pacman::moveToBase(std::shared_ptr<PacmanEntity> &it, std::pair<float, float> &ennemyPos)
{
    Pathfinder::Path path = _pathfinderBase.getPathTo(12, 13);
    std::pair<float, float> pathTo = path.getVectorFrom(it->getPos()[0].first, it->getPos()[0].second, 0.2);
    if (path.getVectorFrom(it->getPos()[0].first, it->getPos()[0].second, 0.1).first == 0 &&
        path.getVectorFrom(it->getPos()[0].first, it->getPos()[0].second, 0.1).second == 0) {
        it->_isDead = false;
        makeEnnemyStrong(it.get());
    }
    ennemyPos.first += pathTo.first;
    ennemyPos.second += pathTo.second;
}

void Pacman::moveEnemy() {
    std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = time - _lastEnemyUpdate;
    std::pair<float, float> &myPacPos = _data.myGetPacmanEntity()->getPos()[0];
    Pathfinder::Path pathPac = _pathfinderPac.getPathTo(myPacPos.first, myPacPos.second, true);

    if (_weak) {
        moveWeakEnemy(time);
    }

    if (elapsed_seconds.count() < 0.01)
        return;

    for (auto &it: _data.myGetEntities()) {
        if (it->getName().find("ennemy") != std::string::npos) {
            std::pair<float, float> &ennemyPos = it->getPos()[0];
            if (it->getWeakness() && !it->_isDead)
                pathPac = _pathfinderPac.getPathTo(1, 1);
            if (it->_isDead) {
                moveToBase(it, ennemyPos);
            } else {
                std::pair<float, float> pacPos =
                        pathPac.getVectorFrom(ennemyPos.first, ennemyPos.second,
                                              it->getWeakness() ? 0.02 : 0.08);
                ennemyPos.first += pacPos.first;
                ennemyPos.second += pacPos.second;
            }
        }
    }
    _lastEnemyUpdate = time;
}

void Pacman::makeEnnemyWeak() {
    for (auto &it: _data.myGetEntities()) {
        if (it->getName().find("ennemy") != std::string::npos) {
            _lastUpdateWeak = std::chrono::system_clock::now();
            it->setTexture("enweak");
            it->getWeakness() = true;
            _weak = true;
        }
    }
}

void Pacman::makeEnnemyStrong(PacmanEntity *ennemy) {
    if (ennemy->getName() == "ennemy1")
        ennemy->setTexture("en1");
    else if (ennemy->getName() == "ennemy2")
        ennemy->setTexture("en2");
    else if (ennemy->getName() == "ennemy3")
        ennemy->setTexture("en3");
    else if (ennemy->getName() == "ennemy4")
        ennemy->setTexture("en4");
    ennemy->getWeakness() = false;
}
