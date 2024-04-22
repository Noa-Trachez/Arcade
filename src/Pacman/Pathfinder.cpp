/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Pathfinder
*/

#include "Pathfinder.hpp"
#include <sstream>

///////////////////////////////////////////
//        Pathfinder::Pathfinder         //
///////////////////////////////////////////

void Pathfinder::Pathfinder::addObstacle(int x, int y)
{
    if (!isInMap(x, y)) return;
    _grid[y][x] = BLOCKED;
    needUpdate = true;
}

void Pathfinder::Pathfinder::addObstacle(std::vector<std::pair<int, int>> &obstacles)
{
    for (auto &obstacle : obstacles)
        addObstacle(obstacle.first, obstacle.second);
}

void Pathfinder::Pathfinder::generateGrid(int x, int y)
{
    std::queue<std::tuple<int, int, int>> queue;

    if (!isInMap(x, y)) return;

    resetGrid(true);
    queue.emplace(y, x, _maxDistance);

    while(!queue.empty()) {
        std::tuple<int, int, int> current = queue.front();
        queue.pop();

        int currY = std::get<0>(current);
        int currX = std::get<1>(current);
        int distance = std::get<2>(current);

        if (_grid[currY][currX] != BLOCKED && distance >= 0)
            _grid[currY][currX] = distance;
        else continue;

        if (currY > 0 && _grid[currY - 1][currX] < (distance - 1))
            queue.emplace(currY - 1, currX, distance - 1);

        if (currY < _mapHeight - 1 && _grid[currY + 1][currX] < (distance - 1))
            queue.emplace(currY + 1, currX, distance - 1);

        if (currX > 0 && _grid[currY][currX - 1] < (distance - 1))
            queue.emplace(currY, currX - 1, distance - 1);

        if (currX < _mapWidth - 1 && _grid[currY][currX + 1] < (distance - 1))
            queue.emplace(currY, currX + 1, distance - 1);
    }
    needUpdate = false;
    _lastPos = {x, y};
}

void Pathfinder::Pathfinder::resetGrid(bool keepObstacles)
{
    for (auto &column : _grid)
        for (auto &cell : column)
            cell = (keepObstacles && cell == BLOCKED) ? BLOCKED : 0;
}

Pathfinder::Path Pathfinder::Pathfinder::getPathTo(int x, int y, bool uniqPath)
{
    if (!isInMap(x, y)) return {{}, 0, 0, uniqPath};
    if (needUpdate || _lastPos.first != x || _lastPos.second != y) generateGrid(x, y);

    return {_grid, _mapWidth, _mapHeight, uniqPath};
}


///////////////////////////////////////////
//           Pathfinder::Path            //
///////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Pathfinder::Path &path)
{
    os << "\t=====| PATHFINDER INFOS |===== " << std::endl;
    os << " > Map Width: " << path.getMapWidth() << std::endl;
    os << " > Map Height: " << path.getMapHeight() << std::endl;

    for (auto &col : path.getGrid()) {
        for (auto &cell : col) {
            if (cell >= 0)
                os << " ";
            else
                os << "#";
        }
        os << std::endl;
    }
    return os;
}

void Pathfinder::Path::updatePathFrom(int x, int y)
{
    if (!isInMap(x, y)) return;

    int max = 0;
    _destination = {x, y};


    if (isInMap(x + 1, y) && _grid[y][x + 1] > max) {
        max = _grid[y][x + 1];
        _destination = {x + 1, y};
    }
    if (isInMap(x - 1, y) && _grid[y][x - 1] > max) {
        max = _grid[y][x - 1];
        _destination = {x - 1, y};
    }
    if (isInMap(x, y + 1) && _grid[y + 1][x] > max) {
        max = _grid[y + 1][x];
        _destination = {x, y + 1};
    }
    if (isInMap(x, y - 1) && _grid[y - 1][x] > max)
        _destination = {x, y - 1};

	if (_uniqPath)
		_grid[_destination.second][_destination.first] = USED;
}

std::pair<int, int> Pathfinder::Path::getCoordsFrom(int x, int y)
{
    updatePathFrom(x, y);
    return _destination;
}

std::pair<float, float> Pathfinder::Path::getVectorFrom(float x, float y, float velocity)
{
    int x1 = static_cast<int>(round(x));
    int y1 = static_cast<int>(round(y));
    updatePathFrom(x1, y1);
    auto vector_x = static_cast<float>(_destination.first) - x;
    auto vector_y = static_cast<float>(_destination.second) - y;

    double angle = atan2f(vector_y, vector_x);

    float mx = velocity * (float)cos(angle);
    float my = velocity * (float)sin(angle);

    if (vector_x == 0 && vector_y == 0) return {0, 0};
    else return std::make_pair(mx, my);
}

void Pathfinder::Path::resetUniquePath()
{
	for (auto &col : _grid)
		for (auto &cell : col)
			if (cell == USED)
				cell = EMPTY;
}
