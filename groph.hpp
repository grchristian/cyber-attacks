#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
//------------------------------------------------------------------------------------------------------
#define UNVISITED 0
#define IN_PROGRESS 1
#define VISITED 2

using namespace std;
//------------------------------------------------------------------------------------------------------
struct fan_outs {
  string ip = " ";
  int f_Outs = 0;
};
//------------------------------------------------------------------------------------------------------
bool sortFunction(fan_outs A, fan_outs B) {
  return (A.f_Outs > B.f_Outs);
}
//------------------------------------------------------------------------------------------------------
class Node {
  private:
    string value;
    int predecessor;
    int fan_Outs;

  public:
    Node(string _value) {
      value = _value;
      predecessor = 0;
      fan_Outs = 0;
    }
  
  friend class Graph;
};
//------------------------------------------------------------------------------------------------------
class Graph {
  private:
  int **adjacencies;
  vector<Node*> nodes;

  //----------------------------------------------------------------------------------------------------
  //Depth search algorithm
  void dfs(int source, int *states) {
    states[source] = IN_PROGRESS;

    for(int i = 0; i < nodes.size(); i++) {
      if(adjacencies[source][i] != 0 && states[i] == UNVISITED) {
        dfs(i,states);
      }
    }

    states[source] = VISITED;
    cout << source << "\t";
  }
  //----------------------------------------------------------------------------------------------------
  void bfs(int source, int *states) {
    queue <int> inLine;
    inLine.push(source);

    while(!inLine.empty()) {
      for(int i = 0; i < nodes.size(); i++) {
        if(adjacencies[source][i] != 0 && nodes[i]->predecessor == 0) {
          nodes[i]->predecessor = source;
          inLine.push(i);
          states[i] = VISITED;
        }
      }
      cout << inLine.front() << "\t";
      inLine.pop();
    }
  }
  //----------------------------------------------------------------------------------------------------
  //To obtain the index of the node of each chosen value.
  int get_Index(string _value) {
    for(int i = 0; i< nodes.size(); i++) {
      if(nodes[i]->value == _value) {
        return i;
      }
    }
    return -1;
  }
  //----------------------------------------------------------------------------------------------------
  public:
  Graph(int numberOfNodes) {
    adjacencies = new int*[numberOfNodes];
    for(int i = 0; i < numberOfNodes; i++) {
      adjacencies[i] = new int[numberOfNodes];
    }

    for(int i = 0; i < numberOfNodes; i++) {
      for(int j = 0; j < numberOfNodes; j++) {
        adjacencies[i][j] = 0;
      }  
    }
  }
  //----------------------------------------------------------------------------------------------------
  // To counts the amount of messages sent from the same IP, and show them.
  void fan_Outs() {
    vector <fan_outs> tempInfo;
    fan_outs save;

    for(int i = 0; i < nodes.size(); i++) {
      for(int j = 0; j < nodes.size(); j++) {
        if(adjacencies[i][j] != 0) {
          nodes[i]->fan_Outs = nodes[i]->fan_Outs + adjacencies[i][j];
        }
      }

      save.ip = nodes[i]->value;
      save.f_Outs = nodes[i]->fan_Outs;
      tempInfo.push_back(save);
    }

    sort(tempInfo.begin(), tempInfo.end(), sortFunction);

    for(int i = 0; i < tempInfo.size(); i++) {
      cout << tempInfo[i].f_Outs << " - " << tempInfo[i].ip << endl;
    }
  }
  //----------------------------------------------------------------------------------------------------
  //To add an edge to the nodes that have the chosen weight
  void add_edge(string source, string target, int weight) {
    int row, col;

    row = get_Index(source);
    col = get_Index(target);
    adjacencies[row][col] = adjacencies[row][col] + weight;
  }

  //----------------------------------------------------------------------------------------------------
  //To move all the nodes starting at the given node.
  void DFS(string source) {
    int *states = new int[nodes.size()];
    for(int i = 0; i < nodes.size(); i++) {
      states[i] = UNVISITED;
    }
    int sourceIndex = get_Index(source);
    dfs(sourceIndex, states);
  }
  //----------------------------------------------------------------------------------------------------
  //To add a new node to the graph.
  void add_node(string _value) {
    Node *n = new Node(_value);
    nodes.push_back(n);
  }
  //----------------------------------------------------------------------------------------------------
  //To identify the IPs that might be with bad intentioned, trying to attack.
  void cyber_attacks() {
    vector <string> tempInfo;
    vector <string>::iterator it;
    for(int i = 0; i < nodes.size(); i++) {
      for(int j = 0; j < nodes.size(); j++) {
        if(adjacencies[i][j] > 5) {
          it = find(tempInfo.begin(), tempInfo.end(), nodes[j]->value);
          if(it == tempInfo.end()) {
            tempInfo.push_back(nodes[j]->value);
          }
        }
      }
    }

    if(tempInfo.size() > 0) {
      for(int i = 0; i < tempInfo.size(); i++) {
        cout << tempInfo[i] << endl;
      }

    }
  }
  //----------------------------------------------------------------------------------------------------
  void BFS(string source) {
    int *states = new int[nodes.size()];
    int sourceIndex = get_Index(source);

    for(int i = 0; i < nodes.size(); i++) {
      states[i] = UNVISITED;
    }

    for(int i = sourceIndex; i < nodes.size(); i++) {
      if(states[i] == UNVISITED) {
        bfs(i, states);
        states[i] = VISITED;
      }
    }
  }
  //----------------------------------------------------------------------------------------------------
};
