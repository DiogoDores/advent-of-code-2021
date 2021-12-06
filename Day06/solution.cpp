#include <bits/stdc++.h>
using namespace std;

long problem(vector<int> input, int days){

   vector<long> numFishAtStage(9);

   for(const auto& fish : input){
      numFishAtStage[fish]++;
   }


   long newborns;
   for(int i = 0; i < days; i++){
      newborns = numFishAtStage[0];

      for(int j=1; j < 9; j++){
         numFishAtStage[j-1] = numFishAtStage[j];
      }

      numFishAtStage[6] += newborns;
      numFishAtStage[8] = newborns;
   }

   return accumulate(numFishAtStage.begin(), numFishAtStage.end(), 0l);
}

vector<int> getInput(string filePath){
   ifstream file(filePath);
   vector<int> input;

   if (file.is_open()) {
      string line;
      while (getline(file, line, ','))
         input.push_back(stoi(line));
   }
   file.close();
   return input;
}

int main()
{
   vector<int> input = getInput("../Day06/input.txt");
   cout << "Part 1: " << problem(input, 80) << endl;
   cout << "Part 2: " << problem(input, 256) << endl;
   return 0;
}