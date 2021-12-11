#include <bits/stdc++.h>
using namespace std;

map<char, int> errorPoints{
   {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}}
};
map<char, int> autoCompletePoints{
   {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}}
};

void problem(vector<string> input){
   int errorScore = 0;
   vector<long> completionScores;

   for(auto line : input){
      string expectedTags;
      long autoCompleteScore = 0;
      bool corrupted = false;
      for(auto c : line){
         if(c == '(')
            expectedTags.push_back(')');
         else if(c == '[')
            expectedTags.push_back(']');
         else if(c == '{')
            expectedTags.push_back('}');
         else if(c == '<')
            expectedTags.push_back('>');
         else if(c == expectedTags.back()){
            expectedTags.pop_back();
         } else {
            errorScore += errorPoints.find(c)->second;
            corrupted =  true;
            break;
         }
      }
      if(!corrupted){
         reverse(expectedTags.begin(), expectedTags.end());
         for(auto c:expectedTags)
            autoCompleteScore = autoCompleteScore * 5 + autoCompletePoints.find(c)->second;

         completionScores.push_back(autoCompleteScore);
      }
   }

   sort(completionScores.begin(), completionScores.end());

   cout << "Part 1: " << errorScore << endl;
   cout << "Part 2: " << completionScores[completionScores.size()/2] << endl;
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
   vector<string> input = getInput("../Day10/input.txt");
   problem(input);
   return 0;
}