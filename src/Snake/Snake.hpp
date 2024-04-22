/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** MainNcurses.hpp
*/

#ifndef ARCADE_MAINSnake_HPP
#define ARCADE_MAINSnake_HPP

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <utility>
#include <chrono>
#include <math.h>

#include "IDisplayModule.hpp"

using vector2f = std::pair<float, float>;

class SnakeEntity : public Arcade::IEntity { // a static cast pour etre utiliser
// static_cast<SnakeEntity>(Arcade::Entity)
    public:
        SnakeEntity(std::string name, int pos_x, int pos_y, std::string texture);
        ~SnakeEntity() = default;

        std::vector<vector2f> getPosition() const override;
        std::vector<vector2f> &getPos();
        vector2f getSize() const override;
        std::string getTexture() const override;
        float getRotation() const override;
        void setRotation(float rotation);
        std::string getName() const;

    private:
        std::vector<vector2f> _position;
        vector2f _size;
        std::string _texture;
        std::string _name;
        float _rotation;
};

class SnakeData : public Arcade::IGameData {
    public:
        SnakeData();
        ~SnakeData() = default;

        std::map<std::string, int> getScores() const override;
        std::string getGameName() const override;
        std::vector<std::shared_ptr<Arcade::IEntity>> &getEntities() override;
        std::pair<int, int> getMapSize() const override;
        bool isGameOver() const override;
        void createEntity(const std::string &name, int pos_x, int pos_y, std::string texture);
        std::vector<std::shared_ptr<SnakeEntity>> &getGameEntities();
        void setGameOver(bool gameOver);
        const Arcade::ControlMap &getControls() const override;
        void growSize(void);
        void resetGame(void);
        bool &getPaused(void);


private:
        Arcade::ControlMap _controls;
        std::map<std::string, int> _scores;
        std::string _gameName;
        std::vector<std::shared_ptr<SnakeEntity>> _entities;
        std::vector<std::shared_ptr<Arcade::IEntity>> _entities_a;
        std::pair<int, int> _mapSize;
        bool _gameOver = false;
        bool _isPaused = false;
};

class Snake : public Arcade::IGame {
    public:
        Snake();
        ~Snake();

        void handleKeys(const std::vector<Arcade::Key> &pressedKeys) override;
        void update(const std::string &username) override;
        Arcade::IGameData &getGameData() const override;

        enum Direction {
            UP = Arcade::Key::Z,
            DOWN = Arcade::Key::S,
            LEFT = Arcade::Key::Q,
            RIGHT = Arcade::Key::D
        };
        void snakeMove(Direction key, const std::string &username);
        void snakeHeadCollision(vector2f headPos, const std::string &obstacleName,
            void (Snake::*callback)(vector2f, const std::string &), const std::string &username);

        void snakeGrow(vector2f headPos, [[maybe_unused]] const std::string &username);
        void endGame([[maybe_unused]] vector2f headPos, const std::string &username);

        void deleteFood(vector2f headPos);
        void SaveScore(const std::string &username);
private:
        SnakeData _data;

        Direction _snakeDirection = RIGHT;
        Direction _nextDirection = RIGHT;
        std::chrono::time_point<std::chrono::system_clock> _lastUpdate;
};

#endif //ARCADE_MAINSnake_HPP
