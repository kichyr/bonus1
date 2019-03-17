#include <cstdlib>
#include <ctime>

using namespace std;

class Graph_Generator{
public:
    int m[7][7] = {
        1, 0, 1, 1, 0, 0, 1, 
        0, 1, 1, 0, 0, 1, 0, 
        1, 1, 1, 0, 0, 1, 0, 
        1, 0, 0, 1, 1, 1, 0, 
        0, 0, 0, 1, 1, 0, 1, 
        0, 1, 1, 1, 0, 1, 1, 
        1, 0, 0, 0, 1, 1, 1
    };
    Graph get_random_graph(size_t size) {
        Graph g(size);
        srand(time(NULL));
        for(int i = 0 ; i < size; i++)
            for(int j = i+1; j < size; j++) {
                if(rand()%2 == 1)
                    g.AddEdge(i, j);
            }
        return g;
    }
};
