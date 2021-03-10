#include "snake.h"

Position::Position()
    : x(0), y(0) {}

Position::Position(int col,int row)
    : x(col), y(row) {}
    
SnakeGame::SnakeGame()
    : eats_food(0), score(0), speed(100000),
    snake_body('o'), edge('#'), food_char('*')
{
    // ncurses setup
    initscr();
    nodelay(stdscr,true);
    noecho();
    curs_set(0);
    getmaxyx(stdscr, max_height, max_width);
    snake.push_back(Position(max_width / 2, max_height / 2 + 1));
    input = LEFT;
    srand(time(NULL));
    set_food_position();
    
    // Print controls. mvprintw is similar to printf but moves to specified row, column before printing
    mvprintw(0, max_width / 2 - 12, "Snake by Barinder Matharu\n\nControls: w = UP, a = LEFT, s = DOWN, d = RIGHT, l = LEAVE"); 
    
    // Prints board
    for (int i = 0; i < max_width; i++)
    {
        mvaddch(4, i, edge); // char analogue to mvprintw
        mvaddch(max_height - 3, i, edge);
    }
    for (int i = 4; i < max_height - 3; i++)
    {
        mvaddch(i, 0, edge);
        mvaddch(i, max_width - 1, edge);
    }

    // Prints snake, scorecard, and food
    mvaddch(snake[0].y, snake[0].x, snake_body);
    mvprintw(max_height - 1, 0, "Score: %d", score);
    mvaddch(food.y, food.x, food_char);
    refresh();
    }

SnakeGame::~SnakeGame()
{
    // ncurses cleanup
    nodelay(stdscr, false);
    getch();
    endwin();
}

// Places food randomly on board. If food placed on snake or out-of-bounds, retry until valid.
void SnakeGame::set_food_position()
{
    while(1)
    {
        int tmpx = rand() % max_width + 1;
        int tmpy = rand() % max_height + 5;
        bool invalid_placement = false;
        for (int i = 0; i < snake.size(); i++)
        {
            if (snake[i].x == tmpx && snake[i].y == tmpy)
            {
                invalid_placement = true;
                break;
            }
        }
        if (tmpx >= max_width - 1 || tmpy >= max_height - 3 || invalid_placement) continue;
        food.x = tmpx;
        food.y = tmpy;
        break;
    }
    mvaddch(food.y, food.x, food_char);
    refresh();
}

bool SnakeGame::collision()
{
    // Checks for collisions with edges
    if (snake[0].x == 0 || snake[0].x == max_width - 1 || snake[0].y == 4 || snake[0].y == max_height - 3) return true;
    
    // Checks for collisions with snake body
    for (int i = 2; i < snake.size(); i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) return true;
    }
    
    // Checks if snake eats food, and performs necessary updates
    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        eats_food = true;
        set_food_position();
        score++;
        mvprintw(max_height - 1, 0, "Score: %d", score);
        if((score % 10) == 0) speed -= 10000; // "speed" in microseconds, so lower is faster
    }
    else
    {
        eats_food = false;
    }
    return false;
}

void SnakeGame::move_snake()
{
    // Gets input from user
    int tmp = getch();
    switch(tmp)
    {
        case 'a':
            if(input != RIGHT)
                input = LEFT;
            break;
        case 'w':
            if(input != DOWN)
                input = UP;
            break;
        case 's':
            if(input != UP)
                input = DOWN;
            break;
        case 'd':
            if(input != LEFT)
                input = RIGHT;
            break;
        case 'l':
            input = LEAVE;
            break;
    }
    
    // If food is not eaten, then tail of snake pops off when moving
    if (!eats_food)
    {
        mvprintw(snake[snake.size()-1].y, snake[snake.size()-1].x, " ");
        refresh();
        snake.pop_back();
    }
    
    // Add element to head of snake depending on user input, and print
    if (input == LEFT)
    {
        snake.insert(snake.begin(), Position(snake[0].x - 1, snake[0].y));
    }
    else if (input == RIGHT){
        snake.insert(snake.begin(), Position(snake[0].x + 1, snake[0].y));
    }
    else if (input == UP){
        snake.insert(snake.begin(), Position(snake[0].x, snake[0].y - 1));
    }
    else if (input == DOWN){
        snake.insert(snake.begin(), Position(snake[0].x, snake[0].y + 1));
    }
    mvaddch(snake[0].y, snake[0].x, snake_body);
    refresh();
}

void SnakeGame::play()
{
    while(1)
    {
        if(collision())
        {
            mvprintw(max_height / 2 + 1, max_width / 2 - 24, "Gameover. You scored %d. Press any key to leave.", score);
            refresh();
            break;
        }
        move_snake();
        if(input == LEAVE)
        {
            mvprintw(max_height / 2 + 1, max_width / 2 - 23, "Thank you for playing! Press any key to leave.");
            refresh();
            break;
        }
        usleep(speed);
    }
}