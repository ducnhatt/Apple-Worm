#ifndef POSITION_H
#define POSITION_H

#include <stdexcept>


enum Direction {
    UP = 0, DOWN, LEFT, RIGHT, NO
};

int degrees = 0;
SDL_RendererFlip flipType = SDL_FLIP_NONE;

struct Position
{
    int x;
    int y;

    Position(int a, int b) : x(a), y(b) {}
    Position move(Direction direction){
    	switch(direction) { 
    		case UP: return Position(x, y - 1);
    		case DOWN: return Position(x, y + 1);
    		case LEFT: return Position(x - 1, y);
    		case RIGHT: return Position(x + 1, y);
            case NO:return Position(x, y);
    		// default: throw std::invalid_argument("Unknown direction");
		}
        return Position(x, y);
    }

    bool isInsideBox(int left, int top, int width, int height) const {
        return x >= left && x < left+width && y >= top && y < top+height;
    }

    bool operator==(Position p) const {
        return x == p.x && y == p.y;
    }
};

#endif // POSITION_H