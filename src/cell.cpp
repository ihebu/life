#include <vector>

#include "cell.hpp"

#define BLACK sf::Color::Black
#define WHITE sf::Color::White

int Cell::getAliveNeighbours()
{
    int result = 0;

    for (auto &n : neighbours)
    {
        result += n->state == State::ALIVE;
    }

    return result;
}

void Cell::setNextState()
{
    int count_neighbours = getAliveNeighbours();

    bool condition = (count_neighbours == 3) || (state == State::ALIVE && count_neighbours == 2);

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

void Cell::addNeighbours(std::vector<Cell *> &neighbours_list)
{
    neighbours = neighbours_list;
}

Cell::Cell(int cell_size, int x_pos, int y_pos)
{
    sf::Vector2f size(cell_size, cell_size);
    shape.setSize(size);

    sf::Vector2f position(y_pos * cell_size, x_pos * cell_size);
    shape.setPosition(position);

    // Randomly set the initial state of the cell, dead or alive
    state = rand() & 1 ? State::DEAD : State::ALIVE;
}
