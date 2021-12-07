#include <bits/stdc++.h>
using namespace std;

double partOne(vector<int> input){

   int median, size = input.size();
   sort(input.begin(), input.end());
   int spentFuel = 0;

   if (size % 2 != 0)
      median = input[size / 2];
   else
      median = (input[(size - 1) / 2] + input[size / 2]) / 2;

   for(auto crab : input){
      spentFuel += abs(crab - median);
   }

   return spentFuel;
}

int partTwo(vector<int> input){

   int mean = 0, spentFuel = 0;
   int size = input.size();

   mean = round(accumulate(input.begin(), input.end(), 0) / size);

   for(auto crab : input){
      int cost = abs(crab - mean);
      spentFuel += cost * (cost + 1) / 2;
   }

   return spentFuel;
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
   vector<int> input = getInput("../Day07/example.txt");
   cout << "Part 1: " << partOne(input) << endl;
   cout << "Part 2: " << partTwo(input) << endl;
   return 0;
}