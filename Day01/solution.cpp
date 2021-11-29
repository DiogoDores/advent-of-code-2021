#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
   ifstream file("../Day01/example.txt");
   if (file.is_open()) {
      string line;
      while (getline(file, line)) {
         cout << line << endl;
      }
      file.close();
   }
}