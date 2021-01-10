#include <SFML/Graphics.hpp>

#define WIDTH 1000
#define HEIGHT 1000
#define ROWS 100
#define COLS 100
#define CELL_W 10
#define CELL_H 10

#define FOR for (int i = 0; i < ROWS; i++) for (int j = 0; j < COLS; j++)

sf::RectangleShape cells[ROWS][COLS];
bool cur[ROWS][COLS], next[ROWS][COLS];

/*
Initialize the grid randomly with dead and live cells 
*/
void init()
{
    FOR
    {
        double s = (rand() % 1000) / 1000.0;
        if (s <= 0.5)
            cur[i][j] = 1;
        cells[i][j].setSize(sf::Vector2f(CELL_W, CELL_H));
        cells[i][j].setPosition(sf::Vector2f(i * CELL_H, j * CELL_W));
    }
}

/*
Update the colors of cells
if a cell is live : it's colored in white 
otherwise it's colored in black
*/
void colorCells()
{
    FOR
    {
        auto color = cur[i][j] ? sf::Color::White : sf::Color::Black;
        cells[i][j].setFillColor(color);
    }
}

/*
Calculate the number of neighbors of a given cell
if a cell is located at the borders, then cells from the opposite 
side of the grid are considered neighbors
*/
int neighbors(int i, int j)
{
    int ans = 0;
    for (int k : {-1, 0, 1})
        for (int l : {-1, 0, 1})
        {
            int di = i + k;
            int dj = j + l;
            di = (di + ROWS) % ROWS;
            dj = (dj + COLS) % COLS;
            if ((k != 0 || l != 0) && cur[di][dj])
                ans++;
        }
    return ans;
}

/*
Update the grid based on original rules of the game of life :
Any live cell with two or three live neighbours lives on to the next generation.
Any dead cell with exactly three live neighbours becomes a live cell.
Otherwise the cells remains or becomes dead
*/
void update()
{
    FOR
    {
        int n = neighbors(i, j);
        if ((cur[i][j] == 1 && (n == 2 || n == 3)) || (cur[i][j] == 0 && n == 3))
            next[i][j] = 1;
        else
            next[i][j] = 0;
    }
    FOR cur[i][j] = next[i][j];
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game Of Life");
    window.setFramerateLimit(20);

    init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // If R is pressed, Reset the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            init();

        // If Q is pressed, Quit the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            break;

        window.clear();
        colorCells();
        FOR window.draw(cells[i][j]);
        window.display();
        update();
    }
}