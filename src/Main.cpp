/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Main
*/

#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade [libPath]" << std::endl;
        return 84;
    }

    Core core(av[1]);
    if (core.ErrorEngine()) return 84;
    core.RunArcade();
    return 0;
}
