#include <bits/stdc++.h>

using namespace std;

class Vent{
   private:
      pair<int, int> start, end;
      vector<pair<int, int>> ventPath;
      
   public:
      int maxX, maxY;
      string orientation;
      Vent(pair<int, int> coords1, pair<int,int> coords2){

         this->maxX = max(coords1.first, coords2.first);
         this->maxY = max(coords1.second, coords2.second);
         
         if(coords1.first == coords2.first){
            this->orientation = "vertical"; //Y is being changed, X is constant
            this->start = coords1.second < coords2.second ? coords1 : coords2;
            this->end = coords1.second < coords2.second ? coords2: coords1;
         } else if (coords1.second == coords2.second){
            this->orientation = "horizontal"; //X is being changed, Y is constant
            this->start = coords1.first < coords2.first ? coords1 : coords2;
            this->end = coords1.first < coords2.first ? coords2: coords1;
         } else {
            this->orientation = "diagonal";
            this->start = coords2;
            this->end = coords1;
         }

         createVentPath();
      }

      void createVentPath(){
         if(this->orientation == "vertical"){
            for(int y = this->start.second; y <= this->end.second; y++){
               pair<int, int> p(this->start.first, y);
               this->ventPath.push_back(p);
            }
         } else if (this->orientation == "horizontal"){
            for(int x = this->start.first; x <= this->end.first; x++){
               pair<int, int> p(x, this->start.second);
               this->ventPath.push_back(p);
            }
         } else if (this->orientation == "diagonal"){
            int currX = this->start.first;
            int currY = this->start.second;

            while(currX != this->end.first){
               pair<int, int> p(currX, currY);
               this->ventPath.push_back(p);

               currX += currX > this->end.first ? -1 : 1;
               currY += currY > this->end.second ? -1 : 1;
            }

            pair<int, int> lastPair(currX, currY);
            this->ventPath.push_back(lastPair);
         }
      }

      vector<pair<int, int>> getVentPath(){
         return this->ventPath;
      }
};

vector<Vent> getInput(string filePath){
   ifstream file(filePath);
   vector<Vent> vents;

   if (file.is_open()) {
      string line;
      while (getline(file, line)){
         int x1, y1, x2, y2;
         sscanf(line.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
         
         pair<int, int> coords1(x1, y1);
         pair<int, int> coords2(x2, y2);
         Vent v(coords1, coords2);
         vents.push_back(v);
      }
   }
   file.close();

   return vents;
}

int problem(vector<Vent> vents, bool includeDiagonals){

   if(!includeDiagonals){
      vents.erase(remove_if(vents.begin(), vents.end(), [](Vent v){return v.orientation == "diagonal";}), vents.end());
   }

   int gridMaxX = 0, gridMaxY = 0, overlaps = 0;

   for(auto v: vents){
      gridMaxX = max(gridMaxX, v.maxX);
      gridMaxY = max(gridMaxY, v.maxY);
   }

   gridMaxX++;
   gridMaxY++;

   int ventMap[gridMaxY][gridMaxX];
   memset(ventMap, 0, sizeof(ventMap));

   for(auto vent: vents){
      for(auto coords: vent.getVentPath()){
         ventMap[coords.second][coords.first] += 1;
      }
   }

   for(int i = 0; i < gridMaxY; i++){
      for(int j = 0; j < gridMaxX; j++){
         if (ventMap[i][j] >= 2)
            overlaps++;
      }
   }

   return overlaps;
}

int main() {
   vector<Vent> input;
   input = getInput("../Day05/input.txt");
   cout << "Part 1: " << problem(input, false) << endl;
   cout << "Part 2: " << problem(input, true) << endl;
   return 0;
}