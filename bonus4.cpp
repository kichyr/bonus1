
#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>

using namespace std;

class Graph {
public:
	size_t size;
	int** matrix;
public:
	Graph(){}
    Graph(size_t n_vertex){
		size = n_vertex;
		matrix = new int* [size];
		for(size_t i = 0; i < size; i++){
			matrix[i] = new int [size];
		}
		for(size_t i = 0; i < size; i++){
			for(size_t j = 0; j <= i; j++){
				matrix[i][j] = 0;
				matrix[j][i] = matrix[i][j];
			}
		}
		for(size_t i = 0; i < size; i++){
			matrix[i][i] = 1;
		}
	}

	void print(){
		for(size_t i = 0; i < size; i++){
			for(size_t j = 0; j < size; j++){
				cout << matrix[i][j] << ", ";
			}
			cout << endl;
		}
	}
	
    void AddEdge(size_t from, size_t to){
			matrix[from][to] = 1;
			matrix[to][from] = matrix[from][to];
	};
	
    // Метод возвращает true, если в графе действительно есть клика размера заданного размера
    //virtual bool HasClique(size_t clique_size) = 0;

    // Метод возвращает размер максимальной клики для графа
    //virtual size_t GetMaxCliqueSize() = 0;

    // Метод возвращает вершины максимальной клики
    //virtual std::vector<size_t> GetMaxClique() = 0;
};



void massive(Graph & G, uint64_t * arr){
		for(size_t i = 0; i < G.size; i++){
			arr[i] = 0;
		}
		for(size_t i = 0; i < G.size; i++){
			for(size_t j = 0; j < G.size; j++){
				arr[i] = arr[i] + G.matrix[i][j]*(pow(2,(G.size-j-1)));
			}
		}
};
void Separate(Graph & G, Graph & G1, Graph & G2, Graph & G3){
		for(size_t i = 0; i < G1.size; i++){
			for(size_t j = 0; j <= i; j++){
				G1.matrix[i][j] = G.matrix[i][j];
				G1.matrix[j][i] = G.matrix[i][j];
			}
		}
		for(size_t i = 0; i < G.size - G2.size; i++){
			for(size_t j = 0; j <= i; j++){
				G2.matrix[i][j] = G.matrix[G2.size + i][G2.size + j];
				G2.matrix[j][i] = G.matrix[G2.size + i][G2.size + j];
			}
		}
		for(size_t i = 0; i < G3.size; i++){
			for(size_t j = 0; j < G3.size; j++){
				G3.matrix[i][j] = G.matrix[i][G3.size+j];
			}
		}
};


/*
    От приведенного выше класса вам стоит унаследовать 2 потомков, первый будет предоставлять реализацию MITM
    алгоритма, а второй - эвристики.
    Определить способ хранения можно как в обоих потомках (возможно различным), но реализацию AddEdge и хранения графа
    я бы предложит реализовывать в Graph.
    На любые вопросы по С++ готов ответить в личке или после семинаров.
*/


class GraphBRAB : public Graph {
    // ..
};
