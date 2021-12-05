#include <bits/stdc++.h>

using namespace std;

int problem(bool winGame, int deltaNum){
   ifstream file("../Day04/input.txt");
   string data;

   vector<int> bingoNums;

   file >> data;
   stringstream ss(data);

   while(getline(ss, data, ',')){
      bingoNums.push_back(stoi(data));
   }

   int sum;

   while (!file.eof()) {
      vector<int> board;
      int num = 0, boardSum = 0;
      bool bingo = false;

      for (int i = 0; i < 25; i++){
         file >> num;
         board.push_back(num);
         boardSum += num;
      }

      for(int i = 0; i < bingoNums.size() && !bingo; i++){
         int index = distance(board.begin(), find(board.begin(), board.end(), bingoNums[i]));

         if(index != 25){
            boardSum -= board[index];
            board[index] = -1;

            int cntRow = 0, cntCol = 0;

            for (int j = 0; j < 5; j++){
               cntRow += board[5 * floor(index/5) + j] == -1;
               cntCol += board[(index % 5) + 5 * j] == -1;
            }

            if(cntRow == 5 || cntCol == 5){
               if(winGame) {
                  if(i < deltaNum){
                     deltaNum = i;
                     sum = boardSum;
                  }
               } else {
                  if(i >= deltaNum){
                     deltaNum = i;
                     sum = boardSum;
                  }
               }
               
               bingo = true;
            }
         }
      }
   }


   file.close();
   
   return bingoNums[deltaNum] * sum;
}

int main() {
   cout << "Part 1: " << problem(true, INT_MAX) << endl;
   cout << "Part 2: " << problem(false, 0) << endl;
   return 0;
}