#include <iostream>
#include <algorithm> 
#include <cmath>
#include <string>
#include <vector>
#include "graph.h"
using namespace std;

int main()
{
    cout << "测试无向无权图/有向无权图：" << endl;

    Graph g1(1); 
    
    g1.addVertex("A");
    g1.addVertex("B");
    g1.addVertex("C");
    g1.addVertex("D");
    
    g1.addNeighbors("A", "B");
    g1.addNeighbors("A", "C");
    g1.addNeighbors("B", "D");
    g1.addNeighbors("D", "A");

    g1.listVertexes();
    g1.listEdges();
    
    g1.listAdjList();
    
    cout << "测试结束" << endl;
    cout << endl;
    
    cout << "测试无向有权图/有向有权图：" << endl;
    //有向有权图
    Graph g2(2); 
    
    g2.addVertex("A");
    g2.addVertex("B");
    g2.addVertex("C");
    g2.addVertex("D");
    
    g2.addNeighbors("A", "B", 3);
    g2.addNeighbors("A", "C", 5);
    g2.addNeighbors("B", "D", 4);
    g2.addNeighbors("D", "A", 6);
    
    g2.listVertexes();
    g2.listEdges();
    
    g2.listAdjList();
    
    cout << "测试结束" << endl;
}
