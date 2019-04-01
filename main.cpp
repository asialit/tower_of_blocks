#include <iostream>
#include <limits.h>


struct vertex {
	int number;
	char* block;
};

int countArray(char array[], int n, int count) {

	if (array[n] != '\0') {
		return countArray(array, n + 1, count + 1);
	}

	return count;
}


int prefix(char* w, char* t) {

	int wlength = countArray(w, 0, 0);
	int tlength = countArray(t, 0, 0);

	int m = wlength + tlength + 1;
	char* connectedArray = new char[m + 1];

	int l = 0;

	for (int j = 0; j < tlength; j++)
	{
		connectedArray[l] = t[j];
		l++;
	}

	connectedArray[l] = '#';
	l++;

	for (int j = 0; j < wlength; j++)
	{
		connectedArray[l] = w[j];
		l++;
	}

	connectedArray[l] = '\0';

	int* pi = new int[m+1];
	pi[0] = -1;

	int k = -1;

	for (int i = 1; i <= m; i++) {
		while (k > -1 && connectedArray[k] != connectedArray[i - 1]) {
			k = pi[k];
		}

		pi[i] = ++k;
	}

	delete[] connectedArray;
	int ret = pi[m];
	delete[] pi;
	return ret; //return how many common letters
}

//vertex with minimum distance value
int shortestPath(int paths[], bool ifClosed[], int size)
{
	// Initialize min value
	int min = INT_MAX;
	int min_index = 0;

	for (int v = 0; v < size; v++) {
		if (ifClosed[v] == false && paths[v] < min) {
			min = paths[v];
			min_index = v;
		}
	}

	return min_index;
}

int dijkstra(int** graph, int size) {

	int* paths = new int[size];
	bool* ifClosed = new bool[size];


	for (int i = 1; i < size; i++) {
		paths[i] = INT_MAX;
		ifClosed[i] = false;
	}

	paths[0] = 0;

	for (int i = 0; i < size; i++)
	{
		//vertex with minimum distance value
		int u = shortestPath(paths, ifClosed, size);

		ifClosed[u] = true;

		for (int v = 0; v < size; v++) {

			if (graph[u][v] != -1) {
				if (!ifClosed[v]) {
					if (paths[u] + graph[u][v] < paths[v]) {
						paths[v] = paths[u] + graph[u][v];
					}
				}
			}
		}
	}

	delete[] ifClosed;
	int ret = paths[1];
	delete[] paths;
	return ret;
}

int main() {

	int size;

	std::cin >> size;

	std::cin.ignore();

	//create array of vertexs
	vertex* vertexs = new vertex[size];

	size_t lineSize = 1000;

	for (int i = 0; i < size; i++) {
		vertexs[i].number = i;
		vertexs[i].block = new char[lineSize];

		std::cin.getline(vertexs[i].block, lineSize);
	}

	// create graph
	int** graph = new int*[size];
	for (int i = 0; i < size; i++)
		graph[i] = new int[size];

	//insert values into the graph
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j || i == 1 || j == 0) {
				graph[i][j] = -1;
			}
			else {
				if (prefix(vertexs[i].block, vertexs[j].block) == 0) {
					graph[i][j] = -1;
				}
				else {
					graph[i][j] = countArray(vertexs[j].block, 0, 0) - prefix(vertexs[i].block, vertexs[j].block);
				}
			}
		}
	}

	int result = dijkstra(graph, size);

	if (result == INT_MAX) {
		std::cout << '0';
	}
	else {
		std::cout << result + countArray(vertexs[0].block, 0, 0);
	}

	for (int i = 0; i < size; ++i) {
		delete[] graph[i];
	}

	delete[] graph;


	for (int i = 0; i < size; ++i) {
		delete[] vertexs[i].block;
	}
	delete[] vertexs;

	return 0;
}