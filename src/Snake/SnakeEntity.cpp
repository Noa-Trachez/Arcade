/*
** EPITECH PROJECT, 2023
** ARCADE_SNAKEENTITY_CPP
** File description:
** SnakeEntity.cpp
*/

#include "Snake.hpp"

SnakeEntity::SnakeEntity(std::string name, int pos_x, int pos_y, std::string texture)
{
    _position = std::vector<vector2f>();

    _position.emplace_back(pos_x, pos_y);
    _size = std::make_pair(1, 1);
    _texture = std::move(texture);
    _rotation = 0;
    _name = std::move(name);
}

float SnakeEntity::getRotation() const
{
    return _rotation;
}

std::string SnakeEntity::getTexture() const
{
    return _texture;
}

vector2f SnakeEntity::getSize() const
{
    return _size;
}

std::vector<vector2f> SnakeEntity::getPosition() const
{
    return _position;
}

std::vector<vector2f> &SnakeEntity::getPos()
{
    return _position;
}

void SnakeEntity::setRotation(float rotation)
{
    _rotation = rotation;
}

std::string SnakeEntity::getName() const
{
    return _name;
}
