#include"algorithm.cpp"

int main() {
    Graph_Generator generator;
    Graph G  = generator.get_random_graph(48);\
    Search_kliks search(G);
    clock_t start = clock();
    cout << search.GetMaxCliqueSize();
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
}