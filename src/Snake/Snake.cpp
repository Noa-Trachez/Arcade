/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Snake
*/

#include "Snake.hpp"

extern "C"
{
    Arcade::IGame *createGame() {
        return new Snake();
    }

    void deleteGame(Arcade::IGame *display) {
        delete dynamic_cast<Snake *>(display);
    }
}

Snake::Snake() : _data() {}

Snake::~Snake() = default;

void Snake::handleKeys(const std::vector<Arcade::Key> &pressedKeys)
{
    for (auto &key : pressedKeys) {
        _data.getPaused() = false;
        if (key == Arcade::Key::R) {
            _snakeDirection = Snake::RIGHT;
            _data.resetGame();
        }
        if (key == Arcade::Key::Z || key == Arcade::Key::S || key == Arcade::Key::Q || key == Arcade::Key::D) {
            auto news = static_cast<Direction>(key);
            if (news == UP && _snakeDirection == DOWN)
                continue;
            if (news == DOWN && _snakeDirection == UP)
                continue;
            if (news == LEFT && _snakeDirection == RIGHT)
                continue;
            if (news == RIGHT && _snakeDirection == LEFT)
                continue;
            _nextDirection = news;
        }
    }
}

void Snake::update(const std::string &username)
{
    if (_data.getPaused())
        return;
    std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = time - _lastUpdate;

    if (elapsed_seconds.count() < 0.2)
        return;
    if (_data.isGameOver())
        return;
    _snakeDirection = _nextDirection;
    snakeMove(_snakeDirection, username);

    _lastUpdate = time;
}

void Snake::snakeMove(Direction direction, const std::string &username)
{
    std::vector<std::shared_ptr<SnakeEntity>> snakeEntities = _data.getGameEntities();

    vector2f newPos([direction] {
        switch (direction) {
            case UP:
                return std::make_pair(0, -1);
            case DOWN:
                return std::make_pair(0, 1);
            case LEFT:
                return std::make_pair(-1, 0);
            case RIGHT:
                return std::make_pair(1, 0);
            default:
                return std::make_pair(0, 0);
        }
    }());
	int rotation = [direction] {
		switch (direction) {
			case UP:
				return -90;
			case DOWN:
				return 90;
			case LEFT:
				return 180;
			case RIGHT:
				return 0;
			default:
				return 0;
		}
	}();


    std::vector<vector2f> oldHeadPos;
    std::vector<vector2f> newHeadPos;
    for (auto entity : snakeEntities) {
        if (entity->getName() == "snakeHead") {
            std::vector<vector2f> &pos = entity->getPos();
            oldHeadPos = pos;
            pos[0].first += newPos.first;
            pos[0].second += newPos.second;
			entity->setRotation(rotation);
            newHeadPos = pos;
            break;
        }
    }

    for (auto entity : snakeEntities) {
        if (entity->getName() == "snakeBody") {
            std::vector<vector2f> &pos = entity->getPos();

            for (auto i = pos.rbegin(); i != pos.rend(); ++i) {
                if (i + 1 == pos.rend()) {
                    i->first = oldHeadPos[0].first;
                    i->second = oldHeadPos[0].second;
                } else {
                    i->first = (i + 1)->first;
                    i->second = (i + 1)->second;
                }
            }
        }
    }
    snakeHeadCollision(newHeadPos[0], "snakeBody", &Snake::endGame, username);
    snakeHeadCollision(newHeadPos[0], "food", &Snake::snakeGrow, username);

	std::pair<int, int> mapSize = _data.getMapSize();
	if (newHeadPos[0].first < 1 || newHeadPos[0].first >= mapSize.first - 1 || newHeadPos[0].second < 1 || newHeadPos[0].second >= mapSize.second - 1)
		endGame(newHeadPos[0], username);
}

void Snake::snakeHeadCollision(vector2f headPos, const std::string &obstacleName, void (Snake::*callback)(vector2f, const std::string &), const std::string &username)
{
    for (auto entity : _data.getGameEntities())
        if (entity->getName() == obstacleName)
            for (auto &pos : entity->getPos())
                if (pos.first == headPos.first && pos.second == headPos.second)
                    (this->*callback)(headPos, username);
}

void Snake::snakeGrow(vector2f headPos, [[maybe_unused]] const std::string &username)
{
    for (auto entity : _data.getGameEntities())
        if (entity->getName() == "snakeBody") {
            entity->getPos().emplace_back(entity->getPos().back());
            deleteFood(headPos);
            return;
        }
}

void Snake::deleteFood(vector2f headPos)
{
    for (auto entity : _data.getGameEntities())
        if (entity->getName() == "food") {
            auto &pos = entity->getPos();
            for (int i = 0; i < pos.size(); i++)
                if (pos[i].first == headPos.first && pos[i].second == headPos.second) {
                    std::pair<int, int> mapSize = _data.getMapSize();
                    pos.erase(pos.begin() + i);
                    pos.emplace_back((rand()) % (mapSize.first - 2) + 1, (rand()) % (mapSize.second - 2) + 1);
                    _data.growSize();
                    break;
                }
        }
}

void Snake::SaveScore(const std::string &username)
{
    std::ifstream file{"./scores/" + _data.getGameName() + ".score"};
    std::string line;
    std::string name = username;
    int actual_scores = _data.getScores()["Size"];
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

void Snake::endGame([[maybe_unused]] vector2f headPos, const std::string &username)
{
    SaveScore(username);
    _data.setGameOver(true);
}

Arcade::IGameData &Snake::getGameData() const
{
    return (Arcade::IGameData&)_data;
}
