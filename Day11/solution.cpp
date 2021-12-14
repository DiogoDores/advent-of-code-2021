#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> neighbours = {{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

void printGrid(vector<vector<int>> &octopi){
   for(int y = 0; y < octopi.size(); y++){
      for(int x = 0; x < octopi[y].size(); x++){
         cout << octopi[y][x] << " ";
      }
      cout << endl;
   }
   cout << endl << endl;
}

void flashLights(vector<vector<int>> &octopi, int x, int y){

   octopi[y][x] += 1;

   if(octopi[y][x] == 10){
      int startX = (x-1 >= 0) ? x-1 : 0;
      int startY = (y-1 >= 0) ? y-1 : 0;
      int endX = (x+1 > octopi[0].size() - 1) ? octopi[0].size()-1 : x+1;
      int endY = (y+1 > octopi.size() - 1) ? octopi.size() - 1 : y+1;

      for(int idY = startY; idY <= endY; idY++){
         for(int idX = startX; idX <= endX; idX++){
            flashLights(octopi, idX, idY);
         }
      }
   }
}

int part1(vector<vector<int>> octopi){
   int height = octopi.size(), width = octopi[0].size();
   int flashes = 0, step = 0;
   bool firstLoop = true;
   
   for(int i = 0; i < 100; i++){

      bool allFlashed = true;

      for(int y = 0; y < height; y++){
         for(int x = 0; x < width; x++){
            flashLights(octopi, x, y);
         }
      }

      for(int y = 0; y < height; y++){
         for(int x = 0; x < width; x++){
            if(octopi[y][x] > 9){
               flashes++;
               octopi[y][x] = 0;
            } else {
               allFlashed = false;
            }
         }
      }

      if(allFlashed && firstLoop){
         step = i + 1;
         firstLoop = false;
      }
   }
  
   return flashes;
}

int part2(vector<vector<int>> octopi){
   int height = octopi.size(), width = octopi[0].size();
   int step = 0, n = 0;
   bool foundLoop = true;
   
   while(foundLoop){
      bool allFlashed = true;
      n++;

      for(int y = 0; y < height; y++){
         for(int x = 0; x < width; x++){
            flashLights(octopi, x, y);
         }
      }

      for(int y = 0; y < height; y++){
         for(int x = 0; x < width; x++){
            if(octopi[y][x] > 9){
               octopi[y][x] = 0;
            } else {
               allFlashed = false;
            }
         }
      }

      if(allFlashed && foundLoop){
         step = n;
         foundLoop = false;
      }
   }
  
   return step;
}

vector<vector<int>> getInput(string filePath){
   ifstream file(filePath);
   vector<vector<int>> input;

   if (file.is_open()) {
      string line;
      while(getline(file, line)){
         vector<int> temp;
         for(auto n : line){
            temp.push_back(n - '0');
         }
         input.push_back(temp);
      }
   }

   file.close();
   return input;
}

int main() {
   vector<vector<int>> input = getInput("../Day11/input.txt");
   cout << "Part 1: " << part1(input) << endl;
   cout << "Part 2: " << part2(input) << endl;
   return 0;
}