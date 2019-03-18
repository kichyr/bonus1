#include <cstdlib>
#include <ctime>

using namespace std;

class Graph_Generator{
public:
    Graph get_random_graph(size_t size) {
        Graph g(size);
        srand(time(NULL));
        for(uint i = 0 ; i < size; i++)
            for(uint j = i+1; j < size; j++) {
                if(rand()%2 == 1)
                    g.AddEdge(i, j);
            }
        return g;
    }
    

    Graph get_bad_graph() {
        size_t n_vertices = 13;
        Graph result(n_vertices);
        for (uint i = 0; i < n_vertices; ++i) {
            for (uint j = 0; j < n_vertices; ++j) {
                if (i >= j) {
                    continue;
                }
                if ((i < 5) && (j > 35)) {
                    continue;
                } else {
                    result.AddEdge(i, j);
                }
            }
        }
        //result.print();
        return result;
    }
};
