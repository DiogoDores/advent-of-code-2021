#include <bits/stdc++.h>
using namespace std;

vector<string> getDisplayVector(pair<string,string> p){
   vector<string> displays;
   string display = p.second, temp = "";
   stringstream ss(display);

   while(ss >> temp){ displays.push_back(temp); }
   return displays;
}

vector<string> getSignalVector(pair<string, string> p){
   vector<string> signals;
   string signal = p.first, temp = "";
   stringstream ss(signal);

   while(ss >> temp){ signals.push_back(temp); }
   return signals;
}

double partOne(vector<pair<string, string>> input){

   int res = 0;
   vector<int> uniqueDisplay = {2, 3, 4, 7};

   for(auto data:input){
      vector<string> displays = getDisplayVector(data);
      for(auto d: displays){
         if(find(uniqueDisplay.begin(), uniqueDisplay.end(), d.length()) != uniqueDisplay.end())
            res++;
      }
   }

   return res;
}

string getStringSignal(vector<pair<int,string>> v, int n){
   for(auto p : v){
      if(p.first == n)
         return p.second;
   }
   return "";
}

int getNumberSignal(vector<pair<int,string>> v, string signal){
   for(auto p : v){
      if(p.second == signal){
         return p.first;
      }
   }
   return -1;
}

int partTwo(vector<pair<string, string>> input){

   vector<string> displayNumbers;
   int res = 0;

   for(auto data:input){
      vector<pair<int, string>> decodedSignals;
      vector<string> signals = getSignalVector(data);
      vector<string> displays = getDisplayVector(data);
      sort(signals.begin(), signals.end(), []
         (const string& first, const string& second){
            return first.length() < second.length();
         }
      );

      for(auto& s: signals){ 
         sort(s.begin(), s.end());
         pair<int, string> decodedNumber;
         if(s.length() == 2){
            decodedNumber.first = 1;
         } else if(s.length() == 3){
            decodedNumber.first = 7;
         } else if(s.length() == 4){
            decodedNumber.first = 4;
         } else if(s.length() == 7){
            decodedNumber.first = 8;
         } else if(s.length() == 5){
            string seven = getStringSignal(decodedSignals, 7), stringDiffSeven;
            set_intersection(s.begin(), s.end(), seven.begin(), seven.end(), back_inserter(stringDiffSeven));

            if(stringDiffSeven.length() == 3){
               decodedNumber.first = 3;
            } else {
               string four = getStringSignal(decodedSignals, 4), stringDiffFour;
               set_intersection(s.begin(), s.end(), four.begin(), four.end(), back_inserter(stringDiffFour));

               if(stringDiffFour.length() == 3){
                  decodedNumber.first = 5;
               } else {
                  decodedNumber.first = 2;
               }
            }
         } else if(s.length() == 6){
            string four = getStringSignal(decodedSignals, 4), stringDiffFour;
            set_intersection(s.begin(), s.end(), four.begin(), four.end(), back_inserter(stringDiffFour));


            if(stringDiffFour.length() == 4){
               decodedNumber.first = 9;
            } else {
               string seven = getStringSignal(decodedSignals, 7), stringDiffSeven;
               set_intersection(s.begin(), s.end(), seven.begin(), seven.end(), back_inserter(stringDiffSeven));

               if(stringDiffSeven.length() == 3){
                  decodedNumber.first = 0;
               } else {
                  decodedNumber.first = 6;
               }
            }      
         }
         decodedNumber.second = s;
         decodedSignals.push_back(decodedNumber);
      }

      string finalNumberStr = "";
      for(auto d: displays){
         sort(d.begin(), d.end());
         int num = getNumberSignal(decodedSignals, d);
         finalNumberStr += to_string(num);
      }

      displayNumbers.push_back(finalNumberStr);
   }

   for(auto d: displayNumbers){
      res += stoi(d);
   }

   return res;
}

vector<pair<string,string>> getInput(string filePath){
   ifstream file(filePath);
   vector<pair<string, string>> input;
   string signal, display;

   if (file.is_open()) {
      string line;
      while (getline(file, line)){
         signal = line.substr(0, line.find(" |"));
         display = line.substr(line.find("| ") + 2);
         pair<string, string> newPair(signal, display);
         input.push_back(newPair);
      }
   }
   file.close();
   return input;
}

int main()
{
   vector<pair<string, string>> input = getInput("../Day08/input.txt");
   cout << "Part 1: " << partOne(input) << endl;
   cout << "Part 2: " << partTwo(input) << endl;
   return 0;
}