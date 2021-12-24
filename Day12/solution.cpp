#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
        unordered_map<string, vector<string>> tree;
        vector<vector<string>> paths;
        bool part2 = false;

        void calculatePaths(){
            multiset<string> visited;
            vector<string> path;
            DFS("start", path, visited);
        }

    private:
        void DFS(const string& current, vector<string>& path, multiset<string>& visited, bool visitedTwice = false);
};

void Graph::DFS(const string& current, vector<string>& path, multiset<string>& visited, bool visitedTwice){
    if(islower(current[0])){
        if(part2 && visited.count(current)){
            visitedTwice = true;
        }
        visited.insert(current);
    }

    path.push_back(current);

    if(current == "end")
        paths.push_back(path);
    else{
        for(const string& next : tree[current]){
            if(next == "start")
                continue;
            
            if(!visited.count(next) || (part2 && !visitedTwice))
                DFS(next, path, visited, visitedTwice);
        }
    }
    
    path.pop_back();
    auto it = visited.find(current);
    if(it != visited.end()){
        visited.erase(it);
    }
}

int part1(vector<vector<string>> input){
    Graph graph;
    int ret;

    for(const auto& line: input){
        graph.tree[line[0]].push_back(line[1]);
        graph.tree[line[1]].push_back(line[0]);
    }

    graph.calculatePaths();
    ret = graph.paths.size();
    return ret;
}

int part2(vector<vector<string>> input){
    Graph graph;
    int ret;

    for(const auto& line: input){
        graph.tree[line[0]].push_back(line[1]);
        graph.tree[line[1]].push_back(line[0]);
    }

    graph.part2 = true;
    graph.calculatePaths();
    ret = graph.paths.size();
    return ret;
}

vector<vector<string>> getInput(string filePath){
    ifstream file(filePath);
    vector<vector<string>> input;

    if (file.is_open()) {
        string line;
        while(getline(file, line)){
            int delimiterPos = line.find('-');
            string cave1 = line.substr(0, delimiterPos);
            string cave2 = line.substr(delimiterPos + 1);
            vector<string> temp = {cave1, cave2};
            input.push_back(temp); 
        }
    }

    file.close();
    return input;
}

int main() {
   vector<vector<string>> input = getInput("../Day12/input.txt");
   cout << "Part 1: " << part1(input) << endl;
   cout << "Part 2: " << part2(input) << endl;
   return 0;
}