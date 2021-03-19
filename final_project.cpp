#include <iostream>
#include <fstream>
#include <vector>
#include "groph.hpp"
#include <string>

using namespace std;
//------------------------------------------------------------------------------------------------------
struct binnacle_data {
  string month = " ";
  string day = " ";
  string hour = " ";
  string source_ip = " ";
  string target_ip = " ";
  string message = " ";
  bool sourceIn = false;
  bool targetIn = false;
};
//------------------------------------------------------------------------------------------------------
int main() {
  vector <binnacle_data> info;
  char line[64];
  string data_line;
  Graph graph = Graph(1000);

  ifstream file;
  file.open("logs.txt");

  while (!file.eof()) {
    binnacle_data data;
    file.getline(line,4,' ');
    data.month = line;
    file.getline(line,3,' ');
    data.day = line;
    file.getline(line,9,' ');
    data.hour = line;
    file.getline(line,17,' ');
    data.source_ip = line;
    file.getline(line,17,' ');
    data.target_ip = line;
    getline(file,data_line);
    data.message = data_line;
    info.push_back(data);
  }

  file.close();
//------------------------------------------------------------------------------------------------------
  for(int i = 0; i < info.size(); i++) {
    string temp = info[i].source_ip;
    string temp2 = info[i].target_ip;

    if(info[i].sourceIn == false) {
      graph.add_node(info[i].source_ip);

      info[i].sourceIn = true;

      for(int j = 0; j < info.size(); j++) {
        if(info[j].source_ip == temp) { 
          info[j].sourceIn = true;
        }
        if(info[j].target_ip == temp) { 
          info[j].targetIn = true;
        } 
      }
    }
    //------------------------------------------------------------------------------------------------------
    if(info[i].targetIn == false) {
      graph.add_node(info[i].target_ip);
      info[i].targetIn = true;

      for(int j = 0; j < info.size(); j++) {
        if(info[j].target_ip == temp2) { 
          info[j].targetIn = true;
        }
        if(info[j].source_ip == temp2) { 
          info[j].sourceIn = true;
        }
      }
    }

    graph.add_edge(info[i].source_ip, info[i].target_ip, 1);
  }
  //------------------------------------------------------------------------------------------------------
  cout << "- - - - - - - - - - - CAPTSTONE PROJECT - - - - - - - - - - -" <<endl;
  cout << "Act 6.1 - Final Project" <<endl;
  cout << "A01658904 Bruno Passarette Santos" <<endl;
  cout << "A01657929 Christian Jesús González Ramírez" <<endl;
  cout << endl;

  cout << "- - - - - - - - - - POSSIBLE CYBER ATTACKS - - - - - - - - - -" <<endl;
  graph.cyber_attacks();
  cout << endl;

  cout << "- - - - - - - - - - - FAN-OUTS FROM IPS - - - - - - - - - - -" <<endl;
  graph.fan_Outs();
  cout << endl;

  return 0;
}