#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

namespace graph {
enum DirectedTag { undirected, directed };
typedef size_t Index;
typedef unsigned Weight;

template <typename Vertex, DirectedTag directed = directed>
class GraphInterface {
  public:
	struct Edge {
		Index begin;
		Index end;
		Edge(Index begin, Index end) : begin(begin), end(end) {}
		bool operator<(const Edge &other) const {
			return begin < other.begin ||
			       begin == other.begin && end < other.end;
		}
	};
	virtual size_t size() = 0;
	virtual Index getIndex(Vertex vertex) = 0;
	virtual Vertex getVertex(Index index) = 0;
	virtual Weight getWeight(Index start, Index end) = 0;
	virtual void addVertex(Vertex vertex) = 0;
	virtual void addEdge(Vertex u, Vertex v, Weight weight) = 0;

	virtual std::vector<Index> getAdjacences(Index index) = 0;

	static std::vector<Vertex>
	topsort(GraphInterface<Vertex, directed> &graph) {
		std::vector<int> indegree(graph.size(), 0);
		std::queue<Index> q;
		std::vector<Vertex> result;

		for (Index i = 0; i < graph.size(); i++) {
			auto adjacences = graph.getAdjacences(i);
			for (auto &index : adjacences) indegree[index]++;
		}
		for (auto i = 0; i < indegree.size(); i++) {
			if (indegree[i] == 0) q.push(i);
		}
		while (!q.empty()) {
			auto adjacences = graph.getAdjacences(q.front());
			result.push_back(graph.getVertex(q.front()));
			for (auto &index : adjacences) {
				if (--indegree[index] == 0) q.push(index);
			}
			q.pop();
		}
		return result;
	}

	static std::vector<Vertex> BFS(GraphInterface<Vertex, directed> &graph,
	                               Vertex startPoint) {
		using namespace std;
		vector<Vertex> result;
		vector<bool> visited(graph.size(), false);
		queue<Index> q;
		Index start = graph.getIndex(startPoint);
		q.push(start);
		visited[start] = true;
		while (!q.empty()) {
			for (auto &index : graph.getAdjacences(q.front())) {
				if (!visited[index]) {
					q.push(index);
					visited[index] = true;
				}
			}
			result.push_back(graph.getVertex(q.front()));
			q.pop();
		}
		return result;
	}

	static Weight getShortestCost(GraphInterface<Vertex, directed> &graph,
	                              Vertex start, Vertex finish) {
		using namespace std;

		struct Node {
			Weight distance;
			bool known;
			Node() : distance(-1), known(false) {}
		};

		vector<Node> nodes(graph.size());
		int current = graph.getIndex(start);
		nodes[current].distance = 0;

		while (current != -1) {
			nodes[current].known = true;
			auto adjacences = graph.getAdjacences(current);
			for (auto &adj : adjacences) {
				Weight distance =
				    nodes[current].distance + graph.getWeight(current, adj);
				if (distance < nodes[adj].distance) {
					nodes[adj].distance = distance;
				}
			}
			Weight min = -1;
			for (auto i = 0; i < graph.size(); i++) {
				if (!nodes[i].known && min > nodes[i].distance) {
					min = nodes[i].distance;
					current = i;
				}
			}
			if (min == -1) current = -1;
		}
		return nodes[graph.getIndex(finish)].distance;
	}

	static size_t getPathCount(GraphInterface<Vertex, directed> &graph,
	                           Vertex start, Vertex finish) {
		using namespace std;

		stack<Index> searchStack;
		searchStack.push(graph.getIndex(start));
		size_t result = 0;
		Index goal = graph.getIndex(finish);
		do {
			if (goal == searchStack.top()) {
				result++;
				searchStack.pop();
				continue;
			}
			auto adjacences = graph.getAdjacences(searchStack.top());
			searchStack.pop();
			for (auto &index : adjacences) { searchStack.push(index); }
		} while (!searchStack.empty());
		return result;
	}

	static void solution(GraphInterface<Vertex, directed> &graph) {
		using namespace std;
		size_t degree = 0;
		for (Index i = 0; i < graph.size(); i++) {
			if (graph.getAdjacences(i).empty()) {
				cout << "NO";
				return;
			}
			degree += graph.getAdjacences(i).size();
		}
		if (degree / 2 == graph.size() - 1) {
			cout << "YES";
		} else {
			cout << "NO";
		}
	}
};

template <typename Vertex, DirectedTag directed = directed>
class AdjList : public GraphInterface<Vertex, directed> {
  public:
	typedef typename GraphInterface<Vertex, directed>::Edge Edge;

	AdjList() {}

	AdjList(std::vector<Vertex> vertices,
	        std::vector<std::pair<Vertex, Vertex> > edges) {
		for (auto &vertex : vertices) { addVertex(vertex); }
		for (auto &edge : edges) { addEdge(edge.first, edge.second); }
	}

	AdjList(std::vector<Vertex> vertices,
	        std::vector<std::tuple<Vertex, Vertex, Weight> > edges) {
		for (auto &vertex : vertices) { addVertex(vertex); }
		for (auto &edge : edges) {
			addEdge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge));
		}
	}

	size_t size() { return vertexList.size(); }

	Index getIndex(Vertex vertex) {
		for (Index i = 0; i < vertexList.size(); i++)
			if (vertexList[i] == vertex) return i;
		return null;
	}

	Vertex getVertex(Index index) { return vertexList[index]; }

	Weight getWeight(Index start, Index end) {
		return edgeList[{ start, end }];
	}

	void addVertex(Vertex vertex) {
		vertexList.push_back(vertex);
		adjList.push_back(std::set<Index>());
	}

	void addEdge(Vertex u, Vertex v, Weight weight = 1) {
		Index begin = getIndex(u);
		Index end = getIndex(v);
		if (begin == null || end == null) return;
		edgeList.insert(std::make_pair(Edge(begin, end), weight));
		adjList[begin].insert(end);
		if (!directed) { adjList[end].insert(begin); }
	}

	std::vector<Index> getAdjacences(Index index) {
		return std::vector<Index>(adjList[index].begin(), adjList[index].end());
	}

	void display() {
		using namespace std;
		int i = 0;
		for (auto &list : adjList) {
			cout << vertexList[i++] << " : ";
			for (auto &index : list) cout << vertexList[index] << ' ';
			cout << endl;
		}
	}

  private:
	const Index null = -1;
	std::vector<std::set<Index> > adjList;
	std::map<Edge, Weight> edgeList;
	std::vector<Vertex> vertexList;
};
} // namespace graph

int main() {
	using namespace std;
	typedef graph::AdjList<int, graph::undirected> Graph;

	int kase;
	cin >> kase;
	for (int i = 0; i < kase; i++) {
		int n, m;
		cin >> n >> m;
		vector<int> v;
		vector<pair<int, int> > e;
		for (int i = 1; i <= n; i++) v.push_back(i);
		for (int u, v, i = 0; i < m; i++) {
			cin >> u >> v;
			e.push_back({ u, v });
		}
		Graph g = { v, e };
		// g.display();
		Graph::solution(g);
		cout << endl;
	}
}
