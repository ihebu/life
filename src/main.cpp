#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>
#include "cell.hpp"

class Game
{
private:
    sf::RenderWindow *window;
    std::vector<Cell> cells;

    void initializeCells(int cell_size, int rows, int cols)
    {
        for (int i = 0; i < rows * cols; i++)
        {
            int x = i / cols;
            int y = i % cols;
            cells.emplace_back(cell_size, x, y);
        }

        for (int i = 0; i < rows * cols; i++)
        {

            int x = i / cols;
            int y = i % cols;

            std::vector<Cell *> neighbors;

            for (int _x = x - 1; _x <= x + 1; _x++)
            {
                for (int _y = y - 1; _y <= y + 1; _y++)
                {
                    if (_x == x && _y == y)
                    {
                        continue;
                    }

                    int new_x = (_x + rows) % rows;
                    int new_y = (_y + cols) % cols;

                    int j = new_x * cols + new_y;

                    neighbors.push_back(&cells[j]);
                }
            }

            cells[i].addNeighbors(neighbors);
        }
    }

    void renderCells()
    {
        for (auto &cell : cells)
        {
            cell.draw(window);
        }
    }

    void updateCellsState()
    {
        for (auto &cell : cells)
        {
            cell.setNextState();
        }
        for (auto &cell : cells)
        {
            cell.applyNextState();
        }
    }

public:
    Game()
    {
        const int width = 1000;
        const int height = 1000;
        const int cell_size = 10;
        const int rows = height / cell_size;
        const int cols = width / cell_size;

        initializeCells(cell_size, rows, cols);

        const std::string title = "Conway's Game Of Life";
        sf::VideoMode mode(width, height);
        window = new sf::RenderWindow(mode, title);

        const int limit = 30;
        window->setFramerateLimit(limit);
    }

    void runMainLoop()
    {
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }
            }

            // Update game stats
            updateCellsState();

            // Clear the screen
            window->clear();

            // Draw objects
            renderCells();

            // Display the window
            window->display();
        }
    }
};

int main()
{
    std::srand(std::time(nullptr));

    Game game;
    game.runMainLoop();
}