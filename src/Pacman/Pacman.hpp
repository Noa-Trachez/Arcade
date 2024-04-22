/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** MainNcurses.hpp
*/

#ifndef ARCADE_MAINPACMAN_HPP
#define ARCADE_MAINPACMAN_HPP

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <chrono>
#include "IDisplayModule.hpp"
#include "Pathfinder.hpp"

class PacmanEntity : public Arcade::IEntity { // a static cast pour etre utiliser
// static_cast<PacmanEntity>(Arcade::Entity)
    public:
        PacmanEntity(std::string name, int pos_x, int pos_y, std::string texture);
        ~PacmanEntity() = default;
        std::vector<std::pair<float, float>> getPosition() const override;
        std::vector<std::pair<float, float>> &getPos();
        std::pair<float, float> getSize() const override;
        std::string getTexture() const override;
        void setTexture(std::string txt);
        float getRotation() const override;
        void setRotation(float rot);
        std::string getName() const;
        bool &getWeakness();
        bool needWeakness() const;
        bool _isDead = false;

    private:
        std::vector<std::pair<float, float>> _position;
        std::pair<float, float> _size;
        std::string _texture;
        std::string _name;
        float _rotation;
        bool _weak;
};

class PacmanData : public Arcade::IGameData {
    public:
        PacmanData();
        ~PacmanData() = default;
        std::map<std::string, int> getScores() const override;
        std::map<std::string, int> &getScore();
        std::string getGameName() const override;
        std::vector<std::shared_ptr<Arcade::IEntity>> &getEntities() override;
        std::vector<std::shared_ptr<PacmanEntity>> &myGetEntities();
        PacmanEntity *myGetPacmanEntity() const;
        std::pair<int, int> getMapSize() const override;
        std::array<std::string, 31> getMapContent() const;
        bool &getRespawnVal();
        bool needRespawn() const;
        int &getTpVal();
        int needTp() const;
        bool &getGameOverVal();
        bool isGameOver() const override;
        void createEntity(std::string name, int pos_x, int pos_y, std::string texture);
        const Arcade::ControlMap &getControls() const override;
        bool &getIsPaused(void);

    private:
        Arcade::ControlMap _controls;
        std::map<std::string, int> _scores;
        std::string _gameName;
        std::vector<std::shared_ptr<PacmanEntity>> _entities;
        std::vector<std::shared_ptr<Arcade::IEntity>> _entities_a;
        PacmanEntity *_pacman_entity;
        std::pair<int, int> _mapSize;
        std::array<std::string, 31> _mapContent;
        std::pair<int, int> _direction;
        std::pair<int, int> _nextDirection;
        bool _respawn;
        bool _gameOver;
        int _tp;
        bool _isPaused;
};

class Pacman : public Arcade::IGame {
    public:
        Pacman();
        ~Pacman();

        float CalculDistance(float xFirst, float xSecond, float yFirst, float ySecond);
        void handleKeys(const std::vector<Arcade::Key> &pressedKeys) override;
        void handleColision(int x, int y, std::pair<float, float> myPacPos);
        void update(const std::string &username) override;
        void moveEnemy();
        void makeEnnemyWeak();
        void makeEnnemyStrong(PacmanEntity *ennemy);
        Arcade::IGameData &getGameData() const override;
        std::vector<std::pair<int, int>> getMapFinder();
        bool isAWall(std::pair<float, float> pos);
		void resetMap(int not_win = 0);
        void SaveScore(const std::string &username);
        void moveWeakEnemy(const std::chrono::time_point<std::chrono::system_clock> &time);
        void moveToBase(std::shared_ptr<PacmanEntity> &it, std::pair<float, float> &ennemyPos);
        void movePacPac(std::chrono::duration<double> elapsed_seconds, std::pair<float, float> &myPacPos, PacmanEntity *myPac);
        void handleAction(const std::string &username, std::pair<float, float> &myPacPos);
        void collisionCase(const std::shared_ptr<PacmanEntity> &it, std::pair<float, float> &pos, int i, std::pair<int, int> &newPos, float distance);

private:
        PacmanData _data;
        std::chrono::time_point<std::chrono::system_clock> _lastUpdate;
        std::chrono::time_point<std::chrono::system_clock> _lastEnemyUpdate;
        std::chrono::time_point<std::chrono::system_clock> _lastUpdateWeak;
        std::chrono::time_point<std::chrono::system_clock> _statingTimer;
        Pathfinder::Pathfinder _pathfinderBase;
        Pathfinder::Pathfinder _pathfinderPac;

        std::pair<float, float> _destination {13, 23};
        std::pair<int, int> _nextDirection {0, 0};
        std::pair<int, int> _direction {0, 0};
        float _rotation = 0.0f;
        float _speed = 8.0f;

        bool _weak = false;
};

#endif //ARCADE_MAINPACMAN_HPP
