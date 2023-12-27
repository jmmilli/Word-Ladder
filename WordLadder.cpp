#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

//all of the global variables being used
vector<string> wordList; // Contains 5-letter words from wordlist05.txt
unordered_map<string, bool> visited;
unordered_map<string, string> predecessor;
unordered_map<string, int> dist; 
unordered_map<string, vector<string>> neighbors;

//function that builds the word graph by generating all of the neighbors for each word
void buildWordGraph() {
    
    //open the txt file and create a current word placeholder variable
    ifstream wordFile("wordlist05.txt");
    string currentWord;
    
    //Read each word from the text file and add it to the word list 
    while (wordFile >> currentWord)
        wordList.push_back(currentWord);
    
    //Generate all of the neighbors for each of the words in the word list
    for (auto word : wordList) {
        for (int position = 0; position < word.length(); position++) {
            //iterate through and compare each char in the word
            for (char letter = 'a'; letter <= 'z'; letter++) {
                //if the current letter is equal
                if (letter == word.at(position))
                    continue;
                //set the current word and add it to the neighbor list
                string current = word;
                current.at(position) = letter;
                neighbors[word].push_back(current);
            }
        }
    }
}

//function that finds the shortest path between the two words using BFS
int findShortestPath(string start, string end, vector<string> &path) {
    //if the word before the ending word is not found, just return zero
    if (predecessor.find(end) == predecessor.end())
        return 0;

    //If the starting and ending words are different, recursivley find the shortest path between them
    if (start.compare(end) != 0) {
        int step = 1 + findShortestPath(start, predecessor[end], path);
        path.push_back(end);
        return step;
      //else (if the words are the same add the word to the path and return zero)
    } else {
        path.push_back(end);
        return 0;
    }
}

//main word ladder function 
void wordLadder(string start, string end, int &steps, vector<string> &path) {
    
    //build the word graph
    buildWordGraph();
    
    //Create and initialize a queue for BFS traversal
    queue<string> toVisit;
    toVisit.push(start);
    visited[start] = true;
    dist[start] = 0;
    
    //Use BFS to find the shortest path between the words
    while (!toVisit.empty()) {
        string currentNode = toVisit.front();
        toVisit.pop();
        for (string neighbor : neighbors[currentNode]) {
            if (!visited[neighbor]) {
                predecessor[neighbor] = currentNode;
                dist[neighbor] = 1 + dist[currentNode];
                visited[neighbor] = true;
                toVisit.push(neighbor);
            }
        }
    }
    //find the number of steps we need with findShortestPath
    steps = findShortestPath(start, end, path);
}



int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}


