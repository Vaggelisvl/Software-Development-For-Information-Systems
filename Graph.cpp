//
// Created by snz on 10/23/2023
#include "headers/structures/unorderedMap/UnorderedMap.h"
class Node{
    public:
    Node(int id, float *quordinates){
        this->id=id;
        this->quordinates=quordinates;
    }
    int getId(){
        return id;
    }
    float *getQuordinates(){
        return quordinates;
    }

private:
    float *quordinates;
    int id;
};

class Edge{
    public:
    Edge(Node *start, Node *end, float weight){
        this->start=start;
        this->end=end;
        this->weight=weight;
    }
    Node *getStart(){
        return start;
    }
    Node *getEnd(){
        return end;
    }
    float getWeight(){
        return weight;
    }

private:
    Node *start;
    Node *end;
    float weight;
};

class Graph{

public:
    Graph(int N){
        numNodes=0;
        numEdges=0;
        this->nodes=new Node*[N];
    }
    void addNode(Node *node){
        nodes[numNodes]=node;
        numNodes++;
    }
    void addEdge(Edge *edge){
        edges[numEdges]=edge;
        numEdges++;
    }
    Node *getNode(int id){
        for(int i=0;i<numNodes;i++){
            if(nodes[i]->getId()==id){
                return nodes[i];
            }
        }
        return nullptr;
    }
   void setNode(int id, Node *node){
        for(int i=0;i<numNodes;i++){
            if(nodes[i]->getId()==id){
                nodes[i]=node;
            }
        }
    }
    int getNumNodes(){
        return numNodes;
    }
    int getNumEdges(){
        return numEdges;
    }
private:
    Node **nodes;
    Edge **edges;
    int numNodes;
    int numEdges;
};

int main(){
    UnorderedMap unorderedMap= new UnorderedMap(20);


}
