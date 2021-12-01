#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int partOne(vector<int> input){
   int lastNumber = input[0], result = 0;

   for(int i = 1; i < input.size(); i++){
      if(input[i] > lastNumber){
         result++;
      }
      lastNumber = input[i];
   }

   return result;
}

int partTwo(vector<int> input){
   int window = 3, lastSum = 0, result = 0;

   for (int i = 0; i < input.size() - window + 1; i++) {
      int currentSum = 0;
      for (int j = 0; j < window; j++)
         currentSum += input[i + j];

      if (currentSum > lastSum)
         result++;

      lastSum = currentSum;
   }

   //Subtracts the first window comparison with 0
   return result - 1;
}

vector<int> getInput(string filePath){
   ifstream file(filePath);
   vector<int> input;

   if (file.is_open()) {
      string line;
      while (getline(file, line))
         input.push_back(stoi(line));
   }
   file.close();
   return input;
}

int main()
{
   vector<int> input = getInput("../Day01/input.txt");
   cout << "Part 1: " << partOne(input) << endl;
   cout << "Part 2: " << partTwo(input) << endl;
}