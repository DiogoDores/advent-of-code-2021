#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
 
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}

int partOne(vector<string> input){
   int infoLength = input[0].length();
   int cnt = 0;
   string gammaBin = "", epsilonBin = "";

   for(int j = 0; j < infoLength; j++){
      for(int i = 0; i < input.size(); i++){
         if(input[i][j] == '0')
            cnt++;
      }

      if(cnt > input.size() - cnt){
         gammaBin += "0";
         epsilonBin += "1";
      } else {
         epsilonBin += "0";
         gammaBin += "1";
      }
      cnt = 0;
   }

   return binaryToDecimal(gammaBin) * binaryToDecimal(epsilonBin);
}

int getRating(vector<string> input, bool mostCommon, int n){

   if(input.size() == 1 || n > input[0].length()){
      return binaryToDecimal(input[0]);
   }

   int infoLength = input[0].length();
   int cnt = 0, startingBit;

   vector<string> rating;

   for(int i = 0; i < input.size(); i++){
      if(input[i][n] == '0')
         cnt++;
   }

   // There are more 0's than 1's
   if(cnt > input.size() - cnt)
      startingBit = mostCommon ? 0 : 1;
   else
      startingBit = mostCommon ? 1 : 0;

   for(int i = 0; i < input.size(); i++){
      if(input[i][n] - '0' == startingBit){
         rating.push_back(input[i]);
      }
   }

   return getRating(rating, mostCommon, n+1);
}

vector<string> getInput(string filePath){
   ifstream file(filePath);
   vector<string> input;

   if (file.is_open()) {
      string line;
      while (getline(file, line)){
         input.push_back(line);
      }
   }
   file.close();
   return input;
}

int main()
{

   vector<string> input = getInput("../Day03/input.txt");
   cout << "Part 1: " << partOne(input) << endl;
   cout << "Part 2: " << getRating(input, true, 0) * getRating(input, false, 0) << endl;
   return 0;
}