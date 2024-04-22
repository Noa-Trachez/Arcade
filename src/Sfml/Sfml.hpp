/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Sfml
*/

#ifndef Sfml_HPP
#define Sfml_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "IDisplayModule.hpp"

class Sfml : Arcade::IDisplay {
    public:
        Sfml();
        ~Sfml() override;

        void init();
        void exit();

        std::vector <Arcade::Key> getPressedKeys() override;
        void render(Arcade::IGameData &gameData) override;
        void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
            int selectedGame, int selectedDisplay, const Arcade::ControlMap &controls,
            const std::string &username, const std::string &bestScoreUsername, int bestScore) override;
        void DrawTextAtPosition(const char *string, int x, int y, sf::Color color);
        void DrawTextList(const std::vector<std::string> &lib, int selectedLib, int separator, int y, int factor);
    void DrawInformations(Arcade::IGameData &gameData, std::string gameName);
        int GetTextSize(const std::string &text);
        void DrawBox(int x, int y, int width, int height);

private:
        sf::RenderWindow _window{};
        sf::Event _event{};
        sf::Font _font{};
        sf::Text _text{};
		sf::RectangleShape _mapBorder{};
        std::map<std::string, sf::Sprite> _sprites{};
        std::map<std::string, sf::Texture> _texture{};

         std::map<int, int> _keymap = {
                {Arcade::Key::Up,     Arcade::Key::Up},
                {Arcade::Key::Down,   Arcade::Key::Down},
                {Arcade::Key::Right,  Arcade::Key::Right},
                {Arcade::Key::Left,   Arcade::Key::Left},
                {Arcade::Key::Escape, Arcade::Key::Escape},
                {Arcade::Key::Space,  Arcade::Key::Space},
                {Arcade::Key::Enter,  Arcade::Key::Enter},
                {Arcade::Key::Backspace,  Arcade::Key::Backspace},
                {Arcade::Key::A, Arcade::Key::A},
                {Arcade::Key::B, Arcade::Key::B},
                {Arcade::Key::C, Arcade::Key::C},
                {Arcade::Key::D, Arcade::Key::D},
                {Arcade::Key::E, Arcade::Key::E},
                {Arcade::Key::F, Arcade::Key::F},
                {Arcade::Key::G, Arcade::Key::G},
                {Arcade::Key::H, Arcade::Key::H},
                {Arcade::Key::I, Arcade::Key::I},
                {Arcade::Key::J, Arcade::Key::J},
                {Arcade::Key::K, Arcade::Key::K},
                {Arcade::Key::L, Arcade::Key::L},
                {Arcade::Key::M, Arcade::Key::M},
                {Arcade::Key::N, Arcade::Key::N},
                {Arcade::Key::O, Arcade::Key::O},
                {Arcade::Key::P, Arcade::Key::P},
                {Arcade::Key::Q, Arcade::Key::Q},
                {Arcade::Key::R, Arcade::Key::R},
                {Arcade::Key::S, Arcade::Key::S},
                {Arcade::Key::T, Arcade::Key::T},
                {Arcade::Key::U, Arcade::Key::U},
                {Arcade::Key::V, Arcade::Key::V},
                {Arcade::Key::W, Arcade::Key::W},
                {Arcade::Key::X, Arcade::Key::X},
                {Arcade::Key::Y, Arcade::Key::Y},
                {Arcade::Key::Z, Arcade::Key::Z}
        };
};


#endif /* !Sfml_HPP */
