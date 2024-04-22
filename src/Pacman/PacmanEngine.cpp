/*
** EPITECH PROJECT, 2023
** ARCADE_PACMANENGINE_CPP
** File description:
** PacmanEngine.cpp
*/

#include "Pacman.hpp"

void Pacman::SaveScore(const std::string &username)
{
    std::ifstream file{"./scores/" + _data.getGameName() + ".score"};
    std::string line;
    std::string name = username;
    int actual_scores = _data.getScores()["SCORE"];
    int old_score = actual_scores;

    if (file.is_open()) {
        if (getline(file, line)) {
            std::istringstream iss(line);
            iss >> name >> old_score;
            if (old_score < actual_scores) {
                name = username;
                old_score = actual_scores;
            }
        }
        file.close();
    }
    std::ofstream file2;
    file2.open("./scores/" + _data.getGameName() + ".score", std::ios::trunc);
    if (file2.is_open()) {
        file2 << name << " " << old_score << std::endl;
        file2.close();
    }
}

void Pacman::update(const std::string &username) {
    if (_data.getIsPaused()) {
        _statingTimer = std::chrono::system_clock::now();
        return;
    }
    std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    std::chrono::duration<double> statingTimer = time - _statingTimer;

    if (_data.getGameOverVal()) {
        return;
    }

    std::chrono::duration<double> elapsed_seconds = time - _lastUpdate;

    if (statingTimer >= std::chrono::seconds(10))
        moveEnemy();
    if (elapsed_seconds.count() < 0.01)
        return;

    _lastUpdate = time;

    std::pair<float, float> &myPacPos = _data.myGetPacmanEntity()->getPos()[0];
    PacmanEntity *myPac = _data.myGetPacmanEntity();

    movePacPac(elapsed_seconds, myPacPos, myPac);

    handleColision(_direction.first, _direction.second, myPacPos);

    handleAction(username, myPacPos);
}
