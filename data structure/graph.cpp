#include<iostream>
#include<queue>
using namespace std;
class Graph {
private:
	void operator =(const Graph&)
	{
	}
	Graph(const Graph&)
	{
	}
public:
	Graph()
	{
	}
	virtual ~Graph()
	{
	}
	virtual void Init(int n) = 0;//初始化一个有n个结点的图
	//返回图的结点数和边数
	virtual int n() = 0;
	virtual int e() = 0;
	virtual int first(int v) = 0;
	virtual int next(int v, int w) = 0;
	virtual void setEdge(int v1, int v2, int weight) = 0;
	virtual void delEdge(int v1, int v2,int wt) = 0;
	virtual bool isEdge(int i, int j) = 0;
	virtual int weight(int v1, int v2) = 0;
	virtual int getMark(int v) = 0;
	virtual void setMark(int v, int val) = 0;
};
class Graphm : public Graph {
private:
	int numVertex, numEdge;//存储结点和边的数目
	int** matrix;//指针指向邻接矩阵
	int* mark;//指针指向mark数组
public:
	Graphm(int numVertex)
	{
		Init(numVertex);
	}
	~Graphm()
	{
		delete[] mark;
		for (int i = 0; i < numVertex; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	void Init(int n)
	{
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[n];
		for (int i = 0; i < numVertex; i++)
		{
			mark[i] = 0;
		}
		matrix = (int**) new int* [numVertex];
		for (int i = 0; i < numVertex; i++)
		{
			matrix[i] = new int[numVertex];
		}
		for (int i = 0; i < numVertex; i++)
		{
			for (int j = 0; j < numVertex; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}
	int n()
	{
		return numVertex;
	}
	int e()
	{
		return numEdge;
	}
	int first(int v)
	{
		for (int i = 0; i < numVertex; i++)
		{
			if (matrix[v][i] != 0)
			{
				return i;
			}
		}
		return numVertex;//返回n如果全为0
	}
	int next(int v, int w)
	{
		for (int i = w + 1; i < numVertex; i++)
		{
			if (matrix[v][i] != 0)
			{
				return i;
			}
		}
		return numVertex;
	}
	void setEdge(int v1, int v2, int wt)
	{
		if (matrix[v1][v2] == 0)
		{
			numEdge++;
		}
		matrix[v1][v2] = wt;
	}
	void delEdge(int v1, int v2, int wt)
	{
		if (matrix[v1][v2] != 0)
		{
			numEdge--;
		}
		matrix[v1][v2] = 0;
	}
	bool isEdge(int i, int j)
	{
		return matrix[i][j] != 0;
	}
	int weight(int v1, int v2)
	{
		return matrix[v1][v2];
	}
	int getMark(int v)
	{
		return mark[v];
	}
	void setMark(int v, int val)
	{
		mark[v] = val;
	}
	void DFS(Graph* G, int v)
	{
		G->setMark(v, 1);
		for (int i = G->first(v); i < G->n(); i = G->next(v, i))
		{
			if (G->getMark(i) == 0)
			{
				DFS(G, i);
			}
		}
	}
	void BFS(Graph* G, int start, queue<int>& Q)
	{
		int v, w;
		Q.push(start);
		G->setMark(start, 1);
		while (!Q.empty())
		{
			Q.pop();
			for (w = G->first(v); w < G->n(); w = G->next(v, w))
			{
				if (G->getMark(w) == 0)
				{
					G->setMark(w, 1);
					Q.push(w);
				}
			}
		}
	}
	void topsort1(Graph* G)
	{
		int i;
		for (i = 0; i < G->n(); i++)
		{
			G->setMark(i, 0);
		}
		for (i = 0; i < G->n(); i++)
		{
			if (G->getMark(i) == 0)
			{
				tophelp(G, i);
			}
		}
	}
	void tophelp(Graph* G, int v)
	{
		G->setMark(v, 1);
		for (int w = G->first(v); w < G->n(); w = G->next(v, w))
		{
			if (G->getMark(w) == 0)
			{
				tophelp(G, w);
			}
		}
	}
	void topsort2(Graph* G, queue<int>& Q)
	{
		int Count[G->n()];
		int v, w;
		for (v = 0; v < G->n(); v++)
		{
			Count[v] = 0;
		}
		for (v = 0; v < G->n(); v++)
		{
			for (w = G->first(v); w < G->n(); w = G->next(v, w))
			{
				Count[w]++;
			}
		}
		for (v = 0; v < G->n(); v++)
		{
			if (Count[v] == 0)
			{
				Q.push(v);
			}
		}
		while (Q.size() != 0)
		{
			v = Q.front();
			Q.pop();
			for (w = G->first(v); w < G->n(); w = G->next(v, w))
			{
				Count[w]--;
				if (Count[w] == 0)
				{
					Q.push(w);
				}
			}
		}
	}
};
int minVertex(Graph* G, float* D)
{
	int i, v = -1;
	for (i = 0; i < G->n(); i++)
	{
		if (G->getMark(i) == 0)
		{
			v = i;
			break;
		}
	}
	for (i++; i < G->n(); i++)
	{
		if ((G->getMark(i) == 0) && (D[i] < D[v]))
		{
			v = i;
		}
	}
	return v;
}
void Dijkstra(Graph* G, float* D, int s)
{
	int i, v, w;
	for (i = 0; i < G->n(); i++)
	{
		D[i] = INFINITY;
	}
	D[s] = 0;
	for (int j = 0; j < G->n(); j++)
	{
		cout << D[j] << " ";
	}
	cout << endl;
	for (i = 0; i < G->n(); i++)
	{
		v = minVertex(G, D);
		if (D[v] == INFINITY)
		{
			return;
		}
		G->setMark(v, 1);
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
		{
			if (D[w] > D[v] + G->weight(v, w))
			{
				D[w] = D[v] + G->weight(v, w);
			}
		}
		for (int j = 0; j < G->n(); j++)
		{
			cout << D[j] << " ";
		}
		cout << endl;
	}
}
int main(void)
{
	Graphm G(5);
	G.setEdge(0, 1, 10);
	G.setEdge(0, 2, 3);
	G.setEdge(0, 3, 20);
	G.setEdge(1, 3, 5);
	G.setEdge(2, 1, 2);
	G.setEdge(2, 4, 15);
	G.setEdge(3, 4, 11);
	float* D = new float[5];
	int s = 0;
	Dijkstra(&G, D, s);
}