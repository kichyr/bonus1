
#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>

using namespace std;

class Graph {
public:
	size_t size;
	int** matrix;

		Graph(){}
		/*Graph(const Graph &a) {
			size = a.size;
			matrix = new int* [size];
			for(size_t i = 0; i < size; i++){
				matrix[i] = new int [size];
			}
			for(size_t i = 0; i < size; i++){
				for(size_t j = 0; j <= i; j++){
					matrix[j][i] = a.matrix[i][j];
				}
			}
		}*/

    Graph(size_t n_vertex) {
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

	// Какого не работает ??
	
	void free() {
		for(size_t i = 0; i < size; i++){
			delete[]matrix[i];
		}
		delete[]matrix;
		
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
	}
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
}

void Separate(Graph & G, Graph & G1, Graph & G2, Graph & G3){
	//cout<< G1.size << G.size;
		for(size_t i = 0; i < G1.size; i++){
			for(size_t j = 0; j < G1.size; j++){
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
			for(size_t j = 0; j < G.size - G3.size; j++){
				G3.matrix[i][j] = G.matrix[i][G3.size+j];
			}
		}
		
		for(size_t i = 0; i < G3.size; i++)
				G3.matrix[i][G3.size-1] = 0;
		
}
