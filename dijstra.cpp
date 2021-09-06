#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

class core{
public:
    int from, to, cost;
    core(){
        from=0;
        to=0;
        cost=0;
    }
    
    core(int from, int to, int cost){
        this->from=from;
        this->to=to;
        this->cost=cost;
    }
};

template <class H> class Graph{
    H* nodes;
    core **edges;
    
    int _search(H node){
        int k=0;
        while(k<currentNodes && nodes[k]!=node){
            ++k;
        }
        if (!(k<currentNodes)){
            return -1;
        }
        return k;
    }

    int __getMinN(int *costs){
        int min=-1;
        int k;
        for(k=1; k<currentNodes; ++k){
            if (costs[k-1]>costs[k]){
                min = k;
            }
        }
        if (min<0){
            return -1;
        }
        return min;
    }
    
public:
    int sizenodes, sizedges, currentNodes, currentEdges;
    
    Graph(int sizenodes){
        this->sizenodes=sizenodes;
        sizedges=sizenodes*sizenodes;
        currentNodes=currentEdges=0;
        nodes = new H[this->sizenodes];
        edges = new core*[sizedges];
    }
    
    Graph* insertNode(H node){
        if(currentNodes<sizenodes){
            nodes[currentNodes++]=node;
        }
        return this;
    }
    
    Graph* insertEdge(H a, H b, int cost){
        if (!(currentEdges<sizedges)){
            return this;
        }
        int indexA = _search(a), indexB = _search(b);
        if(indexA<0 || indexB < 0){
            return this;
        }
        edges[currentEdges++] = new core(indexA, indexB, cost);
        return this;
    }
    
   
    
    int dijkstra(H source, H dest){
        int res = INT_MAX;
        int *prex = new int[sizenodes];
        int temp;
        int start = _search(source), end = _search(dest);
       
        if (start<0 || end<0){
            return -1;
        }
        int* costs = new int[sizenodes];
        for(int k=0; k<sizenodes; ++k){
            costs[k]=INT_MAX;
            prex[k]=INT_MAX;
        }
        costs[start]=0;
        prex[start] = -1;
         
        for(int count=0; count<sizenodes; count++){
            temp = __getMinN(costs);
            for(int k=0; k<currentEdges; ++k){
                if (costs[edges[k]->from]!=INT_MAX && costs[edges[k]->from] + edges[k]->cost < costs[edges[k]->to]){
                    prex[edges[k]->to] = temp;
                    costs[edges[k]->to] = costs[edges[k]->from] + edges[k]->cost;
                }
            }
        }
        
    
        if (costs[end]!=INT_MAX){
            res = costs[end];
        }
        delete[] costs; 
        delete[] prex;
        return res;
    }
};

int main(int argc, char **argv)
{
	ifstream *in = new ifstream("input.txt");
    ofstream *out = new ofstream("output.txt");
    string type;
    int itemp1, itemp2, sizenodes, sizedges, cost;
    double dtemp1, dtemp2;
    char c;
    while(*in >> sizenodes >> sizedges >> type){
        if (type == "int"){
            Graph<int>* g = new Graph<int>(sizenodes);
            for(int k=0; k<sizenodes; ++k){
                *in >> itemp1;
                g->insertNode(itemp1);
            }
            for(int k=0; k<sizedges; ++k){
                *in >> c >> itemp1 >> itemp2 >> cost >> c;
                g->insertEdge(itemp1, itemp2, cost);
            }
            *in >> itemp1 >> itemp2;

            *out << g->dijkstra(itemp1, itemp2) << endl;
            delete g;
        }
        else{
            Graph<double>* g = new Graph<double>(sizenodes);
            for(int k=0; k<sizenodes; ++k){
                *in >> dtemp1;
                g->insertNode(dtemp1);
            }
            for(int k=0; k<sizedges; ++k){
                *in >> c >> dtemp1 >> dtemp2 >> cost >> c;
                g->insertEdge(dtemp1, dtemp2, cost);
            }
            *in >> dtemp1 >> dtemp2;
        
            *out << g->dijkstra(dtemp1, dtemp2) << endl;
            delete g;
        }
         cout<<"\n";
    }
    in->close();
    out->close();
    delete in;
    delete out;
	return 0;
}

