#include"algorithm.cpp" //Алгоритм MIIM 
#include"kerbosh.cpp"


int main() {
    Graph_Generator generator;

    //input size
    int size;
    cin >> size;

    Graph G  = generator.get_random_graph(size);

    G.print();
    //Запускаем алгоритм Брона — Кербоша
    cout << "------------------------------Bron-Kerbosh -------------------------------------\n";

    clock_t start = clock();
    Kerbosh_Search k_search(G);
    cout << "Max clique size:" << k_search.GetMaxCliqueSize() << endl;
    cout << "Max clique: " << k_search.GetMaxClique() << endl;
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);


    //Запускаем алгоритм MIIM
    cout << "----------------------------------MIIM --------------------------------------\n";
    start = clock();
    Search_kliks MIIM_search(G);
    cout << "Max clique size:" << MIIM_search.GetMaxCliqueSize() << "\n";
    vector<size_t> max_clique = MIIM_search.GetMaxClique();
    cout << "Max clique: " << max_clique << endl;
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);


    //finding error
    //cout << MIIM_search.GetMaxClique();
    //MIIM_search.print_parts_of_kliks();
    //search.find_k_kliks(4);
}