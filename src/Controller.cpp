#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include "Controller.h"
#include "Grid.h"

using namespace std;
typedef pair<int, int> coord2D;

Controller::Controller(Grid grid) {
    this->grid = grid;
}

void Controller::prune(){
    for(int i = 0; i < grid.sizeH; i++){
        for(int j = 0; j<grid.sizeV;j++){
            if (grid.isTrap(i,j)){
               grid.toWall(i,j);
               if(grid.thereIsWayOut(i,j)){
                   int k = i; int l = j;
                   coord2D door = grid.getDoor(i,j);
                   k = door.first; l = door.second;
                   while(grid.isTrap(k,l)){
                       grid.printGrid();
                       grid.toWall(k,l);
                       if(grid.thereIsWayOut(k,l)){
                           coord2D door = grid.getDoor(k,l);
                           k = door.first; l = door.second;
                       }
                   }
                   
               }
               
            }
        }
    }
    grid.printGrid();
}

