#ifndef USINGDJKSTRASALGO_HPP
#define USINGDJKSTRASALGO_HPP

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <iostream>
#include <sstream>


using namespace std;


 struct EDGE{
    public:
    string destiny;
    int weight;
    //cponstructor

    EDGE(string dest, int w){
        dest=destiny;
        w=weight;
    }
 };
 using Graph=unordered_map<string,vector<EDGE>>;
 Graph buildStreetInfoGraph(vector<string>&streetInfo){
Graph graph;

for(string street: streetInfo){
string source,destination;
int weight;

//extract vvals from iss stream  >> = stream extractor operator to read three vals successivelyinto the variables
istringstream iss(street);
iss >> source >> destination >> weight;


//adding edge fron rc to destin
graph[source].emplace_back(destination,weight);
//adding edge from destin to source
graph[destination].emplace_back(source,weight);

}

return graph;
}
 Graph:: vector<std::string> SHORTEST_PATH(Graph graph, string &start, string &end){

    unordered_map<string,int>distance;
    unordered_map<string , string>prev;
    priority_queue<pair<int , string >,vector<pair<int,string>>,greater<>>pq;
    //pq is configured as maxheap  --> greater<>

    //initializing dist to all nodes are oo
    for(auto &entry:graph){

distance[entry.first]=INT_MAX;
    }

//dist of strt node =0
distance[start]=0;
pq.push(make_pair(0,start));

//actual algo 
while(!pq.empty()){

   int DIST=pq.top().first; //curr dist
string  curr=pq.top().second; //curr node
pq.pop();


    if(curr==end)//cheak for end position
    {
        vector<string>path;
//reconstructiong path
        while(curr!=start){
            

        }
    }
}

 }


#endif 
