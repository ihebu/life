#include <fstream>
#include <utility>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>
#include "cell.hpp"

class Game
{
private:
    sf::RenderWindow *window;
    std::vector<Cell> cells;

    std::unordered_map<std::string, std::string> config;

    void parseConfig()
    {
        std::ifstream config_file("config.ini");
        std::string line;

        while (std::getline(config_file, line))
        {
            if (line.empty() || line[0] == '[')
            {
                continue;
            }

            std::size_t separator = line.find('=');

            if (separator != std::string::npos)
            {
                std::string key = line.substr(0, separator);
                std::string value = line.substr(separator + 1);

                config[key] = value;
            }
        }
    }

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

            std::vector<Cell *> neighbours;

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

                    neighbours.push_back(&cells[j]);
                }
            }

            cells[i].addNeighbours(neighbours);
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
        parseConfig();

        const int board_width = stoi(config["board_width"]);
        const int board_height = stoi(config["board_height"]);
        const int cell_size = stoi(config["cell_size"]);
        const int frame_limit = stoi(config["frame_limit"]);
        const std::string window_title = config["window_title"];

        const int rows = board_height / cell_size;
        const int cols = board_width / cell_size;

        initializeCells(cell_size, rows, cols);

        sf::VideoMode mode(board_width, board_height);
        window = new sf::RenderWindow(mode, window_title);

        window->setFramerateLimit(frame_limit);
    }

    void runMainLoop()
    {
        while (window->isOpen())
        {
            sf::Event event;

            // Close the windows if the exit button is pressed
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