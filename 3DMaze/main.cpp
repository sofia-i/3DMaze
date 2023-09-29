//
//  main.cpp
//  3DMaze
//
//  Created by SI on 3/8/21.
//

//memory leak check
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Maze.h"

using namespace std;

int main(int argc, const char * argv[]) {
    VS_MEM_CHECK
    
    //Open Input and Output files
    //cout << argv[1] << endl;
    ifstream in(argv[1]);
    if(!in) {
        cout << "unable to open file" << endl;
        return 1;
    }
    ostream& out = (argc > 2) ? *(new ofstream(argv[2])) : cout;
    if(!out) {
        return 2;
    }
    
    size_t height;
    size_t width;
    size_t numLayers;
    string line;
    
    getline(in, line);
    //out << line;
    istringstream inss(line);
    inss >> height;
    inss >> width;
    inss >> numLayers;
    
    string fullInput;
    
    while(getline(in, line)) {
        fullInput.append(line+"\n");
    }
    
    Maze maze = Maze(height, width, numLayers, fullInput);
    //input maze, height, width, and number of layers
    
    out << "Solve Maze:" << endl;
    out << maze << endl;
    
    if(maze.find_maze_path()) {
        out << "Solution:" << endl;
        out << maze;
    }
    else {
        out << "No Solution Exists!" << endl;
    }
    
    //close files and free memory
    in.close();
    if(&out != &cout) delete(&out);

    return 0;
}
