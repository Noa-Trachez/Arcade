/*
** EPITECH PROJECT, 2023
** ARCADE_PACMANENTITY_C
** File description:
** PacmanEntity.cpp
*/

#include "Pacman.hpp"

PacmanEntity::PacmanEntity(std::string name, int pos_x, int pos_y, std::string texture) {
    _position = std::vector<std::pair<float, float>>();

    _position.push_back(std::make_pair(pos_x, pos_y));
    _size = std::make_pair(1, 1);
    _texture = texture;
    _rotation = 0;
    _weak = false;
    _name = name;
}

float PacmanEntity::getRotation() const {
    return _rotation;
}

std::string PacmanEntity::getTexture() const {
    return _texture;
}

std::pair<float, float> PacmanEntity::getSize() const {
    return _size;
}

std::vector<std::pair<float, float>> PacmanEntity::getPosition() const {
    return _position;
}

std::vector<std::pair<float, float>> &PacmanEntity::getPos() {
    return _position;
}

void PacmanEntity::setRotation(float rot) {
    _rotation = rot;
}

std::string PacmanEntity::getName() const {
    return (_name);
}

bool &PacmanEntity::getWeakness() {
    return (_weak);
}

bool PacmanEntity::needWeakness() const {
    return (_weak);
}

void PacmanEntity::setTexture(std::string txt) {
    _texture = txt;
}
