#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

unordered_map<string, unsigned long> pairs;
unordered_map<string, char> pairInstructions;
char last;

void runStep(){
  auto temp = pairs;
  for(auto& pair : pairs){
     temp.find(pair.first)->second -= pair.second;
     char c = pairInstructions.find(pair.first)->second;
     auto newPair1 = temp.insert({{pair.first[0], c}, pair.second});
     auto newPair2 = temp.insert({{c, pair.first[1]}, pair.second});

     if(!newPair1.second)
			newPair1.first->second += pair.second;
		if(!newPair2.second)
			newPair2.first->second += pair.second;
  }
  pairs = temp;
}

void calculateExtremes(){
   unsigned long min = ULLONG_MAX, max = 0;

	unordered_map<char, unsigned long> counts;
	for(auto p: pairs){
		auto it_p = counts.insert({p.first[0], p.second});
		if(!it_p.second)
			it_p.first->second += p.second;
	}
	auto it_p = counts.insert({last, 1});
	if(!it_p.second)
		it_p.first->second ++;

	for(auto p : counts){
		max = p.second > max ? p.second : max;
		min = p.second < min ? p.second : min;
	}

   cout << max - min << endl;
}

void problem(int steps){
   for(int i = 0; i < steps; i++){
      runStep();
   }
   calculateExtremes();
}

void getInput(string filePath){
   ifstream file(filePath);
   vector<vector<int>> input;

   if (file.is_open()) {
      string line;
      getline(file, line);
      for(int i = 1; i < line.size(); i++)
         auto pair = pairs.insert({{line[i-1], line[i]}, 1});
	   
	   last = line[line.size() - 1];
      getline(file, line);

      while(getline(file, line)){
         string pair{line[0], line[1]};
		   char res = line[6];
		   pairInstructions.insert({pair, res});
      }
   }

   file.close();
   return;
}

int main() {
   getInput("../Day14/input.txt");
   cout << "Part 1: ";
   problem(10);
   pairs.clear();
   pairInstructions.clear();
   getInput("../Day14/input.txt");
   cout << "Part 2: ";
   problem(40);
   return 0;
}