#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

enum class State
{
    DEAD,
    ALIVE
};

class Cell
{
private:
    sf::RectangleShape shape;
    std::vector<Cell *> neighbors;

    State state, next_state;

public:
    void setNextState();

    void applyNextState();

    void draw(sf::RenderWindow *window);

    void addNeighbors(std::vector<Cell *> &neighbors_list);

    Cell(int size, int x_position, int y_position);
};