#include <iostream>
#include <vector>

using namespace std;

class Graph //图的类
{
    private:
        struct Vertex //节点的结构
        {
            string value; //value为节点的值
            vector<string> neighbors; //neighbor为指定节点相邻的节点
        };
        struct Edge //边的结构
        {
            string edge_start, edge_end; //edge_start和edge_end分别为边的起点与终点
            int weight; //weight为边的权重
        };
        
        int graph_type; //graph_type为图的类型，取值范围为1和2，1表示无向无权图/有向无权图, 2表示有向无权图/有向有权图
        
        vector<Vertex *> v; //v存放指定图的所有节点
        vector<Edge *> e; //e存放指定图的所有边
    
    public:
        Graph(const int gt = 0) //构造函数，参数为图的类型graph_type
        {
            graph_type = gt; //将gt赋值于graph_type
        }
        
        ~Graph(){} //析构函数
        
        void addVertex(const string val) //往指定图添加节点，参数为节点的值
        {
            Vertex* newVertex = new Vertex; //新创建一个指向Vertex结构的指针，命名为newVertex
            newVertex->value = val; //将参数val赋值于newVertex的值
            v.push_back(newVertex); //将newVertex传入v（v为存放指定图的所有节点）
        }
        
        void addNeighbors(const string value, const string neighbors, const int w = 1) //往指定图添加邻居，参数为节点的值、节点的邻居、以及它俩的权重
        
            for( int i=0; i<v.size(); i++)
            {
                if(v[i]->value == value)
                {
                    v[i]->neighbors.push_back(neighbors);
                }
            }
            
            Edge* newEdge = new Edge;
            newEdge->edge_start = value; //newEdge(边)的开始为start
            newEdge->edge_end = neighbors;
            newEdge->weight = w;
            e.push_back(newEdge); //把newEdge放入名为edge的向量里
            
        }
        
        void listVertexes() //打印出指定图的所有节点
        {
            cout << "列出全部节点: ";
            for( int i=0; i<v.size(); i++)
            {
                if ( i == v.size()-1 )
                {
                    cout << v[i]->value << ".";
                }
                
                else
                {
                    cout << v[i]->value << ", ";
                }
            }
            cout << endl;
            cout << endl;
            
        }
        
        void listEdges() //打印出指定图的所有边
        {
            cout << "列出全部边: ";
            for( int i=0; i<v.size(); i++)
            {
                if ( i == v.size()-1 )
                {
                    cout << "(" << e[i]->edge_start << ", " << e[i]->edge_end << ", " << e[i]->weight << ").";
                }
                
                else
                {
                    cout << "(" << e[i]->edge_start << ", " << e[i]->edge_end << ", " << e[i]->weight << "), ";
                }
            }
            cout << endl;
            cout << endl;
        }
        
        void listAdjList() //打印出指定图的邻接表
        {
            if( graph_type == 1 )
            {
                cout << "列出邻接表:" << endl;
                for( int i=0; i < v.size(); i++)
                {
                    cout << v[i]->value << " -> ";
                    
                    for( int j=0; j < e.size(); j++)
                    {
                        if( v[i]->value == e[j]->edge_start && j == e.size()-1 )
                        {
                            cout << e[j]->edge_end << ". ";
                        }
                            
                        else if( v[i]->value == e[j]->edge_start )
                        {
                             cout << e[j]->edge_end << ", ";
                        }
                    }
                    cout << endl;
                }
                cout << endl;
            }
            
            else if( graph_type == 2 )
            {
                cout << "列出邻接表:" << endl;
                for( int i=0; i < v.size(); i++)
                {
                    cout << v[i]->value << " -> ";
                    
                    for( int j=0; j < e.size(); j++)
                    {
                        if ( v[i]->value == e[j]->edge_start && j == e.size()-1 )
                        {
                            cout << e[j]->edge_end << "(" << e[j]->weight << "). ";
                        }
                        
                        else if( v[i]->value == e[j]->edge_start )
                        {
                             cout << e[j]->edge_end << "(" << e[j]->weight << "), ";
                        }
                            
                    }
                    cout << endl;
                }
                cout << endl;
            }
                
        }
};