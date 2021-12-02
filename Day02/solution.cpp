#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int partOne(vector<string> input){
   stringstream ss;
   int horizontal = 0, depth = 0;

   for(int i = 0; i < input.size(); i++){
      ss.clear();
      ss << input[i];
      string dir;
      int num;

      while(!ss.eof()){
         ss >> dir >> num;
         
         if(dir == "forward"){
            horizontal += num;
         } else if(dir == "up"){
            depth -= num;
         } else if(dir == "down"){
            depth += num;
         }
      }
   }
   return horizontal * depth;
}

int partTwo(vector<string> input){
   stringstream ss;
   int horizontal = 0, depth = 0, aim = 0;

   for(int i = 0; i < input.size(); i++){
      ss.clear();
      ss << input[i];
      string dir;
      int num;

      while(!ss.eof()){
         ss >> dir >> num;
         
         if(dir == "forward"){
            horizontal += num;
            depth += num * aim;
         } else if(dir == "up"){
            aim -= num;
         } else if(dir == "down"){
            aim += num;
         }
      }
   }
   return horizontal * depth;
}

vector<string> getInput(string filePath){
   ifstream file(filePath);
   vector<string> input;

   if (file.is_open()) {
      string line;
      while (getline(file, line))
         input.push_back(line);
   }
   file.close();
   return input;
}

int main()
{
   vector<string> input = getInput("../Day02/input.txt");
   cout << "Part 1: " << partOne(input) << endl;
   cout << "Part 2: " << partTwo(input) << endl;
   return 0;
}