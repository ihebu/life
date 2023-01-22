#include <vector>

#include "cell.hpp"

#define BLACK sf::Color::Black
#define WHITE sf::Color::White

void Cell::setNextState()
{
    // Number of neighbor cells alive
    int count = 0;

    for (auto &n : neighbors)
    {
        count += n->state == State::ALIVE;
    }

    bool condition = (count == 3) || (state == State::ALIVE && count == 2);

    next_state = condition ? State::ALIVE : State::DEAD;
}

void Cell::applyNextState()
{
    state = next_state;
}

void Cell::draw(sf::RenderWindow *window)
{
    auto color = state == State::ALIVE ? WHITE : BLACK;
    shape.setFillColor(color);
    window->draw(shape);
}

void Cell::addNeighbors(std::vector<Cell *> &neighbors_list)
{
    neighbors = neighbors_list;
}

Cell::Cell(int cell_size, int x_pos, int y_pos)
{
    sf::Vector2f size(cell_size, cell_size);
    shape.setSize(size);

    sf::Vector2f position(x_pos * cell_size, y_pos * cell_size);
    shape.setPosition(position);

    // Randomly set the initial state of the cell, dead or alive
    state = rand() & 1 ? State::DEAD : State::ALIVE;
}
