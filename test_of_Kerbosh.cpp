#include"kerbosh.cpp"
#include"graph_generator.cpp"

int main() {
    Graph_Generator generator;
    Graph G  = generator.get_random_graph(55);
    G.print();
    Kerbosh_Search k_search(G);
    k_search.print_kliks();

    return 0;
}