/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-noa.trachez
** File description:
** IDisplayModule.hpp
*/

#ifndef IDISPLAY_HPP_
    #define IDISPLAY_HPP_
#include "IGameModule.hpp"
#include <fstream>
#include <sstream>

namespace Arcade {
    class IDisplay;
};

/**
 * @brief Interface for Display Libraries.
 *
 * This interface is used to create a display library.
 * The display library is used to render the menu and the selected game.
 * A display library must export two symbols : "createDisplay" and "destroyDisplay".
 */
class Arcade::IDisplay {
public:
    virtual ~IDisplay() = default;

    /**
     * @brief Get the pressed keys.
     *
     * This method return a list of Arcade::Key enum
     * @return A vector containing all the pressed keys by the user.
     */
    virtual std::vector<Key> getPressedKeys() = 0;

    /**
     * @brief Renders the game.
     *
     * This method is continuously called to render the game.
     * It takes as parameter a IGameData object, containing all the data needed to render the game and any useful information.
     * Textures are loaded from the path: ASSETS + GAME_NAME + "/" + LIB_NAME + "/" + textureName
     * @param gameData IGameData containing the entities, scores, controls, mapSize and gameOver.
     */
    virtual void render(IGameData &gameData) = 0;

    /**
     * @brief Renders the menu.
     *
     * @param games The list the game libraries
     * @param graphics The list the graphics libraries
     * @param selectedGame The index of the selected game
     * @param selectedDisplay The index of the selected display
     * @param controls A map, associating a key with string type to an action with a string type too
     */
    virtual void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                            int selectedGame, int selectedDisplay, const ControlMap &controls,
                            const std::string &username, const std::string &bestScoreUsername, int bestScore) = 0;
};

#endif /* !IDISPLAY_HPP_ */