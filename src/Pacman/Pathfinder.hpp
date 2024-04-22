/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Pathfinder
*/

#ifndef Pathfinder_HPP
#define Pathfinder_HPP

#include <utility>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>

#define NO_DISCARD [[nodiscard]]

namespace Pathfinder {
	enum NODE_TYPE {
		USED = -2,
		BLOCKED = -1,
		EMPTY = 0,
	};

    class Pathfinder;
    class Path;
}

class Pathfinder::Path {
    public:
        Path(std::vector<std::vector<int>> grid, int width, int height, bool uniqPath) : _grid(grid), _mapWidth(width), _mapHeight(height), _uniqPath(uniqPath) {}; // Ignore copy warning !
        ~Path() = default;

        NO_DISCARD int getMapWidth() const { return _mapWidth; };
        NO_DISCARD int getMapHeight() const { return _mapHeight; };
        NO_DISCARD std::vector<std::vector<int>> getGrid() const { return _grid; };
        NO_DISCARD bool isInMap(int x, int y) const { return (x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight); }

        std::pair<int, int> getCoordsFrom(int x, int y);
        std::pair<float, float> getVectorFrom(float x, float y, float velocity);

		void resetUniquePath();

    protected:
        int _mapWidth;
        int _mapHeight;
		bool _uniqPath;

    private:
        void updatePathFrom(int x, int y);

        std::vector<std::vector<int>> _grid;
        std::pair<int, int> _destination;
};
std::ostream &operator<<(std::ostream &os, const Pathfinder::Path &path);


class Pathfinder::Pathfinder {
    public:
        Pathfinder(int width, int height) : _mapWidth(width), _mapHeight(height), _grid(_mapHeight, std::vector<int>(_mapWidth, EMPTY)) {};
        ~Pathfinder() = default;

        NO_DISCARD int getMapWidth() const { return _mapWidth; };
        NO_DISCARD int getMapHeight() const { return _mapHeight; };
        NO_DISCARD bool isInMap(int x, int y) const { return (x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight); }

        void addObstacle(int x, int y);
        void addObstacle(std::vector<std::pair<int, int>> &obstacles);

        Path getPathTo(int x, int y, bool uniqPath = false);

    private:
        void generateGrid(int x, int y);
        void resetGrid(bool keepObstacles = false);

        int _mapWidth;
        int _mapHeight;
        std::vector<std::vector<int>> _grid;

        bool needUpdate = false;
        std::pair<int, int> _lastPos {-1, -1};

        const int _maxDistance = 100;
};

#undef NO_DISCARD
#endif /* Pathfinder_HPP */
