#pragma once
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct Position
{
    int x,y;
    Position();
    Position(int col, int row);
};

class SnakeGame
{
    bool eats_food;
    int score,speed,max_width,max_height;
    char snake_body,edge,food_char;
    enum {LEAVE, UP, DOWN, LEFT, RIGHT} input;
    Position food;
    std::vector<Position> snake;

    void set_food_position();
    bool collision();
    void move_snake();
    
public:
    SnakeGame();
    ~SnakeGame();
    void play();
};