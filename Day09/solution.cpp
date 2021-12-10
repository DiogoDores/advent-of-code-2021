#include <bits/stdc++.h>
using namespace std;

struct Coords{ int x, y; };

bool checkIfHigher(vector<vector<int>> input, Coords c, int newX, int newY){

   if(newY < 0 || newX < 0 || newX >= input[0].size() || newY >= input.size())
      return true;
   else if(input[c.y][c.x] < input[newY][newX])
      return true;
   
   return false;
}

vector<Coords> getLowPoints(vector<vector<int>> input){
   vector<Coords> lowPoints;

   int height = input.size(), width = input[0].size(); 
   for(int y = 0; y < height; y++){
      for(int x = 0; x < width; x++){
         Coords currCoords;
         currCoords.x = x; currCoords.y = y;
         if(checkIfHigher(input, currCoords, x-1, y) &&
            checkIfHigher(input, currCoords, x+1, y) &&
            checkIfHigher(input, currCoords, x, y-1) &&
            checkIfHigher(input, currCoords, x, y+1)){
               lowPoints.push_back(currCoords);
         }
      }
   }

   return lowPoints;
}

int partOne(vector<vector<int>> input){
   vector<Coords> lowPoints = getLowPoints(input);
   vector<int> riskLevel;
   for(auto c :lowPoints){ riskLevel.push_back(input[c.y][c.x] + 1);}
   return accumulate(riskLevel.begin(), riskLevel.end(), 0);
}

void floodFill(vector<vector<int>>& input, unsigned int x, unsigned int y, int n) {
   if(y >= 0 && x >= 0 && x < input[0].size() && y < input.size() && input[y][x] != n){
      input[y][x] = n;
      if(y > 0 && input[y - 1][x] != 9)
         floodFill(input, x, y - 1, n);
      if(y + 1 < input.size() && input[y + 1][x] != 9)
         floodFill(input, x, y + 1, n);
      if(x > 0 && input[y][x - 1] != 9)
         floodFill(input, x - 1, y, n);
      if(x + 1 < input[y].size() && input[y][x + 1] != 9)
         floodFill(input, x + 1, y, n);
   }
}

int partTwo(vector<vector<int>> input){

   vector<Coords> lowPoints = getLowPoints(input);
   vector<int> basinSize;

   for(auto point : lowPoints){
      vector<vector<int>> inputCpy = input;
      floodFill(inputCpy, point.x, point.y, -1);

      size_t sum = 0;
      for(auto& v: inputCpy)
        sum += count(v.begin(), v.end(), -1);
      basinSize.push_back(sum);
   }

   sort(basinSize.begin(), basinSize.end());
   return basinSize[basinSize.size()-1] * basinSize[basinSize.size()-2] * basinSize[basinSize.size()-3];
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

int main()
{
   vector<vector<int>> input = getInput("../Day09/example.txt");
   cout << "Part 1: " << partOne(input) << endl;
   cout << "Part 2: " << partTwo(input) << endl;
   return 0;
}