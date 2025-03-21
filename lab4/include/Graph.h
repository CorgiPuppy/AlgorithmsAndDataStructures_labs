#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include "EdgeNode.h"

class Graph {
	private:
		EdgeNode** edges;
		int* outDegree;
		int* inDegree;
		int nVertices;
		int nEdges;
		bool directed;

	public:
		Graph(int vertices, bool isDirected) : nVertices(vertices),  nEdges(0), directed(isDirected) {
			edges = new EdgeNode*[vertices + 1];
			outDegree = new int[vertices + 1];
			inDegree = new int[vertices + 1];

			for (int i = 0; i <= vertices; i++) {
				edges[i] = nullptr;
				outDegree[i] = 0;
				inDegree[i] = 0;
			}
		}

		~Graph() {
			for (int i = 1; i <= nVertices; i++) {
				EdgeNode* current = edges[i];
				while (current) {
					EdgeNode* temp = current;
					current = current->next;
					delete temp;
				}
			}

			delete [] edges;
			delete [] outDegree;
			delete [] inDegree;
		}

		void addEdge(int src, int dest) {
			if (src == dest)
				return;

			EdgeNode* current = edges[src];
			while (current) {
				if (current->vertex = dest)
					return;
				current = current->next;
			}

			EdgeNode* newEdge = new EdgeNode(dest);
			newEdge->next = edges[src];
			edges[src] = newEdge;
			outDegree[src]++;
			inDegree[dest]++;
			nEdges++;

			if (!directed) {
				EdgeNode* reverseEdge = new EdgeNode(src);
				reverseEdge->next = edges[dest];
				edges[dest] = newEdge;
				outDegree[dest]++;
				inDegree[src]++;
			}
		}

		void printGraph() const {
			for (int i = 1; i <= nVertices; i++) {
				std::cout << "Вершина " << i << ": ";
				EdgeNode* current = edges[i];
				while (current != nullptr) {
					std::cout << current->vertex << " ";
					current = current->next;
				}
				std::cout << std::endl;
			}
		}

		int** getAdjacencyMatrix() const {
			int** matrix = new int*[nVertices + 1];
			for (int i = 0; i <= nVertices; i++)
				matrix[i] = new int[nVertices + 1]();

			for (int i = 1; i <= nVertices; i++) {
				EdgeNode* current = edges[i];
				while (current) {
					matrix[i][current->vertex] = 1;
					current = current->next;
				}
			}

			return matrix;
		}

		void freeAdjacencyMatrix(int** matrix) const {
			for (int i = 0; i < nVertices; i++)
				delete [] matrix[i];

			delete [] matrix;
		}

		int getNedges() const { return nEdges; }

		int getOutDegree(int vertex) const { return outDegree[vertex]; }

		int getInDegree(int vertex) const { return inDegree[vertex]; }
};

#endif
