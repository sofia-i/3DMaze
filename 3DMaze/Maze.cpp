//
//  Maze.cpp
//  3DMaze
//
//  Created by SI on 3/9/21.
//

#include <stdio.h>
#include "Maze.h"
#include <string>
#include <sstream>

using namespace std;

Maze::Maze(size_t nRows, size_t nCols, size_t nLayers, string s) {
    rows = nRows;
    cols = nCols;
    layers = nLayers;
    istringstream inss(s);
    
    maze = new size_t** [layers];
    
    for(size_t i = 0; i < layers; ++i) {
        maze[i] = new size_t* [rows];
        for(size_t r = 0; r < rows; ++r) {
            maze[i][r] = new size_t[cols];
            for(size_t c = 0; c < cols; ++c) {
                inss >> maze[i][r][c];
            }
        }
    }
}


bool Maze::find_maze_path(int i, int r, int c) {
    //if out of bounds, return false
    if((i < 0) || (i >= layers) || (r < 0) || (r >= rows) || (c < 0) || (c >= cols)) {
        return false;
    }
    //if blocked, return false
    if(maze[i][r][c] != OPEN) {
        return false;
    }
    
    //if not blocked or out of bounds, assume path
    maze[i][r][c] = PATH;
    
    //if exit, return true
    if(i == layers - 1 && r == rows - 1 && c == cols - 1) {
        maze[i][r][c] = EXIT;
        return true;
    }
    
    //check adjacent cells (recursive case). go through each individually, assign value if call comes back true
    if(find_maze_path(LEFT)) {
        maze[i][r][c] = NEXT_LEFT;
        return true;
    }
    else if(find_maze_path(RIGHT)) {
        maze[i][r][c] = NEXT_RIGHT;
        return true;
    }
    else if(find_maze_path(UP)) {
        maze[i][r][c] = NEXT_UP;
        return true;
    }
    else if(find_maze_path(DOWN)) {
        maze[i][r][c] = NEXT_DOWN;
        return true;
    }
    else if(find_maze_path(OUT)) {
        maze[i][r][c] = NEXT_OUT;
        return true;
    }
    else if(find_maze_path(IN)) {
        maze[i][r][c] = NEXT_IN;
        return true;
    }
    
    //if no adjacent cells open, mark visited and return false
    else {
        maze[i][r][c] = VISITED;
        return false;
    }
}


std::string Maze::toString() const {
    string output;
    for(size_t i = 0; i < layers; ++i) {
        //Label each layer
        output.append("Layer " + to_string(i + 1) + "\n");
        
        //traverse each rows
        for(size_t r = 0; r < rows; ++r) {
            //traverse each entry, append to string corresponding values
            for(size_t c = 0; c < cols; ++c) {
                output.append(" ");
                size_t value = maze[i][r][c];
                switch (value) {
                    case OPEN:
                        output.append("_");
                        break;
                    case VISITED:
                        output.append("*");
                        break;
                    case BLOCKED:
                        output.append("X");
                        break;
                    case PATH:
                        output.append("*");
                        break;
                    case NEXT_LEFT:
                        output.append("L");
                        break;
                    case NEXT_RIGHT:
                        output.append("R");
                        break;
                    case NEXT_UP:
                        output.append("U");
                        break;
                    case NEXT_DOWN:
                        output.append("D");
                        break;
                    case NEXT_OUT:
                        output.append("O");
                        break;
                    case NEXT_IN:
                        output.append("I");
                        break;
                    case EXIT:
                        output.append("E");
                        break;
                }
                //if it's the last column, add an endline. else a space
                if(c == cols - 1) {
                    output.append("\n");
                }
            }
        }
    }
    return output;
}
