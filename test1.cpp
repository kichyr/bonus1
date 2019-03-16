#include"algorithm.cpp"

int main() {
    Graph_Generator generator;
    Graph G  = generator.get_random_graph(9);
    G.print();
    Search_kliks search(G);
    search.print_parts_of_kliks();
    search.find_k_kliks(4);

    cout << search.GetMaxCliqueSize();
}