#include <list>
#include <set>
#include<iostream>

using namespace std;

class Kerbosh_Search{

list<set<int>> max_by_inclusion_kliks;
int **add_m;
int size;
public:
    Kerbosh_Search(Graph G) {
        addition_matrix(G.matrix, G.size);
        max_by_inclusion_kliks = kerbosh(add_m, G.size);
    }

    void print_kliks() {
        for (auto klik : max_by_inclusion_kliks) {
            for(auto i : klik)
                cout << i << " ";
        cout << endl;
        }
    }

    ~Kerbosh_Search() {
        for(int i = 0; i < size; i++)
            delete[]add_m[i];
        max_by_inclusion_kliks.clear();
    }

    size_t GetMaxCliqueSize() {
        size_t max_size_of_clique = 0;
        for (auto klik : max_by_inclusion_kliks) {
            if(klik.size() > max_size_of_clique)
                max_size_of_clique = klik.size();
        }
        return max_size_of_clique;
    }

    std::vector<size_t> GetMaxClique() {
        vector<size_t> max_clique;
        size_t max_size_of_clique = 0;
        for (auto klik : max_by_inclusion_kliks) {
            if(klik.size() > max_size_of_clique) {
                max_size_of_clique = klik.size();
                max_clique.clear();
                copy(klik.begin(), klik.end(), back_inserter(max_clique));
            }
        }
        return max_clique;
    }

    void addition_matrix(int **matrix, uint size){
        this->size = size;
        add_m = new int* [size];
		for(size_t i = 0; i < size; i++){
			add_m[i] = new int [size];
		}
		for(size_t i = 0; i < size; i++){
			for(size_t j = 0; j < size; j++){
				if(matrix[i][j] == 1)
                    add_m[i][j] = 0;
                else
                    add_m[i][j] = 1;
                if(i == j)
                    add_m[i][j] = 1;
			}
		}
    }



    list<set<int> >kerbosh(int **&a,int SIZE) {
        set <int> M,G,K,P;
        list<set<int> > REZULT;
        for (int i=0; i<SIZE;i++)
        {
            K.insert(i);
        }
        int v,Count=0,cnt=0;
        int Stack1[100];
        std::set<int> Stack2[100];
        std::set<int>::iterator theIterator;
        theIterator=K.begin();
        while ((K.size()!=0)||(M.size()!=0))
        {
            if (K.size()!=0)
            {
                theIterator=K.begin();
                v=*theIterator;
                Stack2[++Count]=M;
                Stack2[++Count]=K;
                Stack2[++Count]=P;
                Stack1[++cnt]=v;
                M.insert(v);
                for (int i=0;i<SIZE;i++)
                {
                    if (a[v][i])
                    {
                        theIterator=K.find(i);
                        if (theIterator!=K.end())
                        {
                            K.erase(theIterator);
                        }
                        theIterator=P.find(i);
                        if (theIterator!=P.end())
                        {
                            P.erase(theIterator);
                        }
                    }
                }
                theIterator=K.find(v);
                if (theIterator!=K.end())
                {
                    K.erase(theIterator);
                }
            }
            else
            {
                if (P.size()==0)
                {
                    REZULT.push_back(M);
                }
                v=Stack1[cnt--];
                P=Stack2[Count--];
                K=Stack2[Count--];
                M=Stack2[Count--];
                theIterator=K.find(v);
                if (theIterator!=K.end())
                {
                    K.erase(theIterator);
                }
                P.insert(v);
            }
        }
        return  REZULT;
    }
};