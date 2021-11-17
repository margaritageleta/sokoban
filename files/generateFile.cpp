#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <list>

using namespace std;
typedef pair<int, int> coord2D;

int main (int argc, char** argv) {

   
   std::ifstream infile (argv[1]);
   string line;
   istringstream iss;
   int i = 0;
   int j = 0;
   list <coord2D> walls, boxes, storage;
   coord2D player;

   if (infile.is_open()){
       while(getline(infile, line)){
           i++;j=1;
           for (char const &c: line) {
               if (c == '#'){
                   walls.push_back(make_pair(i,j));
               } else if(c == '.'){
                   storage.push_back(make_pair(i,j));
               } else if(c == '$'){
                   boxes.push_back(make_pair(i,j));
               } else if(c == '@'){
                   player = make_pair(i,j);
               }
               j++;
            }
       }
   }
   string fileName = "sokoban";
   fileName = fileName + argv[1][5] + argv[1][6] + ".txt";

   ofstream myfile (fileName);
   if (myfile.is_open()){
        myfile << i << " " << j-1 << " " << endl;

        myfile << walls.size() << " ";
        for (coord2D const& coord : walls) {
            myfile << coord.first << " " << coord.second << " ";
        }
        myfile << endl;
        myfile << boxes.size() << " ";
        for (coord2D const& coord : boxes) {
            myfile << coord.first << " " << coord.second << " ";
        }
        myfile << endl;
        myfile << storage.size() << " ";
        for (coord2D const& coord : storage) {
            myfile << coord.first << " " << coord.second << " ";
        }
        myfile << endl;
        myfile << player.first << " " << player.second << endl;
        myfile.close();
    }
}