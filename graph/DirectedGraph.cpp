template <class TCost>
class DirectedGraph : public Graph<TCost> {
public:
    using typename Graph<TCost>::Edge;
    vector<vector<Edge>> inEdges;
    DirectedGraph() {};
    DirectedGraph(long _size, bool _zeroIndexed): Graph<TCost>(_size, _zeroIndexed) {};
    DirectedGraph(long _size): Graph<TCost>(_size) {};
    void addEdge(long from, long to, TCost cost = 0) {
        this->edges.push_back({from, to, cost});
        this->adjacencyList[from].push_back({to, cost});
    }
    void printEdges() {
        for (auto edge: this->edges) {
            cout << edge.from << ' ' << edge.to << endl;
        }
    }
    void buildInEdges() {
        inEdges.resize(this->size);
        for (Edge u: this->edges) {
            inEdges[u.to].push_back(u);
        }
    }
};