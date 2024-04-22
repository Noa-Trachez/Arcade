/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-noa.trachez
** File description:
** IGameModule.hpp
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <string>

/**
 * @brief Namespace containing of all the arcade classes.
 */
namespace Arcade {

    /**
     * @brief Enum of all the possible keys that can be pressed.
     */
    enum Key {
        Unknown = -1, ///< Unhandled key
        A       = 0,  ///< The A key
        B,            ///< The B key
        C,            ///< The C key
        D,            ///< The D key
        E,            ///< The E key
        F,            ///< The F key
        G,            ///< The G key
        H,            ///< The H key
        I,            ///< The I key
        J,            ///< The J key
        K,            ///< The K key
        L,            ///< The L key
        M,            ///< The M key
        N,            ///< The N key
        O,            ///< The O key
        P,            ///< The P key
        Q,            ///< The Q key
        R,            ///< The R key
        S,            ///< The S key
        T,            ///< The T key
        U,            ///< The U key
        V,            ///< The V key
        W,            ///< The W key
        X,            ///< The X key
        Y,            ///< The Y key
        Z,            ///< The Z key
        Num0,         ///< The 0 key
        Num1,         ///< The 1 key
        Num2,         ///< The 2 key
        Num3,         ///< The 3 key
        Num4,         ///< The 4 key
        Num5,         ///< The 5 key
        Num6,         ///< The 6 key
        Num7,         ///< The 7 key
        Num8,         ///< The 8 key
        Num9,         ///< The 9 key
        Escape,       ///< The Escape key
        LControl,     ///< The left Control key
        LShift,       ///< The left Shift key
        LAlt,         ///< The left Alt key
        LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (macOS), ...
        RControl,     ///< The right Control key
        RShift,       ///< The right Shift key
        RAlt,         ///< The right Alt key
        RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (macOS), ...
        Menu,         ///< The Menu key
        LBracket,     ///< The [ key
        RBracket,     ///< The ] key
        Semicolon,    ///< The ; key
        Comma,        ///< The , key
        Period,       ///< The . key
        Apostrophe,   ///< The ' key
        Slash,        ///< The / key
        Backslash,    ///< The \ key
        Grave,        ///< The ` key
        Equal,        ///< The = key
        Hyphen,       ///< The - key (hyphen)
        Space,        ///< The Space key
        Enter,        ///< The Enter/Return keys
        Backspace,    ///< The Backspace key
        Tab,          ///< The Tabulation key
        PageUp,       ///< The Page up key
        PageDown,     ///< The Page down key
        End,          ///< The End key
        Home,         ///< The Home key
        Insert,       ///< The Insert key
        Delete,       ///< The Delete key
        Add,          ///< The + key
        Subtract,     ///< The - key (minus, usually from numpad)
        Multiply,     ///< The * key
        Divide,       ///< The / key
        Left,         ///< Left arrow
        Right,        ///< Right arrow
        Up,           ///< Up arrow
        Down,         ///< Down arrow
        Numpad0,      ///< The numpad 0 key
        Numpad1,      ///< The numpad 1 key
        Numpad2,      ///< The numpad 2 key
        Numpad3,      ///< The numpad 3 key
        Numpad4,      ///< The numpad 4 key
        Numpad5,      ///< The numpad 5 key
        Numpad6,      ///< The numpad 6 key
        Numpad7,      ///< The numpad 7 key
        Numpad8,      ///< The numpad 8 key
        Numpad9,      ///< The numpad 9 key
        F1,           ///< The F1 key
        F2,           ///< The F2 key
        F3,           ///< The F3 key
        F4,           ///< The F4 key
        F5,           ///< The F5 key
        F6,           ///< The F6 key
        F7,           ///< The F7 key
        F8,           ///< The F8 key
        F9,           ///< The F9 key
        F10,          ///< The F10 key
        F11,          ///< The F11 key
        F12,          ///< The F12 key
        F13,          ///< The F13 key
        F14,          ///< The F14 key
        F15,          ///< The F15 key
        Pause,        ///< The Pause key
        KeyCount,     ///< Keep last -- the total number of keyboard keys
    };

    typedef std::unordered_map<std::string, std::string> ControlMap;

    /**
     * @brief Interface of an entity.
     *
     * An entity is an object that can be displayed on the screen.
     * Multiple entities can be displayed by adding a position to the entity.
     */
    class IEntity {
    public:
        /**
         * @brief Gets all the positions of the entity.
         * @return A vector containing all the positions of the entity.
        */
        virtual std::vector<std::pair<float, float>> getPosition() const = 0;

        /**
         * @brief Gets the size of the entity.
         * @return A pair of float representing the size of the entity.
        */
        virtual std::pair<float, float> getSize() const = 0;

        /**
         * @brief Gets the texture name of the entity.
         * @return The entity texture name.
         */
        virtual std::string getTexture() const = 0;

        /**
         * @brief Gets the rotation of the entity.
         * @return The entity rotation in degrees.
         */
        virtual float getRotation() const = 0;
    };

    /**
     * @brief Interface of the game data.
     *
     * This interface is used to get the data of the game.
     * Data are send to the display through the core to be interpreted and displayed.
     */
    class IGameData {
    public:
        /**
         * @brief Gets the scores of the game.
         * @return A map of string and int. The key is the name of the player and the value is the score of the player.
         */
        virtual std::map<std::string, int> getScores() const = 0;

        /**
         * @brief Gets the name of the game.
         * @return The name of the game.
         */
        virtual std::string getGameName() const = 0;

        /**
         * @brief Gets all game entities to display.
         *
         * Array of every entity active in the game at the moment.
         * @return
         */
        virtual std::vector<std::shared_ptr<Arcade::IEntity>> &getEntities() = 0;

        /**
         * @brief Gets the size of the map.
         * @return The size of the map in terms of cell.
         */
        virtual std::pair<int, int> getMapSize() const = 0;

        /**
         * @brief Gets the controls of the game.
         *
         * Contains the controls of the game needed to play.
         * @return A map of name => control.
         */
        virtual const ControlMap &getControls() const = 0;

        /**
         * @brief Returns either the game is over or not.
         * @return True if the game is over, false otherwise.
         */
        virtual bool isGameOver() const = 0;
    };

    /**
     * @brief Interface of the game.
     *
     * This interface is used to interact with the game.
     * It contains the three main methods for the game to work.
     */
    class IGame {
    public:
        virtual ~IGame() = default;

        /**
         * @brief Handles the keys pressed by the user.
         *
         * This method receives the keys pressed by the user to handle them.
         * @param pressedKeys A vector of keys get from the display.
         */
        virtual void handleKeys(const std::vector<Key> &pressedKeys) = 0;

        /**
         * @brief Updates the game depending on a game tick (clock).
         *
         * This method is called continuously by the core to update the game.
         * @param username The username of the player.
         */
        virtual void update(const std::string &username) = 0;

        /**
         * @brief Gets the game data.
         * @return An instance of IGameData containing all needed information.
         */
        virtual IGameData &getGameData() const = 0;
    };
};

#endif /* !IGAME_HPP_ */
