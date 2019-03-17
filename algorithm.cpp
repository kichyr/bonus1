#include <iostream>
#include <cmath>
#include <vector>
#include "bonus4.cpp"
#include "graph_generator.cpp"
#include "stdint.h"
#include <utility> 

using namespace std;

template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) 
{ 
    os << "["; 
    for (int i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    } 
    os << "]\n"; 
    return os; 
} 

typedef struct Subsets{
    //int;
    int flag;
    uint64_t img;
    int size_of_subset;
}Subsets;


class Search_kliks {
public:
    uint64_t *adj_m1, *adj_m2, *adj_m3; // матрица смежности

    vector<vector<pair<uint64_t,uint64_t>>> kliks1;
    vector<vector<uint64_t>> kliks2;
     

    Graph G1, G2, G3;
    Subsets *subset1, *subset2;
    size_t size, sub_size;

    size_t size_of_max_clicue = 0;
    Search_kliks(Graph G){
        //size - половина суммарного размера
        size = (int)ceil(G.size/2+0.5);
        G1 = Graph(size);
        G2 = Graph(size);
        G3 = Graph(size); // for connection
    

        Separate(G, G1, G2, G3);

        adj_m1 = new uint64_t[size];
        adj_m2 = new uint64_t[size];	
        adj_m3 = new uint64_t[size];	
        

        massive(G1, adj_m1);
        massive(G2, adj_m2);
        massive(G3, adj_m3);
        //
        //G1.print();
        //G2.print();
        //G3.print();
        
        sub_size = (int)pow(2, size);

        kliks1.resize(size+1);
        kliks2.resize(size+1);
        
        
        this->inizialise_subset(&subset1);
        this->inizialise_subset(&subset2);
        //
        subset1[0].flag = 1;
        subset1[0].img = 0;
        subset1[0].size_of_subset = 0;
        subset2[0].flag = 1;
        subset2[0].img = 0;
        subset2[0].size_of_subset = 0;
        kliks1[0].push_back(make_pair(0, (uint64_t)(-1)));
        kliks2[0].push_back(0);

        tree_search(0, size-1);
        
        //print_parts_of_kliks();

        //print_parts_of_kliks();
        //print_kliks();

    }

    void inizialise_subset(Subsets **subset) {
        *subset = new Subsets[sub_size];
    }


    void tree_search(uint64_t i, int level) {
        if(!(level >= 0)) return;
        
        uint64_t right_c = (i|(((uint64_t)1)<<level));

        //Для первого графа
        if(subset1[i].flag == 1) {
            if((right_c & adj_m1[size-level-1]) == right_c) {
                subset1[right_c].flag = 1;
                subset1[right_c].size_of_subset = subset1[i].size_of_subset+1;

                if(i != 0)
                    subset1[right_c].img = subset1[i].img & adj_m3[size-level-1];
                else
                    subset1[right_c].img = adj_m3[size-level-1];

                kliks1[subset1[right_c].size_of_subset].push_back(make_pair(right_c, subset1[right_c].img));
            }
        }
        //Для второго графа
        if(subset2[i].flag == 1) {
            if((right_c & adj_m2[size-level-1]) == right_c) {
                subset2[right_c].flag = 1;
                subset2[right_c].size_of_subset = subset2[i].size_of_subset+1;

                kliks2[subset2[right_c].size_of_subset].push_back(right_c);
            }
        }

    tree_search(right_c, level-1);
        tree_search(i, level-1);
    }

    // Необходимые методы
    bool HasClique(size_t clique_size) {
        for(int i = 0; i <= size; i++) {
            for(uint64_t klik2 : kliks2[i]) 
                for(pair<uint64_t,uint64_t> klik1 : kliks1[clique_size - i])
                    if((klik1.second & klik2) == klik2) {
                        return true;
                    }
        }
        return false;
    }

    virtual size_t GetMaxCliqueSize() {
        GetMaxClique();
        return size_of_max_clicue;
    }


    std::vector<size_t> GetMaxClique() {
        size_of_max_clicue = 0;
        vector<size_t> max_clicue;
        for(int i = size; i >= 0; i--) {
            for(int j = size; j >= 0; j--)
                for(uint64_t klik2 : kliks2[i]) 
                    for(pair<uint64_t,uint64_t> klik1 : kliks1[j])
                        if((klik1.second & klik2) == klik2 && size_of_max_clicue < i+j) {
                            size_of_max_clicue = i+j;
                            max_clicue =  make_vertex_set(klik1.first, klik2, size_of_max_clicue);
                        }
        }
        return max_clicue;
    }



    // Дохрена различных выводов

    void find_k_kliks(int k) {
        for(int i = 0; i < size; i++) {
            for(uint64_t klik2 : kliks2[i]) 
                for(pair<uint64_t,uint64_t> klik1 : kliks1[k - i])
                    if((klik1.second & klik2) == klik2) {
                        cout << "this is klik of size k ";
                        print_set(klik1.first, klik2);
                    }
        }
    }

    void print_parts_of_kliks() {
        for(int i = 0; i < size; i++) {
            cout << "\n" << i  << endl;
            for(pair<uint64_t,uint64_t> klik1 : kliks1[i])
                cout << " (" << klik1.first << "; " << klik1.second << ")";
        }
        for(int i = 0; i < size; i++) {
            cout << "\n" << i  << endl;
            for(uint64_t klik2 : kliks2[i])
                cout << " " << klik2;
        }
    }


    vector<size_t> make_vertex_set(uint64_t set1,uint64_t set2,int size_of_set) {
        vector<size_t> max_clique;
        for(int i = 0; i < size; i++)
            if((set1 & (((uint64_t)1)<<i)) > 0)
               max_clique.push_back(size - i - 1);

        for(int i = 0; i < size; i++)
            if((set2 & (((uint64_t)1)<<i)) > 0)
                max_clique.push_back(2*size - i - 1);
        return max_clique;
    }

    void print_set(uint64_t set1,uint64_t set2) {
        for(int i = 0; i < size; i++)
            if((set1 & (((uint64_t)1)<<i)) > 0)
                cout << size - i - 1 << ' ';

        for(int i = 0; i < size; i++)
            if((set2 & (((uint64_t)1)<<i)) > 0)
                cout << 2*size - i - 1 << ' ';
        cout << "\n";
    }

    void print_kliks() {
        for(uint64_t i = 0; i < sub_size; i++) {
            if(subset1[i].flag == 1)
                cout << i << " ";
        }
         for(uint64_t i = 0; i < sub_size; i++) {
            if(subset2[i].flag == 1)
                cout << i << " ";
        }
        //cout << sub_size;
    }
};
