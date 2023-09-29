//
//  Maze.h
//  3DMaze
//
//  Created by SI on 3/8/21.
//

#ifndef Maze_h
#define Maze_h

#include "MazeInterface.h"
#include <string>

using namespace std;

enum cells { OPEN = 0, BLOCKED = 1, VISITED = 2, PATH = 3, NEXT_LEFT = 4, NEXT_RIGHT = 5, NEXT_UP = 6, NEXT_DOWN = 7, NEXT_OUT = 8, NEXT_IN = 9, EXIT = 10 };
#define UP      i,r-1,c
#define DOWN    i,r+1,c
#define LEFT    i,r,c-1
#define RIGHT   i,r,c+1
#define IN      i+1,r,c
#define OUT     i-1,r,c

class Maze : public MazeInterface {
private:
    size_t*** maze;
    size_t rows;
    size_t cols;
    size_t layers;
    
public:
    Maze() {
        rows = 0;
        cols = 0;
        layers = 0;
        maze = NULL;
    }
    
    Maze(size_t nRows, size_t nCols, size_t nLayers, string s);
    
    ~Maze() {
        for(size_t i = 0; i < layers; ++i) {
            for(size_t r = 0; r < rows; ++r) {
                delete[] maze[i][r];
            }
        }
        for(size_t i = 0; i < layers; ++i) {
            delete[] maze[i];
        }
        delete[] maze;
    }
    
    
    void setValue(int height, int width, int layer, int value) {
        maze[layer][height][width] = value;
    }
    
    bool find_maze_path() {
        return find_maze_path(0,0,0);
    }
    
    bool find_maze_path(int i, int r, int c);
    
    virtual std::string toString() const;
    
    friend ostream& operator<<(ostream& os, Maze& maze1) {
        os << maze1.toString();
        return os;
    }
    
};


#endif /* Maze_h */
