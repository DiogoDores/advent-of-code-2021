#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> neighbours = {{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

void flashLights(vector<vector<int>> octopi, int x, int y, int &flashes){
   for(auto neighbour:neighbours){
      int newX = x + neighbour.first, newY = y + neighbour.second;
      if(newX >= 0 && newY >= 0 && newX < octopi[0].size() && newY < octopi.size()){
         octopi[newY][newX] += 1;

         if(octopi[newY][newX] == 9){
            octopi[newY][newX] = 0;
            flashes++;
            flashLights(octopi, newX, newY, flashes);
         }
      }
   }
}

int problem(vector<vector<int>> octopi){
   int height = octopi.size(), width = octopi[0].size();
   int flashes = 0;
   
   for(int i = 0; i < 10; i++){
      for(int y = 0; y < height; y++){
         for(int x = 0; x < width; x++){
            octopi[y][x]++;
            cout << octopi[y][x] << " ";
            if(octopi[y][x] == 9){
               octopi[y][x] = 0;
               flashes++;
               flashLights(octopi, x, y, flashes);
            }
         }
         cout << endl;
      }
      cout << endl << endl;
   }
  
  return flashes;
}

 vector<vector<int>> getInput(string filePath){
   ifstream file(filePath);
   vector<vector<int>> input;

   if (file.is_open()) {
      string line;
      while (getline(file, line)){
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
   vector<vector<int>> input = getInput("../Day11/example.txt");
   cout << "Part 1: " << endl << problem(input) << endl;
   return 0;
}