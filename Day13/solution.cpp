#include <bits/stdc++.h>
using namespace std;

struct Dot{
   int x, y;

   Dot(int x, int y){
      this->x = x;
      this->y = y;
   }

   bool operator < (const Dot& dot) const {
      if(dot.y == this->y)
         return dot.x < this->x;
      else
         return dot.y < this->y;
   }

   bool operator == (const Dot& dot) const {
      return dot.x == this->x && dot.y == this->y;
   }
};

struct Fold{
   string axis;
   int foldPos;

   Fold(string axis, int pos){
      this->axis = (axis == "y") ? "horizontal" : "vertical";
      this->foldPos = pos;
   }
};

vector<Dot> dots;
queue<Fold> folds;

int getMaxX(){
   int max = 0;
   for(const auto& dot:dots){
      if(dot.x > max)
         max = dot.x;
   }
   return max;
}

int getMaxY(){
   int max = 0;
   for(const auto& dot:dots){
      if(dot.y > max)
         max = dot.y;
   }
   return max;
}

void printPaper(){
   int maxX = getMaxX() + 1, maxY = getMaxY() + 1;
   vector<vector<char>> grid(maxY, vector<char>(maxX, ' '));

   for(const auto& dot:dots)
      grid[dot.y][dot.x] = '#';
   
   for(int i = 0; i < grid.size(); i++){
      for(int j = 0; j < grid[i].size(); j++){
         cout << grid[i][j];
      }
      cout << endl;
   }
}

void foldPaper(){
   Fold newFold = folds.front();
   folds.pop();

   vector<Dot> dotsToFold;

   if(newFold.axis == "horizontal"){
      copy_if(dots.begin(), dots.end(), back_inserter(dotsToFold), [newFold](const Dot& dot){ return dot.y > newFold.foldPos;});
      dots.erase(remove_if(dots.begin(), dots.end(), [newFold](const Dot& dot){ return dot.y > newFold.foldPos;}), dots.end());
      for(auto& dot: dotsToFold){
         dot.y -= 2 * (dot.y - newFold.foldPos);
         dots.push_back(dot);
      }
   } else if(newFold.axis == "vertical"){
      copy_if(dots.begin(), dots.end(), back_inserter(dotsToFold), [newFold](const Dot& dot){ return dot.x > newFold.foldPos;});
      dots.erase(remove_if(dots.begin(), dots.end(), [newFold](const Dot& dot){ return dot.x > newFold.foldPos;}), dots.end());
      for(auto& dot: dotsToFold){
         dot.x -= 2 * (dot.x - newFold.foldPos);
         dots.push_back(dot);
      }
   }

   sort(dots.begin(), dots.end());
   dots.erase(unique(dots.begin(), dots.end()), dots.end());
}

int part1(){
   foldPaper();
   return dots.size();
}

void part2(){
   cout << "Part 1: " << part1() << endl;

   while(folds.size() > 0){
      foldPaper();
   }
   cout << "Part 2: " << endl;
   printPaper();
}

void getInput(string filePath){
   ifstream file(filePath);
   vector<vector<int>> input;

   if (file.is_open()) {
      string line;
      while(getline(file, line)){
         if(line.size() <= 1)
            break;
         
         int delimiterPos = line.find(',');
         int x = stoi(line.substr(0, delimiterPos));
         int y = stoi(line.substr(delimiterPos + 1));
         dots.push_back(Dot(x, y));
      }

      while(getline(file, line)){
         int delimiterPos = line.find('=');
         folds.push(Fold(line.substr(delimiterPos - 1, 1), stoi(line.substr(delimiterPos + 1))));
      }
   }

   file.close();
   return;
}

int main() {
   getInput("../Day13/input.txt");
   part2();
   return 0;
}