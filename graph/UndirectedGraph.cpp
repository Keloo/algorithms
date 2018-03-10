template <class TCost>
class UndirectedGraph : public Graph<TCost> {
public:
    UndirectedGraph() {};
    UndirectedGraph(long _size): Graph<TCost>(_size) {};
    void addEdge(long from, long to, TCost cost = 0) {
        this->edges.push_back({from, to, cost});
        this->adjacencyList[from].push_back({to, cost});
        this->adjacencyList[to].push_back({from, cost});
    }
    void printEdges() {
        for (auto edge: this->edges) {
            cout << edge.from << ' ' << edge.to << endl;
        }
    }
};