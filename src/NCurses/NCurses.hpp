/*
** EPITECH PROJECT, 2023
** Project
** File description:
** NCurses
*/

#ifndef NCurses_HPP
#define NCurses_HPP

#include <ncurses.h>

#include "IDisplayModule.hpp"
#include "NCursesUtils.hpp"

class NCurses : Arcade::IDisplay {
    public:
        NCurses();
        ~NCurses() override;

        NCursesUtils _ = NCursesUtils::getInstance();

        void init();
        void exit();

        std::vector <Arcade::Key> getPressedKeys() override;
        void render(Arcade::IGameData &gameData) override;
        void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
            int selectedGame, int selectedDisplay, const Arcade::ControlMap &controls,
            const std::string &username, const std::string &bestScoreUsername, int bestScore) override;
        void DrawInformations(Arcade::IGameData &gameData, const std::pair<int, int> &mapSize);

private:
        std::map<int, int> _keymap = {
                {259, Arcade::Key::Up},
                {258, Arcade::Key::Down},
                {261, Arcade::Key::Right},
                {260, Arcade::Key::Left},
                {27, Arcade::Key::Escape},
                {32, Arcade::Key::Space},
                {10, Arcade::Key::Enter},
                {263, Arcade::Key::Backspace},
                {127, Arcade::Key::Backspace},
                {8, Arcade::Key::Backspace},
                {65, Arcade::Key::A},
                {66, Arcade::Key::B},
                {67, Arcade::Key::C},
                {68, Arcade::Key::D},
                {69, Arcade::Key::E},
                {70, Arcade::Key::F},
                {71, Arcade::Key::G},
                {72, Arcade::Key::H},
                {73, Arcade::Key::I},
                {74, Arcade::Key::J},
                {75, Arcade::Key::K},
                {76, Arcade::Key::L},
                {77, Arcade::Key::M},
                {78, Arcade::Key::N},
                {79, Arcade::Key::O},
                {80, Arcade::Key::P},
                {81, Arcade::Key::Q},
                {82, Arcade::Key::R},
                {83, Arcade::Key::S},
                {84, Arcade::Key::T},
                {85, Arcade::Key::U},
                {86, Arcade::Key::V},
                {87, Arcade::Key::W},
                {88, Arcade::Key::X},
                {89, Arcade::Key::Y},
                {90, Arcade::Key::Z},
                {97, Arcade::Key::A},
                {98, Arcade::Key::B},
                {99, Arcade::Key::C},
                {100, Arcade::Key::D},
                {101, Arcade::Key::E},
                {102, Arcade::Key::F},
                {103, Arcade::Key::G},
                {104, Arcade::Key::H},
                {105, Arcade::Key::I},
                {106, Arcade::Key::J},
                {107, Arcade::Key::K},
                {108, Arcade::Key::L},
                {109, Arcade::Key::M},
                {110, Arcade::Key::N},
                {111, Arcade::Key::O},
                {112, Arcade::Key::P},
                {113, Arcade::Key::Q},
                {114, Arcade::Key::R},
                {115, Arcade::Key::S},
                {116, Arcade::Key::T},
                {117, Arcade::Key::U},
                {118, Arcade::Key::V},
                {119, Arcade::Key::W},
                {120, Arcade::Key::X},
                {121, Arcade::Key::Y},
                {122, Arcade::Key::Z}
                };
};


#endif /* !NCurses_HPP */
