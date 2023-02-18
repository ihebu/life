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
    std::vector<Cell *> neighbours;

    State state, next_state;

    int getAliveNeighbours();

public:
    void setNextState();

    void applyNextState();

    void draw(sf::RenderWindow *window);

    void addNeighbours(std::vector<Cell *> &neighbors_list);

    Cell(int size, int x_position, int y_position);
};