#include "Controller.h"

Controller::Controller() {}

void Controller::loadFile(string inputFile){
    ifstream infile (inputFile);
    int sizeH, sizeV;
    string line;
    istringstream iss;

    if (infile.is_open()){
      nextLine(infile, line) >> sizeH >> sizeV;
      grid = new Grid(sizeH, sizeV);
      
      int nval;
      iss = nextLine(infile, line);
      iss >> nval;

      for (int i = 0; i < nval; i++) {
         grid->addWall(getXY(iss));
      }
      iss = nextLine(infile, line);
      iss >> nval;
      for (int i = 0; i < nval; i++) {
         grid->addBox(getXY(iss));
      }
      iss = nextLine(infile, line);
      iss >> nval;
      for (int i = 0; i < nval; i++) {
         grid->addStorage(getXY(iss));
      }
      iss = nextLine(infile, line);

      grid->setPlayerPosition(getXY(iss));

      grid->printGrid();
      loaded = true;
      }
}

void Controller::prune(){
    for(int i = 0; i < grid->sizeH; i++){
        for(int j = 0; j<grid->sizeV;j++){
            if (grid->isTrap(i,j)){
               grid->toWall(i,j);
               pruneHallway(i,j);
            }
        }
    }
    grid->printGrid();
}

void Controller::solve(){
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    solution = new State(grid);
    solution = Algorithms::AStar(solution);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "ELAPSED TIME: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " miliseconds"  <<endl;
    if(!solution) throw invalid_argument( "SOLUTION WAS NOT FOUND" );
    cout << "SOLUTION FOUND" << endl;
    }

void Controller::printOptimalSolution(){
    vector<State*> moves;
    moves.push_back(solution);
      
    while(!solution->isInitialState()){
        solution = solution->parent;
        moves.push_back(solution);
    }

    for (int i = moves.size()-1; i >= 0; i--){
        do{cout<<"\nPress enter to see next move\n"<<endl;} while (cin.get() != '\n');
        moves[i]->printGrid();
    }
}

void Controller::pruneHallway(int i, int j){
    if(grid->thereIsWayOut(i,j)){
                   int k = i; int l = j;
                   coord2D door = grid->getDoor(i,j);
                   k = door.first; l = door.second;
                   while(grid->isTrap(k,l)){
                       grid->toWall(k,l);
                       if(grid->thereIsWayOut(k,l)){
                           coord2D door = grid->getDoor(k,l);
                           k = door.first; l = door.second;
                       }
                   }
                   
               }
}

istringstream Controller::nextLine(ifstream &infile, string line){
   getline(infile, line);
   istringstream iss(line);
   return iss;
}

coord2D Controller::getXY(istringstream &iss){
   int x,y;
   iss >> x >> y;
   x--; y--;
   return make_pair(x,y);
}

